#include "image.h"
#include <cstring>
#include <chrono>
#include <iostream>

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image &im, int x, int y, int ch) {

    // TODO: calculate and return the index

    /* SPIEGAZIONE: dato un pixel in posizione (x,y,ch) la funzione restituisce l'indice corrispondente nell'array data (array monodimensionale)
        quindi index = ch * (w * h) + y * w + x;
    */
    return ch * im.w * im.h + y * im.w + x;
}

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image &im, int x, int y, int ch) {
    // TODO: clamp the coordinates and return the correct pixel value

    /* SPIEGAZIONE: restituisce il valore del pixel ma CLAMPANDO cioè limitando le coordinate fuori range */
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (ch < 0) ch = 0;
    if (x >= im.w) x = im.w -1;
    if (y >= im.h) y = im.h -1;
    if (ch >= im.c) ch = im.c -1;

    return im(x, y, ch);
}

// TODO: modify for unexpected values
// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image &im, int x, int y, int ch, float value) {
    // TODO: Only set the pixel to the value if it's inside the image

    /* SPIEGAZIONE: setta un pixel, ma non deve fare nulla se le coordinate sono fuori range */
    if (x < 0 || x >= im.w || y < 0 || y >= im.h || ch < 0 || ch >= im.c) {
        return;
    }
    im(x, y, ch) = value; // Imposta il valore del pixel
}


// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
// HW #2.1: optimize the code with memcopy or other tricks, and check if you can speed it up
// (e.g. https://stackoverflow.com/questions/48993833/copy-2d-array-using-memcpy)
void copy_image(Image &to, const Image &from) {

    // You might want to check how 'memcpy' function works
    //infatti memcpy è una funzione che copia blocchi di memoria: void* memcpy(void* dest, const void* src, size_t n);

    //copia dati matrice
    to.w = from.w;
    to.h = from.h;
    to.c = from.c;

    // alloca memoria per pixel
    int size = to.w * to.h * to.c;
    to.data = (float *) calloc(from.w * from.h * from.c, sizeof(float));

    // copia effettiva dei dati (pixel)
    memcpy(to.data, from.data, size * sizeof(float));
    
}
