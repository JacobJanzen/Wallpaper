#pragma once
#include <vector>
#define BYTES_PER_PIXEL 3 
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

class Bitmap{
private:
    int height, width;
    std::vector<unsigned char> image;
    std::vector<unsigned char> fileHeader;
    std::vector<unsigned char> infoHeader;
    char *imageFileName;
public:
    Bitmap(int h, int w, char *filename);
    void setPixel(unsigned char r, unsigned char g, unsigned char b, int y, int x);
    void generateBitmapImage();
};