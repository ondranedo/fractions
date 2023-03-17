/* Created by Ondrej Nedojedly
 * Date: 13.03.2023 (dd/mm/yyyy)
 */

#ifndef ZLOMKY_FRACTIONS64_H
#define ZLOMKY_FRACTIONS64_H

#define FRAC_API __cdecl

#include <inttypes.h>
#include <stdio.h>

#define FRAC_PRECISION_FLOAT 7
#define FRAC_PRECISION_DOUBLE 24
#define FRAC_PRECISION_LONGDOUBLE 33
#define FRAC_MSG_BUFFER_SIZE 256

typedef struct{
    int64_t a;
    int64_t b;
} fracFraction64;

typedef enum{
    FRAC_ALL = 0,
    FRAC_WARNING,
    FRAC_ERROR,
    FRAC_NONE
} fracSeverity;

// TODO: Fraction allocator
// TODO: Fraction conversion
// TODO: Fraction from/to string

// Fraction creation
fracFraction64*  FRAC_API fracCreateFraction64H(const int64_t a, const int64_t b);
fracFraction64  FRAC_API fracCreateFraction64(const int64_t a, const int64_t b);
//TODO:
//fracFraction64* FRAC_API fracCreateFloatFraction64H(const double num, const int8_t precision);
//TODO:
//fracFraction64  FRAC_API fracCreateFloatFraction64(const double num, const int8_t precision);

// Copy functions
fracFraction64* FRAC_API fracGetCpyFraction64H(const fracFraction64* frac);
fracFraction64 FRAC_API fracGetCpyFraction64(const fracFraction64* frac);

// destruction
void FRAC_API fracDestroyFraction64H(fracFraction64* frac);
void FRAC_API fracDestroyFraction64(fracFraction64* frac);

// Fraction setters
void FRAC_API fracSetFraction64(fracFraction64* frac, const int64_t a, const int64_t b);
void FRAC_API fracSetAFraction64(fracFraction64* frac, const int64_t a);
void FRAC_API fracSetBFraction64(fracFraction64* frac, const int64_t b);

// Fraction getters
int64_t FRAC_API fracGetAFraction64(fracFraction64* frac);
int64_t FRAC_API fracGetBFraction64(fracFraction64* frac);

// Fraction addition
fracFraction64* FRAC_API fracAddFraction64H(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64 FRAC_API fracAddFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracAddOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction subtraction
fracFraction64* FRAC_API fracSubFraction64H(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64 FRAC_API fracSubFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracSubOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction multiplication
fracFraction64* FRAC_API fracMulFraction64H(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64 FRAC_API fracMulFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracMulOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction division
fracFraction64* FRAC_API fracDivFraction64H(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64  FRAC_API fracDivFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracDivOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Fraction power
fracFraction64* FRAC_API fracPowFraction64H(fracFraction64* frac1, fracFraction64* frac2);
fracFraction64  FRAC_API fracPowFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracPowOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2);
double FRAC_API fracPowDoubleFraction64(const double num, fracFraction64* frac);

// Fraction switch
void FRAC_API fracSwitchABFraction64(fracFraction64* frac);
void FRAC_API fracSwitchAFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracSwitchBFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Other functions
int64_t FRAC_API fracComFraction64(fracFraction64* frac1, fracFraction64* frac2);
void FRAC_API fracSimplifyFraction64(fracFraction64* frac);
void FRAC_API fracDumpFraction64(FILE* file, fracFraction64* frac, const char* form);
long double FRAC_API fracFloatFraction64(fracFraction64* frac/*, int8_t precision*/);

int64_t FRAC_API fracLCDFraction64(fracFraction64* frac1, fracFraction64* frac2);

// Control functions
void FRAC_API fracSetLogLvl(fracSeverity severity);
void FRAC_API fracSetDefaultSimplification(const int state);

#endif //ZLOMKY_FRACTIONS64_H
