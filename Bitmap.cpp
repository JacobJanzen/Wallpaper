#include <fstream>
#include "Bitmap.h"

Bitmap::Bitmap(int h, int w, char *filename) : height(h), width(w), imageFileName(filename){
    fileHeader.resize(FILE_HEADER_SIZE);
    infoHeader.resize(INFO_HEADER_SIZE);
    image.resize(height*width*BYTES_PER_PIXEL);
    
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (((width * BYTES_PER_PIXEL) + ((4 - (width * BYTES_PER_PIXEL) % 4) % 4)) * height);
    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

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

void Bitmap::setPixel(unsigned char r, unsigned char g, unsigned char b, int y, int x){
    image[(y*width+x)*BYTES_PER_PIXEL + 2] = r;
    image[(y*width+x)*BYTES_PER_PIXEL + 1] = g;
    image[(y*width+x)*BYTES_PER_PIXEL + 0] = b;
}

void Bitmap::generateBitmapImage(){
    unsigned char padding[3] = {0, 0, 0};
    std::fstream file;
    file.open(imageFileName, std::fstream::out | std::ios::binary);
    file.write((const char *)(&(fileHeader[0])), FILE_HEADER_SIZE);
    file.write((const char *)(&(infoHeader[0])), INFO_HEADER_SIZE);
    for(int i = 0; i < height; i++)
        file.write((const char *)(&(image[i*width * BYTES_PER_PIXEL])), BYTES_PER_PIXEL * width);
    file.close();
}