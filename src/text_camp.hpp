#ifndef TEXT_CAMP
#define TEXT_CAMP

#include <cstddef>
#include <iostream>

class text_camp {
    
    size_t size;
    
public:

    int char_count = 0;
    char* text;

    text_camp(const int size) {
        text = new char[size+1];
        text[size] = '\0';
        for (size_t i = 0; i < size ; ++i) {
            text[i] = '\0';
        }
    }

    ~text_camp() {
        delete [] text;
    }
};

#endif // !TEXT_CAMP
