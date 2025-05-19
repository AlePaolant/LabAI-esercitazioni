#include "../image.h"
#include "../utils.h"

#include <string>

using namespace std;

#include "../image.h"
#include "../utils.h"

// Test per get_pixel con coordinate normali
void test_clamped_pixel_inside() {
    Image im = load_image("data/dots.png");

    TEST(within_eps(0, im.clamped_pixel(0, 0, 0)));
    TEST(within_eps(1, im.clamped_pixel(1, 0, 1)));
    TEST(within_eps(0, im.clamped_pixel(2, 0, 1)));
}

// Test per clamped_pixel con coordinate fuori dai bordi
void test_clamped_pixel_outside() {
    Image im = load_image("data/dots.png");

    // coordinate negative
    TEST(within_eps(im.clamped_pixel(-1, -1, 0), im.clamped_pixel(0, 0, 0)));

    // coordinate troppo grandi
    TEST(within_eps(im.clamped_pixel(1000, 1000, 2), im.clamped_pixel(im.w - 1, im.h - 1, 2)));
}

// Test per set_pixel e verifica con confronto immagine
void test_set_pixel_against_reference() {
    Image im = load_image("data/dots.png");
    Image d(4, 2, 3);

    d.set_pixel(0,0,0,0); d.set_pixel(0,0,1,0); d.set_pixel(0,0,2,0);
    d.set_pixel(1,0,0,1); d.set_pixel(1,0,1,1); d.set_pixel(1,0,2,1);
    d.set_pixel(2,0,0,1); d.set_pixel(2,0,1,0); d.set_pixel(2,0,2,0);
    d.set_pixel(3,0,0,1); d.set_pixel(3,0,1,1); d.set_pixel(3,0,2,0);

    d.set_pixel(0,1,0,0); d.set_pixel(0,1,1,1); d.set_pixel(0,1,2,0);
    d.set_pixel(1,1,0,0); d.set_pixel(1,1,1,1); d.set_pixel(1,1,2,1);
    d.set_pixel(2,1,0,0); d.set_pixel(2,1,1,0); d.set_pixel(2,1,2,1);
    d.set_pixel(3,1,0,1); d.set_pixel(3,1,1,0); d.set_pixel(3,1,2,1);

    TEST(same_image(im, d));
}

// Test pratico di scrittura su canale rosso
void test_manual_set_red_channel_to_zero() {
    Image im2 = load_image("data/dog.jpg");

    for (int i = 0; i < im2.w; i++)
        for (int j = 0; j < im2.h; j++)
            im2(i, j, 0) = 0;

    im2.save_image("output/set_pixel_result");
}

void run_tests() {
    test_clamped_pixel_inside();
    test_clamped_pixel_outside();
    test_set_pixel_against_reference();
    test_manual_set_red_channel_to_zero();

    printf("%d tests, %d passed, %d failed\n", tests_total, tests_total - tests_fail, tests_fail);
}

int main() {
    run_tests();
    return 0;
}