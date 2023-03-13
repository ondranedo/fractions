/* Created by Ondrej Nedojedly
 * Date: 13.03.2023 (dd/mm/yyyy)
 */

#ifndef ZLOMKY_FRACTIONS_H
#define ZLOMKY_FRACTIONS_H

#include <inttypes.h>

typedef struct{
    int64_t a;
    int64_t b;
} fracFraction64;

// Fraction creation
fracFraction64  __cdecl fracCreateSFraction64(const int64_t a, const int64_t b);
fracFraction64* __cdecl fracCreateFraction64(const int64_t a, const int64_t b);

// Fraction setters
void __cdecl fracSetFraction64(fracFraction64* frac, const int64_t a, const int64_t b);
void __cdecl fracSetAFraction64(fracFraction64* frac, const int64_t a);
void __cdecl fracSetBFraction64(fracFraction64* frac, const int64_t b);

// Fraction getters
void __cdecl fracGetAFraction64(fracFraction64* frac, const int64_t a);
void __cdecl fracGetBFraction64(fracFraction64* frac, const int64_t b);

// Copy functions
fracFraction64  __cdecl fracGetCpyFraction64(const fracFraction64* frac);
fracFraction64* __cdecl fracGetCpySFraction64(const fracFraction64* frac);



#endif //ZLOMKY_FRACTIONS_H
