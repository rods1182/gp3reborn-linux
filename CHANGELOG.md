# Changelog

## 1.1.0

**English**
- Same engine as GP3RT 1.1.0 for Windows: each frame's drawing goes to the graphics card in one go; textures are converted, reused and mip-mapped with much less work (big help on Intel graphics).
- GP3 2000 no longer closes in long races (bug in GP3 2000's own 3D sound: a lock that doesn't really lock); fixed in memory, always on.
- New `GP3Reborn-Configurator.html`: opens the game folder, reads `gp3rt.ini` and the last logs, shows the graphics card and game found, explains every option.
- Docs: GPxPatch Debug ON (required) and CPU on all cores.
- Thanks to Stephan Séguin ("Seguin"), the first user and the one who spread the word, and to JF ("BeADriver") for the log that revealed the GP3 2000 sound bug.

**Português**
- Mesmo motor do GP3RT 1.1.0 para Windows: o desenho de cada quadro vai para a placa de vídeo de uma vez; texturas convertidas, reaproveitadas e com mipmaps com muito menos trabalho (ajuda muito em placas Intel).
- O GP3 2000 não fecha mais em corridas longas (erro do próprio som 3D do GP3 2000: uma trava que não trava de verdade); corrigido na memória, sempre ligado.
- `GP3Reborn-Configurator.html` novo: abre a pasta do jogo, lê o `gp3rt.ini` e os últimos logs, mostra a placa de vídeo e o jogo encontrados e explica cada opção.
- Documentação: Debug do GPxPatch LIGADO (obrigatório) e CPU em todos os núcleos.
- Agradecimentos ao Stephan Séguin ("Seguin"), primeiro usuário e quem divulgou o projeto, e ao JF ("BeADriver"), pelo log que revelou o erro do som do GP3 2000.

## 1.0.2 (first public release / primeira versão pública)

**English**
- Grand Prix 3 1.13 and Grand Prix 3 2000 running natively on Linux (`gp3` + `gp3-game`).
- Same engine and fixes as GP3RT 1.0.3 for Windows, including the per-frame geometry limit raised from 2,999 to 16,000 edges (no more vanishing car bodies, grey polygons or crashes on very detailed tracks).
- `GPxPatch`: configuration screen and launcher for GPxPatch 4.52 on Linux (GPxPatch itself is not included; get it from https://www.sdidit.nl).
- `GP3Reborn-Configurator.html`: edits `gp3rt.ini` in the browser.
- Bilingual documentation and `gp3rt.ini` comments.

**Português**
- Grand Prix 3 1.13 e Grand Prix 3 2000 nativos no Linux (`gp3` + `gp3-game`).
- Mesmo motor e correções do GP3RT 1.0.3 para Windows, inclusive o limite de geometria por quadro aumentado de 2.999 para 16.000 bordas (sem carros sumindo, polígonos cinza ou fechamento em pistas muito detalhadas).
- `GPxPatch`: tela de configuração e lançador do GPxPatch 4.52 no Linux (o GPxPatch em si não vem junto; baixe em https://www.sdidit.nl).
- `GP3Reborn-Configurator.html`: edita o `gp3rt.ini` no navegador.
- Documentação e comentários do `gp3rt.ini` em inglês e português.
