//
// Created by Ondřej Nedojedlý on 13.03.2023.
//

#include "fractions64.h"

#include <stdlib.h>

static struct Allocator{
    void*(*alloc)(size_t size);
    void(*free)(void* block);
    void*(*realloc)(void* block,size_t new_size);
}allocator = {malloc, free, realloc};

static int64_t mod64(const int64_t a)
{
    return a >= 0 ? a : -a;
}

fracFraction64 FRAC_API fracCreateFraction64(const int64_t a, const int64_t b)
{
    fracFraction64 f;
    fracSetFraction64(&f, a, b);
    return f;
}

fracFraction64* FRAC_API fracCreateFraction64H(const int64_t a, const int64_t b) {
    fracFraction64* f = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    fracSetFraction64(f, a, b);
    return f;
}

fracFraction64 FRAC_API fracGetCpyFraction64(const fracFraction64 *frac) {
    fracFraction64 f = {frac->a, frac->b};
    return f;
}

fracFraction64 FRAC_API *fracGetCpyFraction64H(const fracFraction64 *frac)
{
    fracFraction64* f = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    f->a = frac->a;
    f->b = frac->b;
    return f;
}

void FRAC_API fracDestroyFraction64(fracFraction64* frac)
{
    frac->a = 0;
    frac->b = 0;
}

void FRAC_API fracDestroyFraction64H(fracFraction64* frac) {
    allocator.free(frac);
}

void FRAC_API fracSetFraction64(fracFraction64* frac, const int64_t a, const int64_t b)
{
    frac->a = a;
    frac->b = b;
    // TODO: if default, simplify
}

void FRAC_API fracSetAFraction64(fracFraction64* frac, const int64_t a)
{
    fracSetFraction64(frac, a, frac->b);
}

void FRAC_API fracSetBFraction64(fracFraction64* frac, const int64_t b)
{
    fracSetFraction64(frac, frac->a, b);
}

int64_t FRAC_API fracGetAFraction64(fracFraction64* frac)
{
    return frac->a;
}

int64_t FRAC_API fracGetBFraction64(fracFraction64* frac)
{
    return frac->b;
}

fracFraction64 FRAC_API fracMulFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 f;
    fracSetFraction64(&f, frac1->a * frac2->a,frac1->b * frac2->b);
    return f;
}

fracFraction64* FRAC_API fracMulFraction64H(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64* f = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    fracSetFraction64(f, frac1->a * frac2->a,frac1->b * frac2->b);
    return f;
}

void FRAC_API fracMulOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracSetFraction64(frac1, frac1->a * frac2->a,frac1->b * frac2->b);
}

fracFraction64 FRAC_API fracDivFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 f;
    fracSetFraction64(&f, frac1->a * frac2->b,frac1->b * frac2->a);
    return f;
}

fracFraction64* FRAC_API fracDivFraction64H(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64* f = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    fracSetFraction64(f, frac1->a * frac2->b,frac1->b * frac2->a);
    return f;
}

void FRAC_API fracDivOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracSetFraction64(frac1, frac1->a * frac2->b,frac1->b * frac2->a);
}

void FRAC_API fracSwitchABFraction64(fracFraction64* frac)
{
    fracSetFraction64(frac, frac->b, frac->a);
}

void FRAC_API fracSwitchAFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracSetAFraction64(frac1, frac2->a);
}

void FRAC_API fracSwitchBFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracSetBFraction64(frac1, frac2->b);
}

int64_t FRAC_API fracLCDFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    int64_t scalar = mod64(frac1->b) > mod64(frac2->b) ? mod64(frac1->b) : mod64(frac2->b);
    int64_t max_LCD = mod64(frac1->b) * mod64(frac2->b);
    int64_t LCD;

    for(LCD = scalar; LCD<max_LCD; LCD+=scalar)
        if(LCD % frac1->b == 0 && LCD % frac2->b == 0)
            break;

    return LCD;
}