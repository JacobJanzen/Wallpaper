#include <fstream>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "PerlinNoise.h"

int main ()
{
    PerlinNoise::generateNewPermutation(time(nullptr));
    int height = 2160;
    int width = 3840;
    std::vector<unsigned char> image(height*width*BYTES_PER_PIXEL);
    char* imageFileName = (char*) "bitmapImage.bmp";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double x = PerlinNoise::perlin((double)i/height,(double)j/width,0);
            image[(i*width+j)*BYTES_PER_PIXEL + 2] = (unsigned char) ( 214*x + 0 );             ///red
            image[(i*width+j)*BYTES_PER_PIXEL + 1] = (unsigned char) ( 2*x + 56 );             ///green
            image[(i*width+j)*BYTES_PER_PIXEL + 0] = (unsigned char) ( 112*x + 168 );             ///blue
        }
    }

    generateBitmapImage(image, height, width, imageFileName);
    return 0;
}


void generateBitmapImage (std::vector<unsigned char> image, int height, int width, char* imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    std::fstream file;

    file.open(imageFileName, std::fstream::out | std::ios::binary);

    unsigned char* fileHeader = createBitmapFileHeader(height, stride);
    file.write((const char *)fileHeader, FILE_HEADER_SIZE);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width);
    file.write((const char *)infoHeader, INFO_HEADER_SIZE);

    for(int i = 0; i < height; i++){
        file.write((const char *)(&(image[i*widthInBytes])), BYTES_PER_PIXEL * width);
    }

    file.close();
}

unsigned char* createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

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

    return infoHeader;
}