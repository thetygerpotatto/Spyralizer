#ifndef TEXT_CAMP
#define TEXT_CAMP

#include <cstddef>
#include <cstring>
#include <iostream>

class text_camp {
    
public:
    size_t size;
    int char_count = 0;
    char* text;

    text_camp(const int size) {
        this->size = size;
        text = new char[size+1];
        text[size] = '\0';
        for (size_t i = 0; i < size ; ++i) {
            text[i] = '\0';
        }
        text[char_count++] = '0';
    }

    text_camp(const text_camp& tc) {
        size = tc.size; char_count = tc.char_count;
        text = new char[size+1];
        *text = {0};
        text[size] = '\0';
        strcpy(text, tc.text);
    }

    text_camp& operator=(const text_camp& tc) {
        size = tc.size; char_count = tc.char_count;
        text = new char[size+1];
        *text = {0};
        text[size] = '\0';
        strcpy(text, tc.text);
        return *this;
    }

    ~text_camp() {
        delete [] text;
    }
};

#endif // !TEXT_CAMP
