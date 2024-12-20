#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath>

float fade(float t);

class NoiseLayer{
    public:
        int nx, ny;
        std::vector<std::vector<Vector2>> map;
        std::vector<std::vector<float>> mapRd;

    NoiseLayer(int nx, int ny);

    float noise(float pointx, float pointy);
    void rotateVectors();
};