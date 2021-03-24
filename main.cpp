#include <iostream>
#include <time.h>
#include "main.h"
#include "Bitmap.h"
#include "PerlinNoise.h"

int main (){
    PerlinNoise::generateNewPermutation(time(nullptr));

    // set this variable to name the output file
    char* imageFileName = (char*) "bitmapImage.bmp";

    // change these to change dimensions of output image
    height = 2160;
    width = 3840;
    image = new Bitmap(height,width,imageFileName);


    // use the following vector for grad mode
    // the image will feature a gradient from
    // colour1 to colour2 to colour3
    colour colours[3] = {
        {   // colour 1
            214,    // red
            2,      // green
            112     // blue
        },
        {   // colour 2
            155,    // red
            79,     // green
            150     // blue
        },
        {   // colour 3
            0,      // red
            56,     // green
            168     // blue
        }
    };

    // use the following structs for classic mode
    // to set the basic gradient from min to max
    colour max = {
        (unsigned char)214, // red
        (unsigned char)2,   // green
        (unsigned char)112  // blue
    };
    colour min = {
        (unsigned char)0,   // red
        (unsigned char)56,  // green
        (unsigned char)168  // blue
    };


    // to use a different mode, 
    // uncomment the desired mode 
    // and comment the others
    classicMode(max,min);
//  psychedelicMode();
//  gradMode(colours);
    image->generateBitmapImage();
    return 0;
}

void classicMode(colour max, colour min){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);

            // casting to unsigned char causes some weird voodoo to happen that makes the ripples and large blobs more common
            image->setPixel((unsigned char)(max.red*x+min.red), (unsigned char)(max.green*x+min.green), (unsigned char)(max.blue*x+min.blue), i, j);
        }
    }
}

void psychedelicMode(){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // generate three slightly offset slices
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

            // generate a gradient
            if(x < 0)
                interpolate(x/-5, colours[0], colours[1]);
            else
                interpolate(x/5, colours[1], colours[2]);
            image->setPixel(outColour.red, outColour.green, outColour.blue, i, j);
        }
    }
}

void interpolate(double val, colour colour1, colour colour2){
    outColour.red = colour1.red * (1.0 - val) + colour2.red * val;
    outColour.green = colour1.green * (1.0 - val) + colour2.green * val;
    outColour.blue = colour1.blue * (1.0 - val) + colour2.blue * val;
}