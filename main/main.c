#include <stdio.h>
#include <stdlib.h>

#define COUNT 30

long fibonacci(int n) {
    if (n <= 1)
        return n;
    long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    FILE *file = fopen("data.bin", "wb");
    if (!file) return 1;

    for (int i = 0; i < COUNT; i++) {
        long value = fibonacci(i);
        fwrite(&value, sizeof(long), 1, file);
    }

    fclose(file);

    file = fopen("data.bin", "rb");
    if (!file) return 1;

    long sum = 0;
    long temp;

    while (fread(&temp, sizeof(long), 1, file) == 1) {
        sum += temp;
    }

    fclose(file);

    volatile long result = sum;
    (void)result;

    return 0;
}