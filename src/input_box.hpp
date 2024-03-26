
#include <cstddef>
#include <raylib.h> 
#include <string>
#include "text_camp.hpp"

#ifndef INPUT_BOX
#define INPUT_BOX

#define MAX_INPUT_CHARS 10
#define TEXT_CAMPS 3

enum camp_index {
    MAG  = 0, ANGLE, ROT
};

struct input_box {
    Rectangle father;
    static size_t box_num;
    text_camp text_camps[3];
    bool in_box[TEXT_CAMPS] = {0};
    Rectangle i_box;
    Rectangle camp_boxes[TEXT_CAMPS];
    Rectangle sym_boxes[TEXT_CAMPS];
    float panning = 4.0f;
    const size_t text_camps_num = TEXT_CAMPS;

    input_box(Rectangle f) {
        this->father = f;

        i_box = {f.x+panning,
                f.y+panning+(f.height/5.0f*box_num),
                f.width-(panning*2.0f),
                (f.height-panning)/5.0f - 4.0f};
        
        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            camp_boxes[i] = { i_box.x+i_box.width/4.0f+panning,
                            i_box.height/3.0f*((float)i) + i_box.y+panning,
                            3.0f*i_box.width/4.0f-(2.0f*panning),
                            i_box.height/3.0f - (2.0f*panning)};
        }

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            sym_boxes[i] = {i_box.x+panning,
                    i_box.height/3.0f*((float)i) + i_box.y+panning,
                    i_box.width/4.0f-panning,
                    i_box.height/3.0f - (2.0f*panning)};
        }
        ++box_num; 
    }

    input_box(const input_box & ib) {
        father = ib.father;
        i_box = ib.i_box;

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            camp_boxes[i] = ib.camp_boxes[i]; 
        }

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            sym_boxes[i] = ib.sym_boxes[i]; 
        }

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            text_camps[i] = text_camp(ib.text_camps[i]); 
        }
    } 

    ~input_box() {
    }
    
    input_box & operator=(const input_box& ib) {
        father = ib.father;
        i_box = ib.i_box;

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            camp_boxes[i] = ib.camp_boxes[i]; 
        }

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            sym_boxes[i] = ib.sym_boxes[i]; 
        }

        for (size_t i = 0; i < TEXT_CAMPS; ++i) {
            text_camps[i] = text_camp(ib.text_camps[i]); 
        }
        return *this;
    }

    float get_camp_value(camp_index i) {
        if (*text_camps[i].text == '\0') {
            return 0;
        } else {
            return std::stof(text_camps[i].text);
        }
    }
    
};

size_t input_box::box_num;

#endif // !INPUT_BOX

