#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
  {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  int nearest_x = static_cast<int>(round(x));
  int nearest_y = static_cast<int>(round(y));
  return clamped_pixel(nearest_x, nearest_y, c);
  }

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
  {
    //interpolazione bilineare = prende 4 pixel vincini e calcola il valore interpolato in mezzo ad essi,
    //pesando in base alla distanza
    int ix = static_cast<int>(floor(x));
    int iy = static_cast<int>(floor(y));

    float dx = x - ix;
    float dy = y - iy;
    
    float v00 = clamped_pixel(ix,    iy,   c);
    float v01 = clamped_pixel(ix,    iy+1, c);
    float v10 = clamped_pixel(ix+1,  iy,   c);
    float v11 = clamped_pixel(ix+1,  iy+1, c);

    float interp_x0 = v00 * (1- dx) + v10 * dx;
    float interp_x1 = v01 * (1- dx) + v11 * dx;

    float ris = interp_x0 * (1- dy) + interp_x1 * dy;
    return ris;
  }

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);
  for (int c = 0; c < im.c; c++){
    for (int j = 0; j < h; j++){
      for (int i = 0; i<w; i++){
        float x_old = ((i + 0.5f) * im.w) / w - 0.5f;
        float y_old = ((j + 0.5f) * im.h) / h - 0.5f;
        ret(i, j, c) = im.pixel_nearest(x_old , y_old, c);
      }
    }
  }  
  return ret;
  }


// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);
  for (int c = 0; c < im.c; c++){
    for (int j = 0; j < h; j++){
      for (int i = 0; i<w; i++){
        float x_old = ((i + 0.5f) * im.w) / w - 0.5f;
        float y_old = ((j + 0.5f) * im.h) / h - 0.5f;
        ret(i, j, c) = im.pixel_bilinear(x_old , y_old, c);
      }
    }
  }  
  return ret;
  }


