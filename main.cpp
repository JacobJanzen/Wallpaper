#include <time.h>
#include "Bitmap.h"
#include "PerlinNoise.h"

int main ()
{
    PerlinNoise::generateNewPermutation(time(nullptr));
    char* imageFileName = (char*) "bitmapImage.bmp";
    int height = 2160;
    int width = 3840;

    Bitmap *image = new Bitmap(height,width,imageFileName);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            image->setPixel(214*x,2*x + 56,112*x + 168, i, j);
        }
    }

    image->generateBitmapImage();
    return 0;
}