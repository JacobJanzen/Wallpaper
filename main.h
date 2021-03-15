typedef struct COLOUR{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} colour;

colour outColour;
void interpolate(double val, colour colour1, colour colour2);
