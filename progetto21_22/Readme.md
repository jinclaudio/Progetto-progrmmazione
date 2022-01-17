Descrizione
Questo gioco è un semplice RPG con grafica ASCII.
Lo scopo del gioco è sopravvivere e accumulare punti raccogliendo artefatti e
sconfiggendo nemici.
Il gioco si organizza in livelli, per passare al livello successivo è necessario
sconfiggere tutti i nemici oppure trovare la chiave.
I comandi sono:
   - WASD per muoversi
   - J per sparare
   - q per chiudere il gioco.
I nemici sono:
   - m, nemico con 1 di vita e 1 di danno;
   - M, nemico con 3 di vita e 2 di danno;
   - B, nemico con la vita che varia a secondo del livello e 3 di danno.
I bonus sono:
   - H, che cura il player di 1 vita.
   - K, apre la porta del livello.
   - T e t sono due artefatti che teletrasportano il player ad un bonus.

Compiling and Running

The program is runnable on Linux and MacOS and it needs
these libraries:
-ncurses.h
-time.h
-math.h

After downloaded the repository, open the folder in terminal
and write:
    cd Make
    cmake ..
    make
    ./Game
