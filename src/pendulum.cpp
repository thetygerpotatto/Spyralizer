#include "pendulum.hpp"

pendulum::pendulum(pendulum &p) {
    is_origin = p.get_origin_status();
    angle = p.get_angle();
    magnitude = p.get_magnitude();
    rotation_rate = p.get_rotation_rate();
    
    base = new Vector2;
    *base = *p.base;
    head = new Vector2;
    *head = *p.head;
}

pendulum::pendulum(pendulum &fa, float x, float y) {
    base = new Vector2;
    *base = *fa.head;
    head = new Vector2;
    head->x = x;
    head->y =y;
    is_origin = false;
    magnitude = sqrtf(powf(head->x - base->x, 2)+ powf(head->y - base->y, 2));
    angle = asinf((head->x - base->x) / magnitude);
}

pendulum::pendulum(Vector2 b, Vector2 h) {
    base = new Vector2;
    head = new Vector2;
    *base = b;
    *head = h;
    is_origin = true;

    magnitude = sqrtf(powf((h.x - b.x),2) + powf((h.y - b.y), 2));
    angle = acosf((h.x - b.x) / magnitude);
}

pendulum::~pendulum(){
    delete head;
    if(is_origin) {
        delete base;
    }
}

void pendulum::SetRotationRate(float r) {
    rotation_rate = r;
}



void pendulum::Rotate() {
    angle += rotation_rate;
    head->x = cosf(angle)*magnitude + base->x;
    head->y = sinf(angle)*magnitude + base->y;
}

const bool pendulum::get_origin_status() {
    return is_origin;
}

float pendulum::get_angle() {
    return angle;
}

float pendulum::get_magnitude() {
    return magnitude;
}

float pendulum::get_rotation_rate() {
    return rotation_rate;
}

pendulum& pendulum::operator=(pendulum p) {
    is_origin = p.get_origin_status();
    angle = p.get_angle();
    magnitude = p.get_magnitude();
    rotation_rate = p.get_rotation_rate();
    
    base = new Vector2;
    *base = *p.base;
    head = new Vector2;
    *head = *p.head;
    return *this;
}
