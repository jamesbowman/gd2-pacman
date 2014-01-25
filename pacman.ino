#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "pacman_assets.h"

void setup()
{
  GD.begin();
  LOAD_ASSETS();
}

#define SPRITE_COUNT 5

#define MODE0_COLUMNS           19
#define MODE0_ROWS              24
static uint8_t _scrp[MODE0_COLUMNS * MODE0_ROWS];

#define mode0_get_block(x,y) (_scrp[(x)+(y)*MODE0_COLUMNS])
#define mode0_set_block(x,y, blk) do {_scrp[(x)+(y)*MODE0_COLUMNS] = (blk);} while(0)
#define mode0_cls()  memset(&mode0_get_block(0,0), ' ', MODE0_ROWS * MODE0_COLUMNS)

static void mode0_print(byte x, byte y, const char *s)
{
  GD.cmd_text(8 * x, 10 * y, FONT_HANDLE, 0, s);
}

#define mode0_print(x, y, txt) \
({ \
  static char __c[] PROGMEM = (txt); \
  memcpy_P(&mode0_get_block((x),(y)), (__c), strlen_P(__c)); \
})

static void sprite_put(byte _, byte x, byte y, byte c)
{
  GD.Vertex2ii(x, y, FONT_HANDLE, c);
}

static void mode0_paint()
{
  GD.ClearColorRGB(0x000000);
  GD.Clear();
  GD.Begin(BITMAPS);

  uint8_t *pblk = &mode0_get_block(0, 0);
  for (byte y = 0; y < 10 * MODE0_ROWS; y += 10) {
    for (byte x = 0; x < 8 * MODE0_COLUMNS; x += 8) {
      uint8_t c = *pblk++;
      if (c)
        GD.Vertex2ii(x, y, FONT_HANDLE, c);
    }
  }
}

/*
 *  Albert Seward Copyright (C) 2005
 *  All Rights Reserved. Proprietary.
 *  alse7905@student.uu.se
 * 
 */

#include "pacman.h"

void scene_intro(void)
{
  uint8_t  i, mode, tmp;
  int pos, pacman;
  
  pos = 60;
  pacman = 70;

  mode = 1;

  for (;;) {
    mode0_cls();
    mode0_print(5,1, "\033\021\021\021\021\021\021\021\032");
    mode0_print(5,2, "\020" PACMAN_LOGO "\020");
    mode0_print(5,3, "\035\021\021\021\021\021\021\021\034");

    mode0_print(4,19, "INSERT COIN");
    mode0_print(3,22, "COPYRIGHT 2005");
    mode0_print(3,23, "ALBERT SEWARD");

    for (;;) {
      mode0_paint();

      for(i = 1; i < SPRITE_COUNT; i++) {
        tmp = pos - i * 10;
        if (tmp < 152 && tmp > 0) {
          if (mode)
            sprite_put(5-i, tmp, 70, BLINKY -1 + i);
          else if(pacman < tmp)
            sprite_put(5-i, tmp, 70, EATEN);
          else
            sprite_put(5-i, tmp, 70, EATABLE);
        }
      }

      if(pacman < 152 && pacman > 0)
        sprite_put(0, pacman, 70, pacman & 8 ? (mode?PACMAN_OPEN_RIGHT:PACMAN_OPEN_LEFT) : (mode?PACMAN_CLOSED_RIGHT:PACMAN_CLOSED_LEFT));

      if(mode) {
        pos++;
        pacman++;
      } else {
        pos--;
        pacman-=2;
      }

      if(pos > 152)
        pacman = 200;
      else if(pos < -10)
        pacman = 0;


      if(pos > 250) {
        mode = 0;
      } else if(pos < -40) {
        mode0_print(5,6, "\045  BLINKY");
        // key_wait_timeout(KEY_COIN, 60);
        mode0_print(5,7, "\046  CLYDE");
        // key_wait_timeout(KEY_COIN, 60);
        mode0_print(5,8, "\047  PINKY");
        // key_wait_timeout(KEY_COIN, 60);
        mode0_print(5,9, "\050  INKEY");
        // key_wait_timeout(KEY_COIN, 200);
        // memset(&mode0_get_block(5,6), ' ', 20*4);
        break;
      }
      GD.swap();
    }
  }

  // highscore_view();
}

void loop()
{
  scene_intro();
}
