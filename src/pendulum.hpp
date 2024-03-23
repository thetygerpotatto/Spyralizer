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

public:
    Vector2 *base;
    Vector2 *head;

    pendulum() {

    }

    pendulum(pendulum &p);

    pendulum(pendulum &fa, float x, float y);

    pendulum(Vector2 b, Vector2 h);

    pendulum(Vector2 h, bool origin);

    pendulum(Vector2 h);

    ~pendulum();

    void SetRotationRate(float r);

    void set_magnitude(float m);

    void set_angle(float a);

    void Rotate();

    const bool get_origin_status();

    void set_origin_status(bool origin);

    float get_angle();

    float get_magnitude(); 

    float get_rotation_rate();

    pendulum& operator=(pendulum p); 
};




#endif // !PENDULUM
#define PENDULUM
