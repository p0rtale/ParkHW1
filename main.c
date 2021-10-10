#include "roman_to_arabic.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_SIZE 20
#define MAX_ROMAN_NUMBER_LENGTH 15

char *read_string() {
    char *input_str = (char *)malloc(sizeof(char)*MAX_SIZE);
    if (!input_str) {
        printf("Error: memory not allocated\n");
        return NULL;
    }

    fgets(input_str, MAX_SIZE, stdin);
    if (ferror(stdin)) {
        printf("Error: input error\n");
        return NULL;
    }

    size_t len = strlen(input_str);
    if (len > MAX_ROMAN_NUMBER_LENGTH) {
        printf("Warning: maximum number length exceeded\n");
    }
    if (input_str[len - 1] == '\n') {
        input_str[len - 1] = '\0';
    }

    return input_str;
}

int main() {
    char *input_string = read_string();
    if (!input_string) {
        return -1;
    }

    int res = -1;
    if (translate_roman_to_arabic(input_string, &res)) {
        printf("Error: this is not a Roman number\n");
    } else {
        printf("%d\n", res);
    }

    free(input_string);

    return 0;
}
