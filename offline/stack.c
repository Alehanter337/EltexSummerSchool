#include <stdio.h>

long sum(long a, long b, long c, long d, long e, long f, long g, long h, long i) {
    long sum = 0;
    sum = a + b + c + d + e + f + g + h + i;
    return sum;
}

int main() {
    long  a,  b, c, d, e, f, g, h, i, j;
    a = 5;
    b = 6;
    c = 7;
    d = 8;
    e = 9;
    f = 10;
    g = 11;
    h = 12;
    i = 13;
    j = 0;
    j = sum(a, b, c, d, e, f, g, h, i);
    printf("sum = %ld\n", j);    

}
