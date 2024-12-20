#include "LightSource.h"
#include "raylib.h"
#include <cmath>

float Vector3DotProduct(Vector3 v, Vector3 u){
    return v.x*u.x + v.y*u.y + v.z*u.z;
}

Vector3 NormalizeVector(Vector3 v){
    float module = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
    v.x /= module;
    v.y /= module;
    v.z /= module;
    return v;
}

Vector3 crossProduct(Vector3 u, Vector3 v) {
    return {
        u.y * v.z - u.z * v.y, // Componente x
        u.z * v.x - u.x * v.z, // Componente y
        u.x * v.y - u.y * v.x  // Componente z
    };
}

float resultantIntensity(Vector3 v1, Vector3 v2, Vector3 v3, LightSource& source){
    Vector3 polygonAVG, LightToPolygon;

    v1.x -= v3.x;
    v1.y -= v3.y;
    v1.z -= v3.z;

    v2.x -= v3.x;
    v2.y -= v3.y;
    v2.z -= v3.z;

    polygonAVG = crossProduct(v1, v2);
    
    LightToPolygon.x = source.pos.x - (v1.x + v2.x + v3.x)/3.0f;
    LightToPolygon.y = source.pos.y - (v1.y + v2.y + v3.y)/3.0f;
    LightToPolygon.z = source.pos.z - (v1.z + v2.z + v3.z)/3.0f;

    //float distance = sqrt(pow(LightToPolygon.x, 2) + pow(LightToPolygon.y, 2) + pow(LightToPolygon.z, 2));

    polygonAVG = NormalizeVector(polygonAVG);
    LightToPolygon = NormalizeVector(LightToPolygon);

    float dp = Vector3DotProduct(polygonAVG, LightToPolygon);
    float surfaceLit = dp < 0 ? 0 : dp;

    return surfaceLit * source.intensity;
}