
#include <cstddef>
#include <raylib.h> 
#include <string>
#include "text_camp.hpp"

#ifndef INPUT_BOX
#define INPUT_BOX

#define MAX_INPUT_CHARS 10

struct input_box {
    Rectangle father;
    static size_t box_num;
    
    text_camp mag_camp = text_camp(MAX_INPUT_CHARS);
    text_camp angle_camp = text_camp(MAX_INPUT_CHARS);
        
    bool in_mag_box = false;
    bool in_angle_box = false;

    Rectangle i_box;
    Rectangle mag_box;
    Rectangle angle_box;
    Rectangle angle_sym;
    Rectangle mag_sym;
    float panning = 5.0f;

    input_box(Rectangle f) {
        this->father = f;

        i_box = {f.x+panning, f.y+panning+(f.height/5.0f*box_num), f.width-(panning*2.0f), (f.height-panning)/5.0f};
        mag_box = {i_box.x+i_box.width/4.0f+panning, i_box.y+panning, 3.0f*i_box.width/4.0f-(2.0f*panning), i_box.height/2.0f - (2.0f*panning)};
        angle_box = {i_box.x+i_box.width/4.0f+panning, (i_box.y+i_box.height/2.0f) + panning, 3.0f*i_box.width/4.0f-(2.0f*panning), i_box.height/2.0f -(2.0f*panning)};
        angle_sym = {i_box.x+panning, i_box.y+panning, i_box.width/4.0f-panning, i_box.height/2.0f - (2.0f*panning)};
        mag_sym = {i_box.x+panning, i_box.y+panning+i_box.height/2.0f, i_box.width/4.0f-panning, i_box.height/2.0f - (2.0f*panning)};
        ++box_num; 
    }

    input_box(const input_box & ib) {
        father = ib.father;
        i_box = ib.i_box;
        mag_box = ib.mag_box;
        angle_box = ib.angle_box;
        angle_sym = ib.angle_sym;
        mag_sym = ib.mag_sym;
        mag_camp = text_camp(ib.mag_camp);
        angle_camp = text_camp(ib.angle_camp);
    }
    
    input_box & operator=(const input_box& ib) {
        father = ib.father;
        i_box = ib.i_box;
        mag_box = ib.mag_box;
        angle_box = ib.angle_box;
        angle_sym = ib.angle_sym;
        mag_sym = ib.mag_sym;
        mag_camp = ib.mag_camp;
        angle_camp = ib.angle_camp;
        return *this;
    }

    float get_mag() {
        if (*mag_camp.text == '\0') {
            return 0;
        } else {
            return std::stof(mag_camp.text);
        }
    }
    
    float get_angle() {
        if (*angle_camp.text == '\0') {
            return 0;
        } else {
            return std::stof(angle_camp.text);
        }
    }

    
};

size_t input_box::box_num;

#endif // !INPUT_BOX

