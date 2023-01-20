#ifndef __SUPPORT_H 
#define __SUPPORT_H

#define GROOTIDLE_WIDTH (69)
#define GROOTIDLE_HEIGHT (93)
#define GROOTIDLE_BYTES_PER_PIXEL (2)
#define GROOTIDLE_PIXEL_DATA0 ((unsigned char*) GROOTIDLE_pixel_data0)
#define GROOTIDLE_PIXEL_DATA1 ((unsigned char*) GROOTIDLE_pixel_data1)
void draw_Groot(int posX, int posY);
void clear_Groot(int posX, int posY);
void battery_management(int, int, int);



#endif
