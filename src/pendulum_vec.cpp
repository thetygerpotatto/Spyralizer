#include "pendulum_vec.hpp"


pendulum_vec::pendulum_vec() {
    pen_count = 0;
    capacity = 0;
}

pendulum_vec::~pendulum_vec() {
    delete [] pens;
}

 pendulum& pendulum_vec::operator[](size_t i) {
    return pens[i];
}

size_t pendulum_vec::size() {
    return pen_count;
}

void pendulum_vec::push_back(pendulum& p) {
    increase_size();
    last_pen_idx = pen_count++;
    pens[last_pen_idx] = p;

    if (last_pen_idx != 0) {
        pens[last_pen_idx].base = pens[last_pen_idx-1].head;
    }
}

void pendulum_vec::push_back(pendulum&& p) {
    increase_size();
    last_pen_idx = pen_count++;
    pens[last_pen_idx] = p;

    if (last_pen_idx != 0) {
        pens[last_pen_idx].base = pens[last_pen_idx-1].head;
    }
}

void pendulum_vec::pop_back() {
    pens[last_pen_idx--]  = 0;
    --pen_count;
}

void pendulum_vec::rotate_pens() {
    for (size_t i = 0; i < size(); ++i) {
        pens[i].Rotate();
    }
}

void pendulum_vec::increase_size() {
    if (capacity == 0) {
        capacity += 5;
        pens = new pendulum[capacity];
    }
    if (pen_count + 1 == capacity && capacity != 0) {
        capacity += 5;
        pens = new(pens) pendulum[capacity];
    }

}
