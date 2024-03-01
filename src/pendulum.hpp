#ifndef PENDULUM
#define PENDULUM

#include <cmath>
#include <raylib.h>

class pendulum {
    Vector2 *base;
    Vector2 *head;
    bool is_origin = false;
    float angle = 0.0f;
    float magnitude = 0.0f;
    float rotation_rate = 0.0f;
    pendulum* father = nullptr;

public:
    pendulum(pendulum &fa) {
        father = &fa;  
        base = father->head;
    }

    pendulum(Vector2 b, Vector2 h) {
        base = new Vector2;
        head = new Vector2;
        *base = b;
        *head = h;
        is_origin = true;

        magnitude = sqrtf(powf((h.x - b.x),2) + pow((h.y - b.y), 2));
        angle = acosf(h.x - b.x / magnitude);
    }

    ~pendulum(){
        delete head;
        if(is_origin) {
            delete base;
        }
    }

    

};

#endif // !PENDULUM
#define PENDULUM

