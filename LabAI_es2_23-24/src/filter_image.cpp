#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"

#define M_PI 3.14159265358979323846

// HW1 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image &im)
{
    float sum = 0.0f;

    // somma tutti i pixel
    for (int c = 0; c < im.c; ++c){
        for (int y = 0; y < im.h; ++y){
            for (int x = 0; x < im.w; ++x){
                sum += im(x, y, c);
            }
        }
    }

    if (sum == 0) return;

    for (int c = 0; c < im.c; ++c) {
        for (int y = 0; y < im.h; ++y) {
            for (int x = 0; x < im.w; ++x) {
                im(x, y, c) /= sum;
            }
        }
    }

}

// HW1 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w)
{
    assert(w % 2); // w needs to be odd

    Image filter(w, w, 1);
    for (int y = 0; y < w; ++y) {
        for (int x = 0; x < w; ++x) {
            filter(x, y, 0) = 1.0f; 
        }
    }

    l1_normalize(filter);
    return filter;
}

// HW1 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image &im, const Image &filter, bool preserve)
{
    assert(filter.c == 1);
    int ret_c = preserve ? im.c : 1;
    Image ret(im.w, im.h, ret_c);

    int fw = filter.w;
    int fh = filter.h;
    int fx = fw / 2;
    int fy = fh / 2;

    
    for (int c = 0; c < im.c; ++c) {
        for (int y = 0; y < im.h; ++y) {
            for (int x = 0; x < im.w; ++x) {
                float val = 0.0f;

                for (int j = 0; j < fh; ++j) {
                    for (int i = 0; i < fw; ++i) {
                        int ix = x + i - fx;
                        int iy = y + j - fy;
                        float image_val = im.clamped_pixel(ix, iy, c);
                        float filter_val = filter(i, j, 0);
                        val += image_val * filter_val;
                    }
                }

                if (preserve)
                    ret(x, y, c) = val;
                else
                    ret(x, y, 0) += val;
            }
        }
    }
    return ret;
}

// HW1 #2.2+ Fast convolution
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image_fast(const Image &im, const Image &filter, bool preserve)
{
    assert(filter.c == 1);
    Image ret;
    // This is the case when we need to use the function clamped_pixel(x,y,c).
    // Otherwise you'll have to manually check whether the filter goes out of bounds

    // TODO: Make sure you set the sizes of ret properly. Use ret=Image(w,h,c) to reset ret
    // TODO: Do the fast convolution operator. Remember to use Eigen for matrix operations
    NOT_IMPLEMENTED();

    // Make sure to return ret and not im. This is just a placeholder
    return im;
}

// HW1 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter()
{
   Image filter(3,3,1);

    filter(0,0,0) =  0; 
    filter(1,0,0) = -1; 
    filter(2,0,0) =  0;

    filter(0,1,0) = -1; 
    filter(1,1,0) =  4; 
    filter(2,1,0) = -1;

    filter(0,2,0) =  0; 
    filter(1,2,0) = -1; 
    filter(2,2,0) =  0;

    return filter;
}

// HW1 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter()
{
    Image filter (3,3,1);

    
    filter(0,0,0) =  0; 
    filter(1,0,0) = -1; 
    filter(2,0,0) =  0;

    filter(0,1,0) = -1; 
    filter(1,1,0) =  5; 
    filter(2,1,0) = -1;

    filter(0,2,0) =  0; 
    filter(1,2,0) = -1; 
    filter(2,2,0) =  0;

    return filter;
}

// HW1 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter()
{
    Image filter(3, 3, 1);

    filter(0,0,0) = -2; 
    filter(1,0,0) = -1; 
    filter(2,0,0) = 0;

    filter(0,1,0) = -1; 
    filter(1,1,0) =  1; 
    filter(2,1,0) = 1;

    filter(0,2,0) =  0; 
    filter(1,2,0) =  1; 
    filter(2,2,0) = 2;

    return filter;
}

// HW1 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma)
{
    /*
    Image filter(3, 3, 1);
    filter(0,0,0) = -2; filter(1,0,0) = -1; filter(2,0,0) = 0;
    filter(0,1,0) = -1; filter(1,1,0) =  1; filter(2,1,0) = 1;
    filter(0,2,0) =  0; filter(1,2,0) =  1; filter(2,2,0) = 2;
    return filter;
    */
   int size = ceil(6 * sigma);
    if (size % 2 == 0) size += 1;

    Image filter(size, size, 1);
    int center = size / 2;

    float sum = 0.0f;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int dx = x - center;
            int dy = y - center;
            float value = (1.0f / (2 * M_PI * sigma * sigma)) *
                          exp(-(dx * dx + dy * dy) / (2 * sigma * sigma));
            filter(x, y, 0) = value;
            sum += value;
        }
    }

    for (int y = 0; y < size; ++y)
        for (int x = 0; x < size; ++x)
            filter(x, y, 0) /= sum;

    return filter;
}

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image &a, const Image &b)
{
    assert(a.w == b.w && a.h == b.h && a.c == b.c); // assure images are the same size

    Image res(a.w, a.h, a.c);
    for (int c = 0; c < a.c; ++c) {
        for (int y = 0; y < a.h; ++y) {
            for (int x = 0; x < a.w; ++x) {
                res(x, y, c) = a(x, y, c) + b(x, y, c);
            }
        }
    }

    return res;
}

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image &a, const Image &b)
{
    assert(a.w == b.w && a.h == b.h && a.c == b.c); // assure images are the same size

    Image res(a.w, a.h, a.c);
    for (int c = 0; c < a.c; ++c) {
        for (int y = 0; y < a.h; ++y) {
            for (int x = 0; x < a.w; ++x) {
                res(x, y, c) = a(x, y, c) - b(x, y, c);
            }
        }
    }

    return res;
}

// HW1 #4.1
// returns basic GX filter
Image make_gx_filter()
{
    Image gx(3, 3, 1);
    gx(0, 0, 0) = -1; gx(1, 0, 0) = 0; gx(2, 0, 0) = 1;
    gx(0, 1, 0) = -2; gx(1, 1, 0) = 0; gx(2, 1, 0) = 2;
    gx(0, 2, 0) = -1; gx(1, 2, 0) = 0; gx(2, 2, 0) = 1;
    return gx;
}

// HW1 #4.1
// returns basic GY filter
Image make_gy_filter()
{
    Image gy(3, 3, 1);
    gy(0, 0, 0) = -1; gy(1, 0, 0) = -2; gy(2, 0, 0) = -1;
    gy(0, 1, 0) =  0; gy(1, 1, 0) =  0; gy(2, 1, 0) =  0;
    gy(0, 2, 0) =  1; gy(1, 2, 0) =  2; gy(2, 2, 0) =  1;
    return gy;
}

// HW1 #4.2
// Image& im: input image
void feature_normalize(Image &im)
{
    assert(im.w * im.h); // assure we have non-empty image

    float min_val = im.data[0];
    float max_val = im.data[0];

    for (int i = 0; i < im.w * im.h * im.c; ++i) {
        if (im.data[i] < min_val) min_val = im.data[i];
        if (im.data[i] > max_val) max_val = im.data[i];
    }

    float range = max_val - min_val;
    if (range == 0) {
        for (int i = 0; i < im.w * im.h * im.c; ++i) {
            im.data[i] = 0;
        }
    } else {
        for (int i = 0; i < im.w * im.h * im.c; ++i) {
            im.data[i] = (im.data[i] - min_val) / range;
        }
    }
}

// Normalizes features across all channels
void feature_normalize_total(Image &im)
{
    assert(im.w * im.h * im.c); // assure we have non-empty image

    int nc = im.c;
    im.c = 1;
    im.w *= nc;

    feature_normalize(im);

    im.w /= nc;
    im.c = nc;
}

// HW1 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image, Image> sobel_image(const Image &im)
{
    Image gx_filter = make_gx_filter();
    Image gy_filter = make_gy_filter();

    Image gx = convolve_image(im, gx_filter, false);
    Image gy = convolve_image(im, gy_filter, false);

    Image magnitude(im.w, im.h, 1);
    Image direction(im.w, im.h, 1);

    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float g_x = gx(x, y, 0);
            float g_y = gy(x, y, 0);

            magnitude(x, y, 0) = std::sqrt(g_x * g_x + g_y * g_y);
            direction(x, y, 0) = std::atan2(g_y, g_x);
        }
    }

    return { magnitude, direction };
}

// HW1 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image &im)
{

    auto [mag, dir] = sobel_image(im);
    feature_normalize(mag);

    // Normalizziamo la direzione: da [0, 2π] a [0,1]
    for (int i = 0; i < dir.w * dir.h * dir.c; ++i) {
        dir.data[i] = (dir.data[i] / (2 * M_PI)) + 0.5f;
    }

    // Blur leggero per migliorare l'estetica
    Image smooth = convolve_image(im, make_gaussian_filter(4), true);

    Image hsv(im.w, im.h, 3);
    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float h = dir(x, y, 0);     // Hue
            float s = mag(x, y, 0);     // Saturation
            float v = mag(x, y, 0);     // Value, o potresti combinare con smooth

            hsv(x, y, 0) = h;
            hsv(x, y, 1) = s;
            hsv(x, y, 2) = v;
        }
    }

    // Converti hsv in rgb in-place
    hsv_to_rgb(hsv);

    return hsv; // ora hsv è in realtà l'immagine RGB convertita
}

// HW1 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image &im, float sigma1, float sigma2)
{
    Image bf = im;
    int kernel_size = (int)(6 * sigma1 + 1);
    if (kernel_size % 2 == 0) kernel_size++;

    int k = kernel_size / 2;
    Image res(im.w, im.h, im.c);

    Image spatial_filter = make_gaussian_filter(sigma1);  // Gδ(i,j)

    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            for (int c = 0; c < im.c; ++c) {
                float sum_weights = 0.0f;
                float sum = 0.0f;

                float center_val = im.clamped_pixel(x, y, c);

                for (int j = -k; j <= k; ++j) {
                    for (int i = -k; i <= k; ++i) {
                        int xi = x + i;
                        int yj = y + j;

                        float neighbor_val = im.clamped_pixel(xi, yj, c);
                        float color_diff = center_val - neighbor_val;

                        float g_spatial = spatial_filter(i + k, j + k, 0);
                        float g_range = std::exp(-(color_diff * color_diff) / (2 * sigma2 * sigma2));

                        float weight = g_spatial * g_range;

                        sum_weights += weight;
                        sum += neighbor_val * weight;
                    }
                }

                res(x, y, c) = sum / sum_weights;
            }
        }
    }

    return res;
}

// HW1 #4.5+ Fast bilateral filter
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter_fast(const Image &im, float sigma1, float sigma2)
{
    Image bf = im;

    // TODO: Your fast bilateral code
    NOT_IMPLEMENTED();

    return bf;
}

// HM #5
//
float *compute_histogram(const Image &im, int ch, int num_bins)
{
    float *hist = (float *)malloc(sizeof(float) * num_bins);
    for (int i = 0; i < num_bins; ++i)
    {
        hist[i] = 0;
    }

    int total_pixels = im.w * im.h;

    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float val = im(x, y, ch);
            int bin = (int)(val * (num_bins - 1));
            bin = std::clamp(bin, 0, num_bins - 1);
            hist[bin] += 1.0f;
        }
    }

    for (int i = 0; i < num_bins; ++i)
        hist[i] /= total_pixels;

    return hist;
}

float *compute_CDF(float *hist, int num_bins)
{
    float *cdf = (float *)malloc(sizeof(float) * num_bins);

    cdf[0] = hist[0];

    for (int i = 1; i < num_bins; ++i)
        cdf[i] = cdf[i - 1] + hist[i];
    return cdf;
}

Image histogram_equalization_hsv(const Image &im, int num_bins)
{
    Image new_im(im);
    for (int c = 0; c < im.c; ++c) {
        float* hist = compute_histogram(im, c, num_bins);
        float* cdf = compute_CDF(hist, num_bins);

        // Ora per ogni pixel sostituisco con cdf(bin)
        for (int y = 0; y < im.h; ++y) {
            for (int x = 0; x < im.w; ++x) {
                float val = im(x, y, c);
                int bin = (int)(val * (num_bins - 1));
                bin = std::clamp(bin, 0, num_bins - 1);
                new_im(x, y, c) = cdf[bin];
            }
        }

        free(hist);
        free(cdf);
    }
    return new_im;
}

Image histogram_equalization_rgb(const Image &im, int num_bins)
{
    Image hsv_im(im);  
    rgb_to_hsv(hsv_im); 
    float* hist = compute_histogram(hsv_im, 2, num_bins); 
    float* cdf = compute_CDF(hist, num_bins);

    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float v = hsv_im(x, y, 2);
            int bin = (int)(v * (num_bins - 1));
            bin = std::clamp(bin, 0, num_bins - 1);
            hsv_im(x, y, 2) = cdf[bin];
        }
    }

    free(hist);
    free(cdf);
    
    hsv_to_rgb(hsv_im); // riconverti in-place
    return hsv_im;  

}

// HELPER MEMBER FXNS

void Image::feature_normalize(void) { ::feature_normalize(*this); }

void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }

void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image &a, const Image &b) { return sub_image(a, b); }

Image operator+(const Image &a, const Image &b) { return add_image(a, b); }
