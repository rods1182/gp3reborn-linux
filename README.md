# GP3 Reborn for Linux

**Grand Prix 3 and Grand Prix 3 2000 running natively on Linux — no Wine, no Proton, no Steam.**

[English](#english) · [Português](#português) · [How it works](docs/HOW-IT-WORKS.txt) · [Como funciona](docs/COMO-FUNCIONA.txt) · [Windows version (GP3RT)](https://github.com/rods1182/gp3rt---GrandPrix-3-Runtime)

---

## English

GP3 Reborn runs your own copy of Grand Prix 3 (1.13) or Grand Prix 3 2000 on Linux as a native program. It is not an emulator and not Wine: it is a small stand-in for Windows, built only for GP3. The real game code runs directly on your processor, and everything the game would ask Windows for is translated to Linux:

- graphics: DirectDraw/Direct3D 7 → OpenGL 3.3;
- sound: DirectSound → PulseAudio/PipeWire;
- controls: DirectInput → Linux keyboard, joysticks, wheels and force feedback.

It shares its engine with [GP3RT](https://github.com/rods1182/gp3rt---GrandPrix-3-Runtime), the `ddraw.dll` for Windows, and has the same fixes, including the 1.0.3 fix for very detailed tracks.

### Download

Open **Releases** (on the right of this page) and download **GP3Reborn-Linux-1.1.0.tar.gz**. The automatic "Source code" links are for developers only.

### Quick start

1. Have your game folder ready, with an executable **without SafeDisc**:
   - Grand Prix 3 1.13: `Gp3.exe`
   - Grand Prix 3 2000: `gp3 2000.exe`

   A folder copied from Windows is fine; put it in your home folder.
2. Unpack the release and copy **all** its files into the game folder.
3. Double-click `gp3`. The first time, a "Grand Prix 3" entry is added to your applications menu.

   If nothing happens: right-click the file > Properties > Permissions > "Allow executing file as program". Do this for `gp3`, `gp3-game` and `GPxPatch`.
4. Optional settings: open `GP3Reborn-Configurator.html` in your browser to change quality, widescreen, window and graphics card.

### Getting GPxPatch

GPxPatch 4.52 is **René Smit's** work and is **not included** here. This project only provides `GPxPatch`, a configuration screen and launcher for Linux that reads and writes the same files as GPxPatch on Windows.

1. Download GPxPatch 4.52 from the author's site: <https://www.sdidit.nl/download.html> (`inst-gpxpatch452.exe`, a Windows installer).
2. The game folder needs **`GPxPSup.dll`** and the **`gpxpdata`** folder. Use one of these:
   - **You already have GP3 + GPxPatch on Windows:** copy `GPxPSup.dll` and `gpxpdata` into the Linux game folder. Your settings, track sets and car sets come along.
   - **On a Windows PC:** install it into a GP3 folder there, then copy `GPxPSup.dll` and `gpxpdata` over.
   - **With Wine, for the installer only:** run `wine inst-gpxpatch452.exe` and pick your game folder. Linux files are on drive `Z:` in Wine. The game itself never uses Wine.
3. Double-click `GPxPatch` in the game folder. You get the GPxSet, GPxTrack, GPxLap, GPxSAT, GPxCInfo and GPxSound tabs, plus keys, fonts and video. "Create shortcuts" adds it to the menu, and "Start with / without GPxPatch" starts the game.

In GPxPatch keep **Debug ON** (required by GP3 Reborn) and **CPU on all cores**.

Do **not** run `GPxPatch.exe`, which is a Windows program. On Linux, GP3 Reborn loads the GPxPatch modules into the game by itself, without changing any GPxPatch file.

### Features

- Fullscreen at your desktop resolution, with Alt+Enter for a window.
- Widescreen with Hor+ field of view: more picture at the sides, no stretching.
- The 3D is rendered at 2x–4x and scaled down (no jaggies), with anisotropic filtering.
- On laptops with two GPUs, the dedicated one is picked automatically.
- Softer rain spray near the TV cameras.
- 3D sound in GP3 2000, and wheels with force feedback.
- GP3's per-frame geometry limit is raised: detailed community tracks no longer lose car bodies or crash.
- No 32-bit libraries are needed on your system.

### Requirements

- 64-bit Linux on an Intel/AMD PC. Tested on Linux Mint and Ubuntu 24.04, with glibc 2.17 or newer.
- OpenGL 3.3.
- SDL2. On Debian/Ubuntu/Mint: `sudo apt install libsdl2-2.0-0`.
- Your own game files. No game files are distributed here.

Full guide: [docs/README.txt](docs/README.txt). Building from source: [LINUX-BUILD.txt](LINUX-BUILD.txt).

### Reporting problems

Please include:

- the game version (1.13 or 2000), the track and the camera;
- `gp3linux.log` and `gp3linux-game.log` from the game folder.

---

## Português

O GP3 Reborn roda a sua cópia do Grand Prix 3 (1.13) ou do Grand Prix 3 2000 no Linux como um programa nativo. Não é emulador nem Wine: é um "Windows de mentirinha" feito só para o GP3. O código de verdade do jogo roda direto no processador, e tudo o que o jogo pediria ao Windows é traduzido para o Linux:

- gráficos: DirectDraw/Direct3D 7 → OpenGL 3.3;
- som: DirectSound → PulseAudio/PipeWire;
- controles: DirectInput → teclado, joystick, volante e force feedback do Linux.

Usa o mesmo motor do [GP3RT](https://github.com/rods1182/gp3rt---GrandPrix-3-Runtime), a `ddraw.dll` para Windows, e tem as mesmas correções, inclusive a da 1.0.3 para pistas muito detalhadas.

### Download

Abra **Releases** (à direita desta página) e baixe o **GP3Reborn-Linux-1.1.0.tar.gz**. Os links automáticos "Source code" são só para desenvolvedores.

### Começo rápido

1. Tenha a pasta do jogo, com o executável **sem SafeDisc**:
   - Grand Prix 3 1.13: `Gp3.exe`
   - Grand Prix 3 2000: `gp3 2000.exe`

   Pode ser a pasta copiada do Windows; coloque-a na sua pasta pessoal.
2. Descompacte e copie **todos** os arquivos para a pasta do jogo.
3. Dê dois cliques em `gp3`. Na primeira vez, aparece "Grand Prix 3" no menu de aplicativos.

   Se nada acontecer: botão direito no arquivo > Propriedades > Permissões > "Permitir executar o arquivo como um programa". Faça isso com `gp3`, `gp3-game` e `GPxPatch`.
4. Configurações (opcional): abra o `GP3Reborn-Configurator.html` no navegador para mudar qualidade, widescreen, janela e placa de vídeo.

### Como obter o GPxPatch

O GPxPatch 4.52 é trabalho de **René Smit** e **não vem aqui**. Este projeto traz só o `GPxPatch`, uma tela de configuração e lançador para Linux que lê e grava os mesmos arquivos do GPxPatch do Windows.

1. Baixe o GPxPatch 4.52 no site do autor: <https://www.sdidit.nl/download.html> (`inst-gpxpatch452.exe`, um instalador de Windows).
2. A pasta do jogo precisa do **`GPxPSup.dll`** e da pasta **`gpxpdata`**. Use um destes jeitos:
   - **Já tem o GP3 + GPxPatch no Windows:** copie o `GPxPSup.dll` e a `gpxpdata` para a pasta do jogo no Linux. Configurações, conjuntos de pistas e de carros vão junto.
   - **Num PC com Windows:** instale numa pasta do GP3 de lá e copie o `GPxPSup.dll` e a `gpxpdata`.
   - **Com o Wine, só para o instalador:** rode `wine inst-gpxpatch452.exe` e escolha a pasta do jogo. No Wine, os arquivos do Linux ficam no drive `Z:`. O jogo em si nunca usa o Wine.
3. Dê dois cliques em `GPxPatch` na pasta do jogo. Aparecem as guias GPxSet, GPxTrack, GPxLap, GPxSAT, GPxCInfo e GPxSound, além de teclas, fontes e vídeo. "Criar atalhos" põe no menu, e "Iniciar com / sem GPxPatch" abre o jogo.

No GPxPatch, deixe o **Debug LIGADO** (o GP3 Reborn precisa dele) e a **CPU em todos os núcleos**.

**Não** use o `GPxPatch.exe`, que é um programa de Windows. No Linux, o GP3 Reborn carrega os módulos do GPxPatch no jogo sozinho, sem mudar nenhum arquivo do GPxPatch.

### Recursos

- Tela cheia na resolução da área de trabalho, com Alt+Enter para janela.
- Widescreen com campo de visão Hor+: mais imagem dos lados, sem esticar.
- O 3D é desenhado em 2x a 4x e reduzido (sem serrilhado), com filtragem anisotrópica.
- Em notebooks com duas placas, a dedicada é escolhida sozinha.
- Spray de chuva mais suave perto das câmeras de TV.
- Som 3D no GP3 2000, e volantes com force feedback.
- O limite de geometria por quadro do GP3 foi aumentado: pistas detalhadas da comunidade não perdem mais a carroceria dos carros nem fecham.
- Não precisa de bibliotecas de 32 bits no sistema.

### O que precisa

- Linux de 64 bits em PC Intel/AMD. Testado no Linux Mint e no Ubuntu 24.04, com glibc 2.17 ou mais nova.
- OpenGL 3.3.
- SDL2. No Debian/Ubuntu/Mint: `sudo apt install libsdl2-2.0-0`.
- Os seus arquivos do jogo. Nenhum arquivo do jogo é distribuído aqui.

Guia completo: [docs/LEIAME.txt](docs/LEIAME.txt). Compilar: [LINUX-BUILD.txt](LINUX-BUILD.txt).

### Relatar problemas

Mande:

- a versão do jogo (1.13 ou 2000), a pista e a câmera;
- o `gp3linux.log` e o `gp3linux-game.log` da pasta do jogo.

---

## Credits / Créditos

- GP3 Reborn for Linux: Rodrigo Motta (Rods), with Claude (Anthropic).
- Special thanks / agradecimento especial: **Stephan Séguin** ("Seguin" on GrandPrixGames.org) — the first user and the first feedback, who spread the word on GrandPrixGames.org, GP2Forum and the Grand Prix Games group on Facebook; **JF ("BeADriver")** — the log that revealed GP3 2000's 3D sound bug.
- GPxPatch 4.52 © 2001–2019 René Smit — not included; get it from <https://www.sdidit.nl>. Thank you, René!
- Grand Prix 3 / Grand Prix 3 2000 © Geoff Crammond / MicroProse.
- Components:
  - SDL2 (zlib);
  - Nuklear (public domain / MIT);
  - fonts: Inter, DejaVu, Noto Sans SC — licences in `art/fonts`.

No license has been chosen yet for this project's own code: see [STATUS-LICENCA.md](STATUS-LICENCA.md).
