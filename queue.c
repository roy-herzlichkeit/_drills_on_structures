#include "STACK.h"

void enqueue(stack *s, int value) {
    push(s, value);
}

int dequeue(stack *s) {
    if (s->top == 0) {
        printf("__queue_underflow\n");
        return INT_MIN;
    }
    stack *t = (stack *)malloc(sizeof(stack));
    init(t);
    while (s->top > 1)
        push(t, pop(s));
    int res = pop(s);
    while (t->top > 0)
        push(s, pop(t));
    destroy(t);
    return res;
}

int main() {
    stack *sp = malloc(sizeof *sp);
    init(sp);
    while (1) {
        printf("CHOICE: ");
        int temp;
        scanf("%d", &temp);
        switch(temp) {
        case 1:
            printf("VALUE: ");
            scanf("%d", &temp);
            enqueue(sp, temp);
            break;
        case 2:
            printf("VALUE: %d\n", dequeue(sp));
            break;
        default:
            destroy(sp);
            return 0;
        }
    }
    destroy(sp);
    return 1;
}