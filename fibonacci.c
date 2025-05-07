#include <stdio.h>
#include <math.h>

static inline int fibonacci(int x) {
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    double psi = (1.0 - sqrt(5.0)) / 2.0;
    return (int)((pow(phi, x) - pow(psi, x)) / sqrt(5.0) + 0.5);
}

int main() {
    int n;
    while(1) {
        printf("n = ");
        scanf("%d", &n);
        if (n < 0)
            return 0;
        printf("f(n) = %d\n", fibonacci(n));
    }
    return 0;
}