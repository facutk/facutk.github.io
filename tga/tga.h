#ifndef TGA_H
#define TGA_H

// 32 bit image
typedef struct
{
  int width, height;
  int** data;
} tga_RBitmap;

int tga_write_truecolor( tga_RBitmap* data, char * filename );

#endif