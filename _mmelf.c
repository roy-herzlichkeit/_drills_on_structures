#include <stdio.h>
#include <stdlib.h>

void encode(char *str) {
    int keys[4] = {11, 17, 19, 23};
    int i = 0, j = 0;
    for (char c = 'z'; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') 
            c = 'a';
        else if (str[i] >= 'A' && str[i] <= 'Z') 
            c = 'A';
        if (c != 'z')
            str[i] = (char)((((((str[i] - c + 1) * keys[(j++) % 3]) % 26) + 25) % 26) + c);
        c = 'z';
    }
}

void decode(char *str) {
    int keys[4] = {19, 23, 11, 17};
    int i = 0, j = 0;
    for (char c = 'z'; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') 
            c = 'a';
        else if (str[i] >= 'A' && str[i] <= 'Z') 
            c = 'A';
        if (c != 'z')
            str[i] = (char)((((((str[i] - c + 1) * keys[(j++) % 3]) % 26) + 25) % 26) + c);
        c = 'z';
    }
}

int main(void) {
    printf("S = ");
    char *s = (char*)calloc(128, sizeof *s);
    fgets(s, 100, stdin);
    encode(s);
    printf("T = %s", s);
    decode(s);
    printf("S' = %s\n", s);
    exit(EXIT_SUCCESS);
}