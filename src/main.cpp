#include <cstddef>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "pendulum_vec.hpp"
#include "pendulum.hpp"
#include "input_box.hpp"
#include <vector>

using std::vector;

int main() {
    const int screen_widht = 1080;
    const int screen_height = 720;
    Vector2 offset = {3.0f*screen_widht/4.0f/2.0f, screen_height/2.0f};
    Vector2 origin = {0};

    vector<input_box> input_boxes;

    Camera2D camera {0};
    camera.offset = offset;
    camera.target = origin;
    camera.zoom = 0.7f; 
    camera.rotation = 0.0f;
    
    size_t panning = 5;


    Rectangle adding_box = {screen_widht/4.0f*3.0f-(screen_widht/16.0f) - panning, (float)panning, screen_widht/16.0f, screen_widht/16.0f};
    Rectangle side_bar = {(screen_widht/4.0f)*3.0f,0,(screen_widht/4.0f),screen_height};

    input_box box1(side_bar);
    input_boxes.push_back(box1);

    pendulum_vec penvec;

    pendulum pen(origin, (Vector2){100, -100});
    pendulum pen2(pen, 270.0f, 77.0f);
    pendulum pen3((Vector2){0.0}, (Vector2){0,100});

    bool input_mode = false;

    pen.SetRotationRate(PI/64);
    pen2.SetRotationRate(-PI/32);
    pen3.SetRotationRate(PI/16);

    penvec.push_back(pen);
    penvec.push_back(pen2);
    penvec.push_back(pen3);
 

    InitWindow(screen_widht, screen_height, "Spyralizer");
    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
        penvec.rotate_pens();
        
        
        Vector2 mouse_cords = GetMousePosition();
        
        for (input_box& box : input_boxes) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_cords, box.mag_box)) {
                box.in_mag_box = true;
            } 
            else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                box.in_mag_box = false;
            }
            
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_cords, box.angle_box)) {
                box.in_angle_box = true;
            }
            else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                box.in_angle_box = false;
            }
        }

        
        // DRAWING
        BeginDrawing();
        ClearBackground({0x39,0x3a,0x41,0xff});
        // drawing side bar
        DrawRectangleRec(side_bar, {0x54,0x18,0x93, 0xAA});
        DrawRectangleRec(adding_box, {0xf0,0xf4,0xff, 0xAA});

        for (size_t i = 0; i < input_boxes.size(); ++i) {
            DrawRectangleRec(input_boxes[i].i_box, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(input_boxes[i].mag_box, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(input_boxes[i].angle_box, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(input_boxes[i].angle_sym, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(input_boxes[i].mag_sym, {0xf0,0xf4,0xff, 0xAA});

            if(input_boxes[i].in_mag_box) {
                DrawRectangleLinesEx(input_boxes[i].mag_box, 5, GRAY);
            }

            if(input_boxes[i].in_angle_box) {
                DrawRectangleLinesEx(input_boxes[i].angle_box, 5, GRAY);
            }            
        }


        BeginMode2D(camera);
        // Draw UI


        // Draw pendulums
        for (size_t i = 0; i < penvec.size(); ++i) {
            DrawLineV(*penvec[i].base, *penvec[i].head, {0x4E, 0xD9, 0xB5, 0xFF});
        }
        DrawCircleV(*penvec[penvec.size()-1].head, 10.0f, {0xff, 0xff, 0xff, 0xff});
        EndMode2D();
        EndDrawing();
    }
}
