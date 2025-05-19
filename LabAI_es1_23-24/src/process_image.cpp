#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
// HW0 #3.1 optimize the code
Image rgb_to_grayscale(const Image &im) {
    /* calcolare per ogni pixel il valore di luma Y' con la seguente formula:  Y′ = 0.299 * R + 0.587 * G + 0.114 * B   */

    assert(im.c == 3); // only accept RGB images
    Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)

    for (int y = 0; y < im.h; y++){
        for (int x = 0; x < im.w; x++) {
            // Extract singular channel values (RGB)
            float r = im(x, y, 0);
            float g = im(x, y, 1);
            float b = im(x, y, 2);

            // Calculate luma value based on Constants
            float luma = 0.299f * r + 0.587f * g + 0.114f * b;

            // Save result in mono channel array created before
            gray(x, y, 0 ) = luma;
        }
    }
    return gray;
}


// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image &im, float r, float g, float b) {
    assert(im.c == 1);
    Image rgb(im.w, im.h, 3);

    for (int q2 = 0; q2 < im.h; q2++)
        for (int q1 = 0; q1 < im.w; q1++) {
            rgb(q1, q2, 0) = r * im(q1, q2);
            rgb(q1, q2, 1) = g * im(q1, q2);
            rgb(q1, q2, 2) = b * im(q1, q2);
        }

    return rgb;
}


// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image &im, int c, float v) {
    assert(c >= 0 && c < im.c); // needs to be a valid channel

    // TODO: shift all the pixels at the specified channel
    /* bestemmio per un errore stupido: nel for non ci va il <= ma solo < perchè gli array partono da zero e arrivano a size -1. 
    l'errore era "access out of bounds"  */

    for (int y = 0; y < im.h; ++y){
        for (int x = 0; x < im.w; ++x){
            im(x, y, c) += v;
        }
    }
}



// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image &im, int c, float v) {
    assert(c>=0 && c<im.c); // needs to be a valid channel

    // TODO: scale all the pixels at the specified channel
    for (int y = 0; y < im.h; ++y){
        for (int x = 0; x < im.w; ++x) {
            im (x, y, c) *= v;
        }
    }
}


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image &im) {
    for (int c = 0; c < im.c; ++c){
        for (int y = 0; y < im.h; ++y){
            for (int x = 0; x < im.w; ++x){
                float &val = im(x,y,c);
                if (val < 0.0f) val = 0.0f;
                else if (val > 1.0f) val = 1.0f;
            }
        }
    }
}

// These might be handy
float max(float a, float b, float c) {
    return max({a, b, c});
}

float min(float a, float b, float c) {
    return min({a, b, c});
}


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image &im) {
    assert(im.c==3 && "only works for 3-channels images");

    // TODO: Convert all pixels from RGB format to HSV format
    for (int y = 0; y < im.h; ++y){
        for (int x = 0; x < im.w; ++x){
            float R = im(x, y, 0);
            float G = im(x, y, 1);
            float B = im(x, y, 2);

            float V = max(R, G, B);
            float m = min(R, G, B);
            float C = V - m;

            float S = (V == 0) ? 0 : C / V;

            float H = 0;
            if (C != 0) {
                if (V == R)
                    H = (G - B) / C;
                else if (V == G)
                    H = (B - R) / C + 2;
                else
                    H = (R - G) / C + 4;

                H /= 6.0f;
                if (H < 0) H += 1.0f;
            }

            im(x, y, 0) = H;
            im(x, y, 1) = S;
            im(x, y, 2) = V;
        }
    }



}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image &im) {
    assert(im.c==3 && "only works for 3-channels images");
    // TODO: Convert all pixels from HSV format to RGB format
    for (int y = 0; y < im.h; ++y){
        for (int x = 0; x < im.w; ++x){
            float H = im(x, y, 0);
            float S = im(x, y, 1);
            float V = im(x, y, 2);

            float C = V * S;
            float H_ = H * 6.0f;
            float X = C * (1 - fabs(fmodf(H_, 2.0f) - 1));
            float m = V - C;

            float Rp, Gp, Bp;
            
            if (0 <= H_ && H_ < 1) {
                Rp = C; Gp = X; Bp = 0;
            } else if (1 <= H_ && H_ < 2) {
                Rp = X; Gp = C; Bp = 0;
            } else if (2 <= H_ && H_ < 3) {
                Rp = 0; Gp = C; Bp = X;
            } else if (3 <= H_ && H_ < 4) {
                Rp = 0; Gp = X; Bp = C;
            } else if (4 <= H_ && H_ < 5) {
                Rp = X; Gp = 0; Bp = C;
            } else if (5 <= H_ && H_ < 6) {
                Rp = C; Gp = 0; Bp = X;
            } else {
                Rp = Gp = Bp = 0; // fallback, dovrebbe essere impossibile
            }

            im(x, y, 0) = Rp + m;
            im(x, y, 1) = Gp + m;
            im(x, y, 2) = Bp + m;
        }
    }
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");

    // TODO: Convert all pixels from RGB format to LCH format


    NOT_IMPLEMENTED();

}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");

    // TODO: Convert all pixels from LCH format to RGB format

    NOT_IMPLEMENTED();

}


// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }

void Image::shift(int c, float v) { shift_image(*this, c, v); }

void Image::scale(int c, float v) { scale_image(*this, c, v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }

void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }

//void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
