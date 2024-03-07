#include <cmath>
#include <complex>
#include <cstddef>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "pendulum_vec.hpp"
#include "pendulum.hpp"


int main() {
    const int screen_widht = 1080;
    const int screen_height = 720;
    Vector2 offset = {screen_widht/2.0, screen_height/2.0};
    Vector2 origin = {0};

    Camera2D camera {0};
    camera.offset = offset;
    camera.target = origin;
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    
    pendulum_vec penvec;

    pendulum pen(origin, (Vector2){100, -100});
    pendulum pen2(pen, 270.0f, 77.0f);

    pen.SetRotationRate(PI/64);
    pen2.SetRotationRate(-PI/128);

    penvec.push_back(pen);
    penvec.push_back(pen2);
    
    

    InitWindow(screen_widht, screen_height, "Spyralizer");
    SetTargetFPS(120); 

    while (!WindowShouldClose()) {
        penvec.rotate_pens();
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground({BLACK});
        for (size_t i = 0; i < penvec.size(); ++i) {
            DrawLineV(*penvec[i].base, *penvec[i].head, {0x4E, 0xD9, 0xB5, 0xFF});
        }
        EndMode2D();
        EndDrawing();
    }
}
