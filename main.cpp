#include <fstream>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "PerlinNoise.h"

int main ()
{
    PerlinNoise::generateNewPermutation(time(nullptr));
    height = 2160;
    width = 3840;
    fileHeader.resize(FILE_HEADER_SIZE);
    infoHeader.resize(INFO_HEADER_SIZE);
    image.resize(height*width*BYTES_PER_PIXEL);
    char* imageFileName = (char*) "bitmapImage.bmp";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            setPixel(214*x,2*x + 56,112*x + 168, i, j);
        }
    }

    generateBitmapImage(height, width, imageFileName);
    return 0;
}

void setPixel(unsigned char red, unsigned char green, unsigned char blue, int y, int x){
    image[(y*width+x)*BYTES_PER_PIXEL + 2] = red;
    image[(y*width+x)*BYTES_PER_PIXEL + 1] = green;
    image[(y*width+x)*BYTES_PER_PIXEL + 0] = blue;
}


void generateBitmapImage (int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    std::fstream file;

    file.open(imageFileName, std::fstream::out | std::ios::binary);

    createBitmapFileHeader(height, stride);
    file.write((const char *)(&(fileHeader[0])), FILE_HEADER_SIZE);

    createBitmapInfoHeader(height, width);
    file.write((const char *)(&(infoHeader[0])), INFO_HEADER_SIZE);

    for(int i = 0; i < height; i++){
        file.write((const char *)(&(image[i*widthInBytes])), BYTES_PER_PIXEL * width);
    }

    file.close();
}

void createBitmapFileHeader (int height, int stride){
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
}

void createBitmapInfoHeader (int height, int width){
    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);
}