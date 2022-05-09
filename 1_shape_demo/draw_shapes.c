#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"

void
draw_rectangle(void)
{
  int height = 10;
  int width  = 60;
  int row = 20, col = screenWidth / 2;
  int left_col = col - (width / 2);
  int top_row  = row - (height / 2);

  u_int blue = 16, green = 0, red = 31;
  u_int color = (blue << 11) | (green << 5) | red;

  fillRectangle(left_col, row, width, height, color);
}

void
draw_border(int inner_offset)
{
  drawRectOutline((0) + inner_offset, (0) + inner_offset, (screenWidth - 1) - inner_offset * 2, (screenHeight - 1) - inner_offset * 2, COLOR_GREEN);
}
  
void
draw_triangle(void)
{
  int height = 40;
  int row = 80, col = screenWidth / 2;

  int step = 0;

  int blue = 31, green = 0, red = 31;

  u_int color = (blue << 11) | (green << 5) | red;

  // draw a n equilateral triangle
  // starts at the top and works down
  // at the first row the width is 1, second 2 and so on
  for (step = 0; step < height; step++) {
    // left side of triangle
    u_char start_col = col - (step / 2);
    // right side of triangle
    u_char end_col   = col + (step / 2);
    u_char width     = end_col - start_col;
    fillRectangle(col - (step / 2), row+step, width, 1, color);
  }
}


void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for (u_int i = 0; i <= length; i++) {
    lcd_writeColor(colorBGR);
  }
  
}

void
draw_diamond(u_int x, u_int y, u_int width, u_int color)
{
  u_int x1 = x - width;
  u_int x2 = x + width;

  u_int y_top = y - 1;
  u_int y_bot = y + 1;
  
  // Draw mid line
  drawHorizontalLine(x1, x2, y_top, color);
  drawHorizontalLine(x1, x2, y, color);
  drawHorizontalLine(x1, x2, y_bot, color);

  // Draw Top Diamond
  y_top -= 1;
  x1 += 1;
  x2 -= 1;
  while (x2 - x1 >= 1)
  {
    drawHorizontalLine(x1, x2, y_top, color);
    y_top -= 1;
    drawHorizontalLine(x1, x2, y_top, color);
    y_top -= 1;

    x1 += 1;
    x2 -= 1;
  }
  drawHorizontalLine(x1, x2, y_top, color);

  // Draw Bot Diamond
  y_bot += 1;
  x1 = x - width;
  x2 = x + width;
  while (x2 - x1 >= 1)
  {
    drawHorizontalLine(x1, x2, y_bot, color);
    y_bot += 1;
    drawHorizontalLine(x1, x2, y_bot, color);
    y_bot += 1;

    x1 += 1;
    x2 -= 1;
  }
  drawHorizontalLine(x1, x2, y_bot, color);
  
}

void
draw_sus(u_int x, u_int y, u_int c)
{
  drawHorizontalLine(x + 1, x + 3, y - 1, c);
  // Body
  for (int i = 0 ; i <= 7 ; i++)
  {
    drawHorizontalLine(x, x + 5, y + i, c);
  }

  // Eye
  for (int i = 1 ; i <= 5 ; i++)
  {
    drawHorizontalLine(x - 1, x + 2, y + i, COLOR_CYAN);
  }

  // Legs
  drawHorizontalLine(x, x + 1, y - 8, c);
  drawHorizontalLine(x, x + 1, y - 9, c);

  drawHorizontalLine(x + 3, x + 4, y - 8, c);
  drawHorizontalLine(x + 3, x + 4, y - 9, c);

  // BackPack
  for (int i = 1 ; i <= 6 ; i++)
  {
    drawHorizontalLine(x + 5, x + 6, y + 1, c);
  }
}


void
draw_heart(u_int x_origin, u_int y_origin, u_int color)
{
  // Origin is bottom of the heart
  drawPixel(x_origin, y_origin, color);

  // Staircase towards middle
  for (int i = 1 ; i < 8 ; i++) {
    drawHorizontalLine(x_origin - i, x_origin + i, y_origin - i, color);
  }
  drawHorizontalLine(x_origin - 5, x_origin + 5, y_origin - 5, color);
  drawHorizontalLine(x_origin - 5, x_origin + 5, y_origin - 6, color);
  drawHorizontalLine(x_origin - 5, x_origin + 5, y_origin - 7, color);
}

void
draw_undertale_heart(u_int x, u_int y, u_int color)
{
  drawHorizontalLine(x, x + 3, y, color);
  drawHorizontalLine(x, x + 3, y - 1, color);

  drawHorizontalLine(x - 2, x + 5, y - 2, color);
  drawHorizontalLine(x - 2, x + 5, y - 3, color);

  drawHorizontalLine(x - 4, x + 7, y - 4, color);
  drawHorizontalLine(x - 4, x + 7, y - 5, color);

  drawHorizontalLine(x - 6, x + 9, y - 6, color);
  drawHorizontalLine(x - 6, x + 9, y - 7, color);

  drawHorizontalLine(x - 6, x + 9, y - 8, color);
  drawHorizontalLine(x - 6, x + 9, y - 9, color);

  drawHorizontalLine(x - 6, x + 9, y - 10, color);
  drawHorizontalLine(x - 6, x + 9, y - 11, color);

  // Heart top
  drawHorizontalLine(x - 6, x, y - 12, color);
  drawHorizontalLine(x + 3, x + 9, y - 12, color);

  drawHorizontalLine(x - 6, x, y - 13, color);
  drawHorizontalLine(x + 3, x + 9, y - 13, color);

  drawHorizontalLine(x - 5, x - 1, y - 14, color);
  drawHorizontalLine(x + 4, x + 8, y - 14, color);

  drawHorizontalLine(x - 4, x - 3, y - 15, color);
  drawHorizontalLine(x + 6, x + 7, y - 15, color);
}


// Origin is on tip of marios left foot
void
draw_mario(u_int bottom_left_x, u_int bottom_left_y)
{
  int y = bottom_left_y;
  int bottom_right_x = bottom_left_x + 11;
  
  // Draw the shoes
  drawHorizontalLine(bottom_left_x, bottom_left_x + 3, y, COLOR_BROWN);
  drawHorizontalLine(bottom_left_x + 1, bottom_left_x + 2, y - 1, COLOR_BROWN);

  drawHorizontalLine(bottom_right_x - 3, bottom_right_x, y, COLOR_BROWN);
  drawHorizontalLine(bottom_right_x - 2, bottom_right_x - 1, y, COLOR_BROWN);
}


void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
					  
}

void
draw_circle(void)
{
  int x_coord = screenWidth / 2;
  int y_coord = 60;
  int r = 20;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  u_int color = COLOR_SIENNA;

  drawLines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, color);
  }
}
  

