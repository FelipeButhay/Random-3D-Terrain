#include "raylib.h"
#include "Terrain.h"
#include "LightSource.h"

int main() {
    InitWindow(1600, 900, "Modo 3D con Raylib");
    SetTargetFPS(60);
    
    Camera camera = {0};
    camera.position = {60.0f, 150.0f, 60.0f};
    camera.target = {80.0f, 0.0f, 80.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Terrain terrain(120.0f);
    
    LightSource source = {0};
    source.intensity = 1.0f;
    source.decay = 0;
    source.color = WHITE;
    source.pos = {80.0f, 1000.0f, 80.0f};

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        // DESCOMENTAR PARA QUE EL TERRENO SE MUEVA
        terrain.rotateAllVectors();
        terrain.refreshHeightMap();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                terrain.Render(source);
                DrawPlane({80.0f, 0.0f, 80.0f}, {160.0f, 160.0f}, (Color){63, 168, 220, 100});
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
