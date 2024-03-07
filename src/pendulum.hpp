#ifndef PENDULUM
#define PENDULUM

#include <cmath>
#include <raylib.h>
#include <iostream>

class pendulum {
    bool is_origin = false;
    float angle = 0.0f;
    float magnitude = 0.0f;
    float rotation_rate = 0.0f;
    pendulum* father = nullptr;

public:
    Vector2 *base;
    Vector2 *head;

    pendulum() {

    }

    pendulum(pendulum &p) {
        is_origin = p.get_origin_status();
        angle = p.get_angle();
        magnitude = p.get_magnitude();
        rotation_rate = p.get_rotation_rate();
        father = p.get_father();
        
        if(is_origin) {
            base = new Vector2;
            *base = *p.base;
        } else {
            base = father->head;
        }
        head = new Vector2;
        *head = *p.head;
    }

    pendulum(pendulum &fa, float x, float y) {
        father = &fa;  
        base = father->head;
        head = new Vector2;
        head->x = x;
        head->y =y;
        magnitude = sqrtf(powf(head->x - base->x, 2)+ powf(head->y - base->y, 2));
        angle = asinf((head->x - base->x) / magnitude);
    }

    pendulum(Vector2 b, Vector2 h) {
        base = new Vector2;
        head = new Vector2;
        *base = b;
        *head = h;
        is_origin = true;

        magnitude = sqrtf(powf((h.x - b.x),2) + powf((h.y - b.y), 2));
        angle = acosf((h.x - b.x) / magnitude);
    }

    ~pendulum(){
        delete head;
        if(is_origin) {
            delete base;
        }
    }

    void SetRotationRate(float r) {
        rotation_rate = r;
    }



    void Rotate() {
        angle += rotation_rate;
        head->x = cosf(angle)*magnitude + base->x;
        head->y = sinf(angle)*magnitude + base->y;
    }

    bool get_origin_status() {
        return is_origin;
    }

    float get_angle() {
        return angle;
    }

    float get_magnitude() {
        return magnitude;
    }

    float get_rotation_rate() {
        return rotation_rate;
    }

    pendulum* get_father() {
        return father;
    }

    pendulum& operator=(pendulum p) {
        is_origin = p.get_origin_status();
        angle = p.get_angle();
        magnitude = p.get_magnitude();
        rotation_rate = p.get_rotation_rate();
        father = p.get_father();
        
        if(is_origin) {
            base = new Vector2;
            *base = *p.base;
        } else {
            base = father->head;
        }
        head = new Vector2;
        *head = *p.head;
        return *this;
    }

};

#endif // !PENDULUM
#define PENDULUM

