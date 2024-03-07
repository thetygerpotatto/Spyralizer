#ifndef PENDULUM_VEC
#define PENDULUM_VEC
#include <complex>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "pendulum.hpp"

class pendulum_vec {
    size_t pen_count;
    size_t capacity;
    size_t last_pen_idx;
    pendulum* pens = nullptr;
    
public:
    pendulum_vec() {
    pen_count = 0;
        capacity = 0;
    }

    pendulum& operator[](size_t i) {
        return pens[i];
    }

    size_t size() {
        return pen_count;
    }

    void push_back(pendulum& p) {
        increase_size();
        last_pen_idx = pen_count++;
        pens[last_pen_idx] = pendulum(p);
    }

    void rotate_pens() {
        for (size_t i = 0; i < size(); ++i) {
            pens[i].Rotate();
        }
    }
private:
    void increase_size() {
        if (capacity == 0) {
            capacity += 5;
            pens = static_cast<pendulum*>(malloc(sizeof(pendulum)*capacity));
        }
        if (pen_count + 1 == capacity && capacity != 0) {
            capacity += 5;
            pens = static_cast<pendulum*>(realloc(pens, capacity));
        }

    }
};

#endif // !PENDULUM_VEC
