#pragma once

class PerlinNoise{
private:
    static int p[512];
    static int permutation[];

    // Fade function as defined by Ken Perlin. This eases coordinate values
    // so that they will ease towards integral values. This ends up smoothing
    // the final output. 6t^5-15t^4+10t^3
    static double fade(double t);
    // Linear Interpolate
    static double lerp(double t, double a, double b);
    // Gradient
    static double grad(int hash, double x, double y, double z);
    static void initialize();
public:
    // generates the permutation to create the noise
    // must be called before any calls to perlin()
    static void generateNewPermutation(unsigned int seed);
    // return the value generated at (x,y,z)
    static double perlin(double x, double y, double z);
    
};