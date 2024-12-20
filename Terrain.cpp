#include "Terrain.h"
#include "math.h"
#include "LightSource.h"

#define initNoise 10

Terrain::Terrain(float height) : 
    L0(initNoise, initNoise), L1(initNoise*2, initNoise*2), L2(initNoise*4, initNoise*4), L3(initNoise*8, initNoise*8)
{
    this->heightMul = height;
    for (int i = 0; i<160; i++){
        for (int j = 0; j<160; j++){
            this->HeightMap[i][j] = layering(i/10.0f, j/10.0f)*heightMul;
        }
    }
}

float Terrain::layering(float px, float py){
    float LayerSum = L0.noise(px/(160/(float)L0.nx), py/(160/(float)L0.ny))/1.0f
                   + L1.noise(px/(160/(float)L1.nx), py/(160/(float)L1.ny))/2.0f 
                   + L2.noise(px/(160/(float)L2.nx), py/(160/(float)L2.ny))/4.0f 
                   + L3.noise(px/(160/(float)L3.nx), py/(160/(float)L3.ny))/8.0f;
    return LayerSum;
}

void Terrain::Render(LightSource& source){
    for (int i = 0; i<159; i++){
        for (int j = 0; j<159; j++){
            float d1 = (HeightMap[i  ][j  ] - HeightMap[i+1][j+1]) * (HeightMap[i  ][j  ] - HeightMap[i+1][j+1]);
            float d2 = (HeightMap[i+1][j  ] - HeightMap[i  ][j+1]) * (HeightMap[i+1][j  ] - HeightMap[i  ][j+1]);

            Vector3 v00 = {(float)(i  ), HeightMap[i  ][j  ], (float)(j  )};
            Vector3 v10 = {(float)(i+1), HeightMap[i+1][j  ], (float)(j  )};
            Vector3 v01 = {(float)(i  ), HeightMap[i  ][j+1], (float)(j+1)};
            Vector3 v11 = {(float)(i+1), HeightMap[i+1][j+1], (float)(j+1)};

            Color surfaceColor;
            if                                 ( v00.y < -heightMul*0.08f) surfaceColor = {120, 120, 120, 255};
            else if (-heightMul*0.08f < v00.y && v00.y <  heightMul*0.03f) surfaceColor = {255, 224,   0, 255};
            else if ( heightMul*0.03f < v00.y && v00.y <  heightMul*0.35f) surfaceColor = {  0, 255,   0, 255};
            else if ( heightMul*0.35f < v00.y && v00.y <  heightMul*0.50f) surfaceColor = {120, 120, 120, 255};
            else if ( heightMul*0.50f < v00.y)                             surfaceColor = {240, 240, 240, 255}; 
            
            if (d1 > d2){
                DrawTriangle3D(v00, v11, v10, (Color){
                    (unsigned char)(surfaceColor.r * resultantIntensity(v00, v11, v10, source)),
                    (unsigned char)(surfaceColor.g * resultantIntensity(v00, v11, v10, source)),
                    (unsigned char)(surfaceColor.b * resultantIntensity(v00, v11, v10, source)),
                    (unsigned char)(surfaceColor.a)});
                DrawTriangle3D(v00, v01, v11, (Color){
                    (unsigned char)(surfaceColor.r * resultantIntensity(v00, v01, v11, source)),
                    (unsigned char)(surfaceColor.g * resultantIntensity(v00, v01, v11, source)),
                    (unsigned char)(surfaceColor.b * resultantIntensity(v00, v01, v11, source)),
                    (unsigned char)(surfaceColor.a)});
            } else {
                DrawTriangle3D(v00, v01, v10, (Color){
                    (unsigned char)(surfaceColor.r * resultantIntensity(v00, v01, v10, source)),
                    (unsigned char)(surfaceColor.g * resultantIntensity(v00, v01, v10, source)),
                    (unsigned char)(surfaceColor.b * resultantIntensity(v00, v01, v10, source)),
                    (unsigned char)(surfaceColor.a)});
                DrawTriangle3D(v01, v11, v10, (Color){
                    (unsigned char)(surfaceColor.r * resultantIntensity(v01, v11, v10, source)),
                    (unsigned char)(surfaceColor.g * resultantIntensity(v01, v11, v10, source)),
                    (unsigned char)(surfaceColor.b * resultantIntensity(v01, v11, v10, source)),
                    (unsigned char)(surfaceColor.a)});
            }
        }
    }
}

void Terrain::rotateAllVectors(){
    L0.rotateVectors();
    L1.rotateVectors();
    L2.rotateVectors();
    L3.rotateVectors();
}

void Terrain::refreshHeightMap(){
    for (int i = 0; i<160; i++){
        for (int j = 0; j<160; j++){
            this->HeightMap[i][j] = layering(i/10.0f, j/10.0f)*heightMul;
        }
    }
}