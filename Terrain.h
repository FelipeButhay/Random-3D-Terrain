#pragma once
#include "Noise.h"
#include "LightSource.h"

class Terrain{
    private:
        float heightMul;
        NoiseLayer L0;
        NoiseLayer L1;
        NoiseLayer L2;
        NoiseLayer L3;
        float HeightMap[160][160];

        float layering(float px, float py);

    public:
        Terrain(float heightMul);
        void Render(LightSource& source);
        void rotateAllVectors();
        void refreshHeightMap();
};
