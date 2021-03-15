#pragma once
#include <vector>
#define BYTES_PER_PIXEL 3 /// red, green, & blue
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

int height, width;
std::vector<unsigned char> image;
void setPixel(unsigned char red, unsigned char green, unsigned char blue, int y, int x);
void generateBitmapImage(int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);