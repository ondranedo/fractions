#include <fractions64.h>

int main() {
    fracFraction64 f1 = fracCreateFraction64(-3, -8);
    fracFraction64 f2 = fracCreateFraction64(-6, -2);

    int64_t lcd = fracLCDFraction64(&f1, &f2);
    return lcd;
}