#include <cmath>
#include <complex>
#include <iostream>
#include <raylib.h>
#include <raymath.h>


int main() {
    const int screen_widht = 1080;
    const int screen_height = 720;
    Vector2 offset = {screen_widht/2.0, screen_height/2.0};

    float tita = 0.0f;
    float tita2 = 0.0f;
    float norm = 100.0f;
    float norm2 = 200.0f;

    Vector2 origin = {0, 0};
    Vector2 CompPoint = {0};
    Vector2 SeccondCompPoint = {0};

    Camera2D camera {0};
    camera.offset = offset;
    camera.target = origin;
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    

    InitWindow(screen_widht, screen_height, "Spyralizer");
    SetTargetFPS(120); 

    while (!WindowShouldClose()) {

        CompPoint = {norm*sinf(tita), norm*cosf(tita)};
        SeccondCompPoint = {CompPoint.x + norm2*sinf(tita2), CompPoint.y + norm2*cosf(tita2)};

        tita += PI/180.0f;
        tita2 -= PI/180.0f;
        
        
        BeginDrawing();
        BeginMode2D(camera);
        //ClearBackground({BLACK});
        DrawLineV(origin, CompPoint, {0x4E, 0xD9, 0xB5, BLEND_ADD_COLORS});
        DrawLineV(CompPoint, SeccondCompPoint,{0x4E, 0xD9, 0xB5, BLEND_ADD_COLORS});
        EndMode2D();
        EndDrawing();
    }
}
