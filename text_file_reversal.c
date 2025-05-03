#include "stack.h"

int main()
{
    const char *source = "input.txt", *dest = "output.txt";
    FILE *fps = fopen(source, "r");
    if (!fps)
    {
        fprintf(stderr, "Error opening file %s\n", source);
        return 1;
    }
    FILE *fpd = fopen(dest, "w");
    if (!fpd)
    {
        fprintf(stderr, "Error opening file %s\n", dest);
        fclose(fps);
        return 1;
    }
    stack *s = malloc(sizeof *s);
    if (!s)
    {
        perror("malloc");
        fclose(fps);
        fclose(fpd);
        return 1;
    }
    init(s);
    int ch;
    while ((ch = fgetc(fps)) != EOF)
    {
        push(s, ch);
    }
    while (s->top > 0)
    {
        fputc(pop(s), fpd);
    }
    fclose(fps);
    fclose(fpd);
    destroy(s);
    return 0;
}