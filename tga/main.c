#include <stdlib.h>
#include <stdio.h>
#include "tga.h"

int main() {
  int width = 320;
  int height = 240;
  
  int **img = (int**)malloc(width*sizeof(int*));
  for (int x=0; x<width; x++)
    {
      img[x] = (int*)malloc(height*sizeof(int));
      for (int y=0; y<height; y++)
        {
          img[x][y] = 0x000000 + x + y;
        }
    }

  tga_RBitmap image = {
    .width = 320,
    .height = 240,
    .data = img
  };

  tga_write_truecolor(&image, "out.tga");
  for (int x=0; x<width; x++)
    {
      free(img[x]);
    }
  free(img);

  return 0;
}