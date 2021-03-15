#include <iostream>
#include <time.h>
#include "main.h"
#include "Bitmap.h"
#include "PerlinNoise.h"

int main (){
    PerlinNoise::generateNewPermutation(time(nullptr));
    char* imageFileName = (char*) "bitmapImage.bmp";
    int height = 2160;
    int width = 3840;

    colour col1 = {214, 2, 112};
    colour col2 = {155, 79, 150};
    colour col3 = {0, 56, 168};

    Bitmap *image = new Bitmap(height,width,imageFileName);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            if(x < .5)
                interpolate(x*2, col1, col2);
            else
                interpolate((x-.5)*2, col2, col3);
            image->setPixel(outColour.red, outColour.green, outColour.blue, i, j);
        }
    }

    image->generateBitmapImage();
    return 0;
}

void interpolate(double val, colour colour1, colour colour2){
    outColour.red = colour1.red * (1.0 - val) + colour2.red * val;
    outColour.green = colour1.green * (1.0 - val) + colour2.green * val;
    outColour.blue = colour1.blue * (1.0 - val) + colour2.blue * val;
}