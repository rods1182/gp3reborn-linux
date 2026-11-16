#include <stdio.h>
#include <stdint.h>
/* Headless platform: frames are written as PNG files, input comes from a
 * timed script. Used for automated testing of the runtime. */
#include "rt.h"
#include "plat.h"
#include <sys/stat.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

static int g_mode_w = 640, g_mode_h = 480, g_mode_bpp = 32;
static int g_frames;
static char g_pending_shot[128];
static pthread_mutex_t g_pmx = PTHREAD_MUTEX_INITIALIZER;

/* ------------------------------------------------------------------ */
/* input script                                                          */
typedef struct { uint32_t t; int kind; int vk; int down; char arg[96]; } sevt_t;
enum { SE_KEY, SE_SHOT, SE_QUIT, SE_CHAR, SE_MOUSE, SE_ACTIVATE };
static sevt_t g_ev[1024];
static int g_nev, g_next;

static int vk_from_name(const char *s) {
    static const struct { const char *n; int vk; } t[] = {
        {"enter", 0x0d}, {"return", 0x0d}, {"esc", 0x1b}, {"escape", 0x1b}, {"space", 0x20}, {"left", 0x25}, {"up", 0x26},
        {"right", 0x27}, {"down", 0x28}, {"tab", 0x09}, {"shift", 0x10}, {"ctrl", 0x11}, {"alt", 0x12}, {"backspace", 0x08},
        {"pgup", 0x21}, {"pgdn", 0x22}, {"home", 0x24}, {"end", 0x23}, {"f1", 0x70}, {"f2", 0x71}, {"f3", 0x72}, {"f4", 0x73},
        {"f5", 0x74}, {"f6", 0x75}, {"f7", 0x76}, {"f8", 0x77}, {"f9", 0x78}, {"f10", 0x79}, {"f11", 0x7a}, {"f12", 0x7b}, {"prtsc", 0x2c}, {NULL, 0} };
    for (int i = 0; t[i].n; i++) if (!strcasecmp(t[i].n, s)) return t[i].vk;
    if (strlen(s) == 1) return toupper((unsigned char)s[0]);
    if (s[0] == '0' && s[1] == 'x') return (int)strtol(s, NULL, 16);
    return 0;
}
extern int vk_to_scancode(int vk);

void script_start(void) {
    if (!g_cfg.script[0]) return;
    FILE *f = fopen(g_cfg.script, "r");
    if (!f) { WARN("script %s not found", g_cfg.script); return; }
    char line[256]; uint32_t last = 0;
    while (fgets(line, sizeof line, f) && g_nev < 1020) {
        char *s = line; while (isspace((unsigned char)*s)) s++;
        if (!*s || *s == '#') continue;
        char tstr[32], cmd[32], a1[96] = "", a2[32] = "";
        if (sscanf(s, "%31s %31s %95s %31s", tstr, cmd, a1, a2) < 2) continue;
        uint32_t t = tstr[0] == '+' ? last + (uint32_t)atoi(tstr + 1) : (uint32_t)atoi(tstr);
        last = t;
        sevt_t *e = &g_ev[g_nev];
        memset(e, 0, sizeof *e); e->t = t;
        if (!strcmp(cmd, "key") || !strcmp(cmd, "tap")) {
            e->kind = SE_KEY; e->vk = vk_from_name(a1);
            if (!strcmp(a2, "down")) { e->down = 1; g_nev++; }
            else if (!strcmp(a2, "up")) { e->down = 0; g_nev++; }
            else { e->down = 1; g_nev++; g_ev[g_nev] = *e; g_ev[g_nev].down = 0; g_ev[g_nev].t = t + 80; g_nev++; }
        } else if (!strcmp(cmd, "shot")) { e->kind = SE_SHOT; snprintf(e->arg, sizeof e->arg, "%s", a1); g_nev++; }
        else if (!strcmp(cmd, "quit")) { e->kind = SE_QUIT; g_nev++; }
        else if (!strcmp(cmd, "activate")) { e->kind = SE_ACTIVATE; g_nev++; }
        else if (!strcmp(cmd, "type")) { e->kind = SE_CHAR; snprintf(e->arg, sizeof e->arg, "%s", a1); g_nev++; }
        else if (!strcmp(cmd, "click")) { e->kind = SE_MOUSE; e->vk = atoi(a1); e->down = atoi(a2); g_nev++; }
    }
    fclose(f);
    /* stable sort by time (insertion) */
    for (int i = 1; i < g_nev; i++) { sevt_t k = g_ev[i]; int j = i - 1; while (j >= 0 && g_ev[j].t > k.t) { g_ev[j + 1] = g_ev[j]; j--; } g_ev[j + 1] = k; }
    LOG("script: %d events", g_nev);
}

extern void win_post_message(HWND h, UINT msg, WPARAM w, LPARAM l);
void plat_pump(void) {
    uint32_t now = rt_ticks_ms() - 1000;   /* rt clock starts at 1s */
    if (g_cfg.max_seconds && now > (uint32_t)g_cfg.max_seconds * 1000) {
        LOG("max-seconds reached, exiting"); { extern void gpx_dump_modules(void); gpx_dump_modules(); }
        plat_screenshot("final");
        if (g_log) fflush(g_log);
        _exit(0);
    }
    while (g_next < g_nev && g_ev[g_next].t <= now) {
        sevt_t *e = &g_ev[g_next++];
        switch (e->kind) {
        case SE_KEY: LOG("script: key %02x %s", e->vk, e->down ? "down" : "up"); win_input_key(e->vk, vk_to_scancode(e->vk), e->down); break;
        case SE_SHOT: { extern int g_probe_active; g_probe_active = 1; plat_screenshot(e->arg);
            const char *md = getenv("GP3_MEMDUMP");
            if (md) { char fn[512]; snprintf(fn, sizeof fn, "%s_%s.bin", md, e->arg); FILE *f = fopen(fn, "wb");
                      if (f) { fwrite((void *)(uintptr_t)0x401000, 1, 0xd00000 - 0x401000, f); fclose(f); } }
            break; }
        case SE_ACTIVATE: { extern HWND g_main_hwnd; LOG("script: WM_ACTIVATE"); win_post_message(g_main_hwnd, 6, 1, 0); break; }
        case SE_QUIT: LOG("script: quit"); plat_screenshot("final"); if (g_log) fflush(g_log); _exit(0);
        case SE_CHAR: for (char *c = e->arg; *c; c++) win_input_char(*c == '_' ? ' ' : *c); break;
        case SE_MOUSE: win_input_mouse(e->vk >> 16, e->vk & 0xffff, 1, e->down); break;
        }
    }
}

/* ------------------------------------------------------------------ */
static uint32_t *g_last; static int g_lw, g_lh;

void plat_screenshot(const char *name) {
    pthread_mutex_lock(&g_pmx);
    if (g_last) {
        mkdir(g_cfg.dump_dir, 0755);
        char p[1024]; snprintf(p, sizeof p, "%s/%s.png", g_cfg.dump_dir, name);
        write_png(p, g_last, g_lw, g_lh, g_lw);
        LOG("screenshot %s (%dx%d)", p, g_lw, g_lh);
    } else snprintf(g_pending_shot, sizeof g_pending_shot, "%s", name);
    pthread_mutex_unlock(&g_pmx);
}

void plat_present(const uint32_t *xrgb, int w, int h, int pitch_px) {
    pthread_mutex_lock(&g_pmx);
    if (!g_last || g_lw != w || g_lh != h) { free(g_last); g_last = malloc((size_t)w * h * 4); g_lw = w; g_lh = h; }
    for (int y = 0; y < h; y++) memcpy(g_last + (size_t)y * w, xrgb + (size_t)y * pitch_px, (size_t)w * 4);
    g_frames++;
    { extern int g_probe_active; if (g_probe_active == 1) g_probe_active = 2; else if (g_probe_active == 2) g_probe_active = 0; }
    int dump = g_cfg.dump_every > 0 && g_frames % g_cfg.dump_every == 0;
    char pend[128]; snprintf(pend, sizeof pend, "%s", g_pending_shot); g_pending_shot[0] = 0;
    pthread_mutex_unlock(&g_pmx);
    if (dump || pend[0]) {
        mkdir(g_cfg.dump_dir, 0755);
        char p[1024];
        if (pend[0]) snprintf(p, sizeof p, "%s/%s.png", g_cfg.dump_dir, pend);
        else snprintf(p, sizeof p, "%s/frame_%05d.png", g_cfg.dump_dir, g_frames);
        write_png(p, xrgb, w, h, pitch_px);
        TRACE("dumped %s", p);
    }
}
void plat_client_size(int *w, int *h) { *w = g_mode_w; *h = g_mode_h; }
void plat_set_mode(int w, int h, int bpp) { g_mode_w = w; g_mode_h = h; g_mode_bpp = bpp; LOG("display mode -> %dx%dx%d", w, h, bpp); }
void plat_show_cursor(int show) { (void)show; }
void plat_message_box(const char *cap, const char *text) { (void)cap; (void)text; }
void video_init(void) {}
void plat_set_window(void *hwnd, unsigned flags) { (void)hwnd; (void)flags; }
/* no audio device in headless runs: DirectSound advances with the clock */
int plat_audio_rate(void) { return 0; }
uint32_t plat_audio_space(void) { return 0; }
void plat_audio_write(const int16_t *lr, uint32_t frames) { (void)lr; (void)frames; }
