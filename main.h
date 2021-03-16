#include <vector>
class Bitmap;

typedef struct COLOUR{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} colour;

Bitmap *image;
int height, width;
colour outColour;
void gradMode(colour colours[3]);
void psychedelicMode();
void classicMode(colour max, colour min);
void interpolate(double val, colour colour1, colour colour2);
