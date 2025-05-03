#include "stack.h"

int encode(char x) {
    switch(x) {
        case '*':
        case '/':
        case '$':
            return 1;
        case '+':
        case '-':
            return 0;
        default:
            return -1; 
    }
}

int isSuperior(char x, char y) {
    return (encode(x) <= encode(y));
}

void convert(char *s, char *t) {
    int len, j = 0;
    for (len = 0; s[len] != '\0'; len++);
    stack *sp = (stack *)malloc(sizeof(stack));
    init(sp); 
    push(sp, (int)'(');
    s[len++] = ')';   
    s[len] = '\0';
    for (int i = 0; i < len; i++) {
        char ch = s[i];
        switch(ch) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '$':
                while (sp->top > 0 && sp->items[sp->top - 1] != '(' &&
                       isSuperior(ch, (char)(sp->items[sp->top - 1]))) {
                    t[j++] = (char)pop(sp);
                }
                push(sp, (int)(ch));
                break;
            case '(':
                push(sp, (int)'(');
                break;
            case ')':
                while (sp->top > 0 && sp->items[sp->top - 1] != '(') {
                    t[j++] = (char)pop(sp);
                }
                if (sp->top > 0 && sp->items[sp->top - 1] == '(')
                    pop(sp); 
                break;
            default:
                t[j++] = ch;
        }
    }
    t[j] = '\0';
    destroy(sp);
}

int main() {
    char *s, *t;
    s = (char *)calloc(64, sizeof(char));
    t = (char *)calloc(64, sizeof(char));
    printf("INFIX: ");
    if (scanf(" %63[^\n]", s) != 1) {
        fprintf(stderr, "Input error\n");
        free(s);
        free(t);
        return 1;
    }
    convert(s, t);
    printf("POSTFIX: %s\n", t);
    free(s);
    free(t);
    return 0;
}