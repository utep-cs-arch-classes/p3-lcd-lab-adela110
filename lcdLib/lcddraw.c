/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

void drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int color)
{
  u_int length = x_end - x_start;

  lcd_setArea(x_start, y, x_end, y);

  for(int i = 0 ; i <= length ; i++)
  {
    lcd_writeColor(color);
  }
}

void draw_diamond(u_int x, u_int y, u_int width, u_int color)
{
  u_int x1 = x - width;
  u_int x2 = x + width;

  u_int y_top = y - 1;
  u_int y_bot = y + 1;

  // Draw Mid Line
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

