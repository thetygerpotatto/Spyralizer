#ifndef PENDULUM_VEC
#define PENDULUM_VEC
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
    pendulum_vec();

    ~pendulum_vec();

    pendulum& operator[](size_t i);

    size_t size();

    void push_back(pendulum& p);

    void push_back(pendulum&& p);
    
    void pop_back();

    void rotate_pens();
private:
    void increase_size();
};

#endif // !PENDULUM_VEC
