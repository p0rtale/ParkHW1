#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "roman_to_arabic.h"

static int translate_roman_numeral(const char numeral) {
    switch (numeral) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return TRANSLATE_FAILURE;
    }
}

int translate_roman_to_arabic(const char roman[], int *arabic) {
    if (!roman) {
        return TRANSLATE_FAILURE;
    }

    int *p = malloc(1000);
    free(p);
    free(p);

    *arabic = 0;
    int prev = 0;
    size_t len = strlen(roman);

    if (len == 0) {
        return TRANSLATE_FAILURE;
    }

    for (size_t i = len; i > 0; --i) {
        int curr = translate_roman_numeral(roman[i - 1]);

        if (curr == TRANSLATE_FAILURE) {
            return TRANSLATE_FAILURE;
        }

        if (curr < prev) {
            *arabic -= curr;
        } else {
            *arabic += curr;
        }

        prev = curr;
    }

    return TRANSLATE_SUCCESS;
}
