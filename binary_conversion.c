#include "STACK.h"
#include <math.h>

int main()
{
    printf("N = ");
    int N, i = 0;
    scanf("%d", &N);
    int temp = N;
    stack *sp = malloc(sizeof *sp);
    init(sp);
    int SIZE = (int)log2(temp) + 1;
    int *bin = malloc(SIZE * sizeof(int));
    while (N > 0)
    {
        push(sp, N % 2);
        N = N >> 1;
    }
    while (sp->top > 0)
    {
        bin[i++] = pop(sp);
    }
    printf("Binary N:\n");
    for (int j = 0; j < SIZE; j++)
    {
        printf("%d ", bin[j]);
    }
    printf("\n");
    destroy(sp);
    free(bin);
    return 0;
}