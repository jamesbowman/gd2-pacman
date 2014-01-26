gd2-pacman
==========

Gameduino port of Albert Seward's AVR pacman.
To compile on Arduino, build a sketch with `pacman.ino`, `pacman.h` and `pacman_assets.h`.

Tap to start play. Pacman's direction is controlled by tilt.

![screenshot](/screenshot.jpg)

Some notes on the conversion
----------------------------

Playing area is 19x24 tiles.
With the original 8x10 tiles, this gives an area of 152x240.
With tiles resized to 14x18 the screen area is 266x408,
a good fit for Gameduino 2's screen in sideways ("portrait") orientation.

A single set of 96 tiles holds all the game's graphics, both foreground and sprites.
The graphics are encoded at the original 8x10 resolution, and and the larger 14x18 resolution.
The 14x18 tileset is:

![preview](/graphics/preview.png)

The game code uses an in-memory tilemap for the game screen, which takes 19x24=456 bytes of RAM.
The Gameduino 2 has no direct support for tilemaps, so every frame it draws all 456 tiles as bitmaps.
