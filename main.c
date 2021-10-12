#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roman_to_arabic.h"

#define READ_SUCCESS 0
#define READ_FAILURE 1

#define MAX_SIZE 20
#define MAX_ROMAN_NUMBER_LENGTH 15

int read_string(char *input_string) {
    fgets(input_string, MAX_SIZE, stdin);
    if (ferror(stdin)) {
        fprintf(stderr, "Error: input error\n");
        return READ_FAILURE;
    }

    size_t len = strlen(input_string);
    if (len > MAX_ROMAN_NUMBER_LENGTH) {
        fprintf(stderr, "Warning: maximum number length exceeded\n");
    }
    if (input_string[len - 1] == '\n') {
        input_string[len - 1] = '\0';
    }

    return READ_SUCCESS;
}

int main() {
    char *input_string = (char *)malloc(sizeof(char)*MAX_SIZE);
    if (!input_string) {
        fprintf(stderr, "Error: memory not allocated\n");
        return EXIT_FAILURE;
    }

    if (read_string(input_string)) {
        free(input_string);
        return EXIT_FAILURE;
    }

    int res = 0;
    if (translate_roman_to_arabic(input_string, &res)) {
        fprintf(stderr, "Error: this is not a Roman number\n");
    } else {
        printf("%d\n", res);
    }

    free(input_string);

    return EXIT_SUCCESS;
}
