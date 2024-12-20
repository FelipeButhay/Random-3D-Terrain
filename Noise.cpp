#include "raylib.h"
#include "Noise.h"

#include <iostream>
#include <vector>
#include <cmath>

float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

NoiseLayer::NoiseLayer(int nx, int ny){
    this->nx = nx;
    this->ny = ny;

    map.resize(nx+1, std::vector<Vector2>(ny+1));
    mapRd.resize(nx+1, std::vector<float>(ny+1));

    for(int i = 0; i<(nx+1); i++){
        for (int j = 0; j<(ny+1); j++){
            float angle = 2.0f * PI * (float)std::rand() / RAND_MAX;
            mapRd[i][j] = angle;
            map[i][j] = (Vector2){(float)cos(mapRd[i][j]), (float)sin(mapRd[i][j])};
        }
    }
}

float NoiseLayer::noise(float pointx, float pointy){ // ambos deben estar entre 0 y nx o ny respectivamente
    float dotProducts[2][2];
    float pointxDP = pointx - (int)pointx;
    float pointyDP = pointy - (int)pointy;
    dotProducts[0][0] = (map[(int)pointx  ][(int)pointy  ].x * (pointxDP    )) + (map[(int)pointx  ][(int)pointy  ].y * (pointyDP    ));
    dotProducts[1][0] = (map[(int)pointx+1][(int)pointy  ].x * (pointxDP - 1)) + (map[(int)pointx+1][(int)pointy  ].y * (pointyDP    ));
    dotProducts[0][1] = (map[(int)pointx  ][(int)pointy+1].x * (pointxDP    )) + (map[(int)pointx  ][(int)pointy+1].y * (pointyDP - 1));
    dotProducts[1][1] = (map[(int)pointx+1][(int)pointy+1].x * (pointxDP - 1)) + (map[(int)pointx+1][(int)pointy+1].y * (pointyDP - 1));

    float u = fade(pointxDP);
    float v = fade(pointyDP);

    float upInter = (1 - u)*dotProducts[0][0] + (u)*dotProducts[1][0];
    float dwInter = (1 - u)*dotProducts[0][1] + (u)*dotProducts[1][1];
    float fiInter = (1 - v)*upInter           + (v)*dwInter;

    return fiInter;
}

void NoiseLayer::rotateVectors(){
    for(int i = 0; i<(nx+1); i++){
        for (int j = 0; j<(ny+1); j++){
            mapRd[i][j] += (((float)std::rand() / RAND_MAX))*0.02f;
            map[i][j] = (Vector2){(float)cos(mapRd[i][j]), (float)sin(mapRd[i][j])};
        }
    }
}