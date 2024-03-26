#ifndef TEXT_CAMP
#define TEXT_CAMP

#include <cstddef>
#include <cstring>
#include <iostream>

#define TEXT_CAMP_SIZE 10

class text_camp {
    
public:
    const size_t size = TEXT_CAMP_SIZE;
    int char_count = 0;
    char* text;

    text_camp() {
        text = new char[size+1];
        text[size] = '\0';
        for (size_t i = 0; i < size ; ++i) {
            text[i] = '\0';
        }
        text[char_count++] = '0';
    }

    text_camp(const text_camp& tc) {
        text = new char[size+1];
        *text = {0};
        text[size] = '\0';
        strcpy(text, tc.text);
    }

    text_camp& operator=(const text_camp& tc) {
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
