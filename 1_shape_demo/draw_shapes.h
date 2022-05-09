#ifndef _DRAW_SHAPES_H_
#define _DRAW_SHAPES_H_

/* draws a rectangle */
void draw_rectangle(void);
/* draws an equaleral triangle by starting at the top with a 
   width of 1 and increasing the width by 1
   for every row */
void draw_triangle(void);
/* draws a circle using bresenham's algorithm */
void draw_circle(void);

void draw_border(int inner_offset);

void draw_heart(int x_origin, int y_origin, u_int colorBGR);

void draw_mario(u_int bottom_left_x, u_int bottom_left_y);

void draw_undertale_heart(u_int x, u_int y, u_int color);

void draw_sus(u_int x, u_int y, u_int c);

void draw_diamond(u_int x, u_int y, u_int width, u_int color);

#endif // _DRAW_SHAPES_H_
