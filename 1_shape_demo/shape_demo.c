#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

void main()
{
  configureClocks();
  lcd_init();

  // clear the screen in case something is already on there
  clearScreen(COLOR_BLACK);

  //draw_rectangle();
  //draw_triangle();
  //draw_circle();
  
  draw_border(0);
  // draw_border(16);
  // draw_border(32);
  
  draw_undertale_heart((screenWidth / 2), (screenHeight / 2) + 8, COLOR_RED);
  draw_undertale_heart((screenWidth / 2) - 32, (screenHeight / 2), COLOR_ORANGE);
  draw_undertale_heart((screenWidth / 2) + 32, (screenHeight / 2), COLOR_GREEN);
  draw_undertale_heart((screenWidth / 2) - 24, (screenHeight / 2) - 24, COLOR_YELLOW);
  draw_undertale_heart((screenWidth / 2) + 24, (screenHeight / 2) - 24, COLOR_PURPLE);
  draw_undertale_heart((screenWidth / 2) - 24, (screenHeight / 2) + 24, COLOR_WHITE);
  draw_undertale_heart((screenWidth / 2) + 24, (screenHeight / 2) + 24, COLOR_CYAN);

  // draw_sus((screenWidth / 2), (screenHeight / 4) * 3, COLOR_RED);

  
  //draw_heart(screenWidth / 2, screenHeight / 2, COLOR_RED);
  //draw_mario((screenWidth/2) - 7, (screenHeight - 2) - 7);

  draw_diamond(24, 24, 5, COLOR_BLUE);
  draw_diamond(screenWidth - 24, 24, 5, COLOR_ORANGE);
  draw_diamond(24, screenHeight - 24, 5, COLOR_ORANGE);
  draw_diamond(screenWidth - 24, screenHeight - 24, 5, COLOR_BLUE);
  
  or_sr(0x10);	/**< CPU OFF */
}
