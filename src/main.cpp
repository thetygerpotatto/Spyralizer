#include <cmath>
#include <cstddef>
#include <iostream>
#include <raylib.h>
#include "pendulum_vec.hpp"
#include "pendulum.hpp"
#include "input_box.hpp"
#include "text_camp.hpp"
#include <stdlib.h>
#include <vector>

using std::vector;

void update_penvec(pendulum_vec& penvec, vector<input_box> &boxes);

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
    
    const size_t panning = 5;


    Rectangle adding_box = {screen_widht/4.0f*3.0f-(screen_widht/16.0f) - panning, (float)panning, screen_widht/16.0f, screen_widht/16.0f};
    Rectangle side_bar = {(screen_widht/4.0f)*3.0f,0,(screen_widht/4.0f),screen_height};

    input_box box1(side_bar);

    input_boxes.push_back(box1);

    pendulum_vec penvec;

    pendulum pen(origin, (Vector2){100, 0});

    bool input_mode = false;

    pen.SetRotationRate(PI/64);

    for(size_t i = 0; i < input_boxes.size(); ++i) {
        float m = input_boxes[i].get_mag();
        float a = (input_boxes[i].get_angle())*PI/180.0f;
        pendulum p = pendulum(origin, (Vector2){cosf(a)*m, sinf(a)*m});
        p.SetRotationRate(PI/180.0f);
        penvec.push_back(p);
    }

    InitWindow(screen_widht, screen_height, "Spyralizer");
    SetTargetFPS(60); 

    while (!WindowShouldClose()) { 

        penvec.rotate_pens();
        
        
        Vector2 mouse_cords = GetMousePosition();
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_cords, adding_box)) {
            input_box bbb(side_bar);
            input_boxes.push_back(bbb);
        }
        
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

        int key = GetCharPressed();
            
        for (input_box& box: input_boxes) {

            text_camp* camp = 0;

            if (box.in_mag_box) {
                camp = &box.mag_camp;
                update_penvec(penvec, input_boxes);
            }

            if (box.in_angle_box) {
                camp = &box.angle_camp;
                update_penvec(penvec, input_boxes);
            }

            while (key > 0 && camp) {
                if (key >= 48 && key <= 57 && camp->char_count <= 10) {
                    camp->text[camp->char_count++] = key;
                    camp->text[camp->char_count + 1] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && camp) {
                if (camp->char_count < 0) camp->char_count = 0;
                else camp->text[--camp->char_count] = '\0';
            }
        }

        // DRAWING
        BeginDrawing();
        ClearBackground({0x39,0x3a,0x41,0xff});
        // drawing side bar
        DrawRectangleRec(side_bar, {0x54,0x18,0x93, 0xAA});
        DrawRectangleRec(adding_box, {0xf0,0xf4,0xff, 0xAA});

        for (input_box& box : input_boxes) {
            DrawRectangleRec(box.i_box, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(box.mag_box, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(box.angle_box, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(box.angle_sym, {0xf0,0xf4,0xff, 0xAA});
            DrawRectangleRec(box.mag_sym, {0xf0,0xf4,0xff, 0xAA});
            DrawText(box.mag_camp.text, box.mag_box.x + 8.0f, box.mag_box.y + 5.0f, 28, GRAY);
            DrawText(box.angle_camp.text, box.angle_box.x + 8.0f, box.angle_box.y + 5.0f, 28, GRAY);

            if(box.in_mag_box) {
                DrawRectangleLinesEx(box.mag_box, 5, GRAY);
            }

            if(box.in_angle_box) {
                DrawRectangleLinesEx(box.angle_box, 5, GRAY);
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

void update_penvec(pendulum_vec& penvec, vector<input_box> &boxes){
    if(boxes.size() > penvec.size()) {
        for (size_t i = penvec.size(); i < boxes.size(); ++i) {
            float m = boxes[i].get_mag();
            float a = (boxes[i].get_angle())*PI/180.0f;
            pendulum p = pendulum((Vector2){cosf(a)*m, sinf(a)*m});
            p.SetRotationRate((PI/180.0f)*(float)(rand() % 10));
            penvec.push_back(p);
        }
    } 
    
    for (size_t i = 0; i < penvec.size(); ++i) {
        float m = boxes[i].get_mag();
        float a = boxes[i].get_angle();
        
        penvec[i].set_angle(a);
        penvec[i].set_magnitude(m);
        penvec[i].SetRotationRate(PI/180.0f*(float)(rand() % 10));
    }
}

