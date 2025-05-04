#include "STACK.h"
#include <stdio.h>
#include <stdlib.h>

int isValid(char *s)
{
    stack *sp = calloc(1, sizeof *sp);
    init(sp);
    for (int i = 0; s[i]; i++)
    {
        int code;
        switch (s[i])
        {
        case '(':
            code = 0;
            push(sp, code);
            break;
        case '{':
            code = 1;
            push(sp, code);
            break;
        case '[':
            code = 2;
            push(sp, code);
            break;
        case ')':
            if (sp->top == 0 || pop(sp) != 0)
            {
                destroy(sp);
                return 0;
            }
            break;
        case '}':
            if (sp->top == 0 || pop(sp) != 1)
            {
                destroy(sp);
                return 0;
            }
            break;
        case ']':
            if (sp->top == 0 || pop(sp) != 2)
            {
                destroy(sp);
                return 0;
            }
            break;
        default:
            continue;
        }
    }
    int ok = (sp->top == 0);
    destroy(sp);
    return ok;
}

int main()
{
    char *s = calloc(64, 1);
    if (!s)
    {
        perror("calloc");
        return 1;
    }
    printf("String: ");
    if (scanf(" %63[^\n]", s) != 1)
    {
        fprintf(stderr, "Input error\n");
        free(s);
        return 1;
    }
    puts(isValid(s) ? "__valid" : "__invalid");
    free(s);
    return 0;
}