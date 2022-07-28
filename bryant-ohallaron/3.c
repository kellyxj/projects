#include <stdio.h>
#include <stdlib.h>

typedef __int128 int128_t;

long decode2(long x, long y, long z);

int main(void) {
    
}

long decode2(long x, long y, long z) {
    y -= z;
    x *= y;
    y <<= 63;
    y >>= 63;
    y ^= x;
    return y;
}

void store_prod(int128_t *dest, int64_t x, int64_t y) {
    *dest = x * (int128_t) y;
}