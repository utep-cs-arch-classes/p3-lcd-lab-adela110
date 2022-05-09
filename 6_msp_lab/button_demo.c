#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

char redraw_screen = 1;
u_int backgroundColor = COLOR_BLACK;
 
void
update_text(void)
{
  const u_char text_row = 20;
  const u_char text_col = 40;
  const u_char char_width = 12;
  static u_char blue = 31, green = 16, red = 31;
  u_int on_color  =                (green << 5) | red;
  u_int off_color = (blue << 11)                | red;

  drawString5x7(4, 16, "LcD DeMO\0", COLOR_WHITE, backgroundColor);
  drawString5x7(4, 24, "[NOT TIGER!]\0", COLOR_WHITE, backgroundColor);
  drawString5x7(4, 32, "FUN! PLAY!\0", COLOR_WHITE, backgroundColor);
  drawString5x7(4, 40, "GOOD TIME!\0", COLOR_WHITE, backgroundColor);
  
  if (switch1_state == down) {
    // drawChar5x7(text_col, text_row, 'O',on_color, backgroundColor);
    // drawRectOutline(0, 0, 128, 160, COLOR_GREEN);

    // Draw Diamonds
    draw_diamond(8, 120, 4, COLOR_ORANGE);
    draw_diamond(40, 120, 8, COLOR_GREEN);
    draw_diamond(78, 120, 12, COLOR_RED);

    drawString5x7(8, 60, "Diamonds\0", on_color, backgroundColor);
    
    buzzer_set_period(C3);
  } else {
    // drawChar5x7(text_col, text_row, '-',off_color, backgroundColor);
    // drawRectOutline(0, 0, 128, 160, backgroundColor);

    // Draw Diamonds
    draw_diamond(8, 120, 4, backgroundColor);
    draw_diamond(40, 120, 8, backgroundColor);
    draw_diamond(78, 120, 12, backgroundColor);

    drawString5x7(8, 60, "Diamonds\0", off_color, backgroundColor);
    
    buzzer_set_period(0);
  }
  if (switch2_state == down) {
    // drawChar5x7(text_col + char_width, text_row, 'K',on_color, backgroundColor);
    drawString5x7(8, 72, "Hearts\0", on_color, backgroundColor);

    // Draw Hearts
    u_int colors[] = {COLOR_ORANGE, COLOR_YELLOW, COLOR_GREEN, COLOR_RED, COLOR_CYAN, COLOR_PURPLE, COLOR_WHITE};

    u_int x_pos = 100;
    u_int y_pos = 24;

    for (int i = 0 ; i < 7 ; i++)
    {
      draw_undertale_heart(x_pos, y_pos, colors[i]);
      y_pos += 16;
    }
    
    buzzer_set_period(E3);
  } else {
    // drawChar5x7(text_col + char_width, text_row, '-',off_color, backgroundColor);
    drawString5x7(8, 72, "Hearts\0", off_color, backgroundColor);

    u_int x_pos = 100;
    u_int y_pos = 24;

    for (int i = 0 ; i < 7 ; i++)
    {
      draw_undertale_heart(x_pos, y_pos, backgroundColor);
      y_pos += 16;
    }

    
    buzzer_set_period(0);
  }
  /*
  if (switch3_state == down)
  {
    drawString5x7(8, 84, "Switch 3!\0", on_color, backgroundColor);
  } else {
    drawString5x7(8, 84, "Switch 3!\0", off_color, backgroundColor);
  }
  */

  drawRectOutline(0, 0, 120, 150, COLOR_GREEN);
  
}

void main(void)
{
  
  configureClocks();
  led_init();
  switch_p2_init();
  lcd_init();

  buzzer_init();
  
  //enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(backgroundColor);

  while (1) {			/* forever */
    if (redraw_screen) {
      redraw_screen = 0;
      update_text();
    }
    green_on = 0;   	/* led off */
    led_changed = 1;
    led_update();
    or_sr(0x10);	/**< CPU OFF */
    
    green_on = 1;	/* led on */
    led_changed = 1;
    led_update();
  }
}

    
    
