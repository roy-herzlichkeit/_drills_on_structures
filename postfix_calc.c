#include "stack.h"
#include <math.h>

int main() {
    stack *sp = malloc(sizeof *sp);
    init(sp);
    char *s = calloc(64, sizeof(char));
    printf("Postfix Expression: ");
    if (scanf(" %63[^\n]", s) != 1) {
        fprintf(stderr, "Input error\n");
        free(s);
        destroy(sp);
        return 1;
    }
    for (int i = 0, a, b; s[i] != '\0'; i++) { 
        switch (s[i]) {
        case '+':
            a = pop(sp), b = pop(sp);
            push(sp, b + a);
            break;
        case '-':
            a = pop(sp), b = pop(sp);
            push(sp, b - a);
            break;
        case '*':
            a = pop(sp), b = pop(sp);
            push(sp, b * a);
            break;
        case '/':
            a = pop(sp), b = pop(sp);
            push(sp, b / a);
            break;
        case '$':
            a = pop(sp), b = pop(sp);
            push(sp, pow(b, a));
            break;
        case ' ':
            break;
        default:
            push(sp, s[i] - '0');
        }
    }
    printf("Result: %d\n", pop(sp));
    free(s);
    destroy(sp);
    return 0;
}