/* Created by Ondrej Nedojedly
 * Date: 13.03.2023 (dd/mm/yyyy)
 */

#ifndef ZLOMKY_FRACTIONS64_H
#define ZLOMKY_FRACTIONS64_H

#define FRAC_API __cdecl

#include <inttypes.h>

typedef struct{
    int64_t a;
    int64_t b;
} fracFraction64;

// TODO: Fraction allocator

// Fraction creation
fracFraction64  FRAC_API fracCreateSFraction64(const int64_t a, const int64_t b);
fracFraction64* FRAC_API fracCreateFraction64(const int64_t a, const int64_t b);

// Copy functions
fracFraction64  FRAC_API fracGetCpySFraction64(const fracFraction64* frac);
fracFraction64* FRAC_API fracGetCpyFraction64(const fracFraction64* frac);

// destruction
void FRAC_API fracDestroyFraction64(fracFraction64* frac);

// Fraction setters
void FRAC_API fracSetFraction64(fracFraction64* frac, const int64_t a, const int64_t b);
void FRAC_API fracSetAFraction64(fracFraction64* frac, const int64_t a);
void FRAC_API fracSetBFraction64(fracFraction64* frac, const int64_t b);

// Fraction getters
void FRAC_API fracGetAFraction64(fracFraction64* frac, const int64_t a);
void FRAC_API fracGetBFraction64(fracFraction64* frac, const int64_t b);

// Fraction addition
fracFraction64  FRAC_API fracAddFraction64S(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64* FRAC_API fracAddFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracAddOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction subtraction
fracFraction64  FRAC_API fracSubFraction64S(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64* FRAC_API fracSubFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracSubOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction multiplication
fracFraction64  FRAC_API fracMulFraction64S(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64* FRAC_API fracMulFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracMulOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction division
fracFraction64  FRAC_API fracDivFraction64S(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64* FRAC_API fracDivFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracDivOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

#endif //ZLOMKY_FRACTIONS64_H
