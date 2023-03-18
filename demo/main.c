#include <fractions64.h>

int main() {
    fracSetLogLvl(FRAC_ALL);
    fracFraction64 f1 = fracCreateFloatFraction64(22.0l/7.0l, 10);
    fracDumpFraction64(stdout, &f1, NULL);
    return 0;
}