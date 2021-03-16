#include <iostream>
#include <time.h>
#include "main.h"
#include "Bitmap.h"
#include "PerlinNoise.h"

int main (){
    PerlinNoise::generateNewPermutation(time(nullptr));
    char* imageFileName = (char*) "bitmapImage.bmp";
    height = 2160;
    width = 3840;
    image = new Bitmap(height,width,imageFileName);
    colour colours[3] = {
        {214,2,112},
        {155,79,150},
        {0,56,168}
    };
    gradMode(colours);
    image->generateBitmapImage();
    return 0;
}

void classicMode(colour max, colour min){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            image->setPixel(max.red*x+min.red, max.green*x+min.green, max.blue*x+min.blue, i, j);
        }
    }
}

void psychedelicMode(){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            double y = PerlinNoise::perlin((double)i/height,(double)j/width,1.0/3);
            double z = PerlinNoise::perlin((double)i/height,(double)j/width,2.0/3);
            image->setPixel(255*x, 255*y, 255*z, i, j);
        }
    }
}

void gradMode(colour colours[3]){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            if(x < 0)
                interpolate(x/-2, colours[0], colours[1]);
            else
                interpolate(x/2, colours[1], colours[2]);
            image->setPixel(outColour.red, outColour.green, outColour.blue, i, j);
        }
    }
}

void interpolate(double val, colour colour1, colour colour2){
    outColour.red = colour1.red * (1.0 - val) + colour2.red * val;
    outColour.green = colour1.green * (1.0 - val) + colour2.green * val;
    outColour.blue = colour1.blue * (1.0 - val) + colour2.blue * val;
}