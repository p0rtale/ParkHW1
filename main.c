#include "roman_to_arabic.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_SIZE 20

char *read_string(FILE *fp) {
    char *input_str = (char *)malloc(sizeof(char)*MAX_SIZE);
    if (!input_str) {
        return NULL;
    }

    fgets(input_str, MAX_SIZE, fp);

    size_t len = strlen(input_str);
    if (input_str[len - 1] == '\n') {
        input_str[len - 1] = '\0';
    }

    return input_str;
}

int main() {
    char *input_string = read_string(stdin);
    if (!input_string) {
        return -1;
    }

    int res = -1;
    translate_roman_to_arabic(input_string, &res);

    printf("%d\n", res);

    free(input_string);

    return 0;
}
