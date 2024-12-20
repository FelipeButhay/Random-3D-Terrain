#pragma once
#include "raylib.h"

struct LightSource{
    Vector3 pos;
    float intensity; // 0-1
    float decay; // 0-1
    Color color;
};

float resultantIntensity(Vector3 v1, Vector3 v2, Vector3 v3, LightSource& source);