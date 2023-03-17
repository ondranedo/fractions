//
// Created by Ondřej Nedojedlý on 13.03.2023.
//

#include "fractions64.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

/*********************\

     Static d.t

\*********************/

static struct Allocator_{
    void*(*alloc)(size_t size);
    void(*free)(void* block);
    void*(*realloc)(void* block,size_t new_size);
};
typedef struct Allocator_ Allocator;

static struct FractionSplitToLCD_{
    int64_t LCD;
    int64_t frac1_num;
    int64_t frac2_num;
};
typedef struct FractionSplitToLCD_ FractionSplitToLCD;

/*********************\

      Static data

\*********************/
// TODO: change allocator functions
static Allocator allocator = {malloc, free, realloc};
// TODO: change msg severity
static fracSeverity severity = FRAC_ERROR;
static int simplify = 1;

/*********************\

   Static functions

\*********************/
static int64_t abs64(const int64_t a);
static void formatMSGOutputToBuffer(char *buff, size_t size, fracFraction64 *frac, const char *form);
static FractionSplitToLCD splitToNumerators(fracFraction64 *frac1, fracFraction64 *frac2);
static void logMSG(const char* msg, fracSeverity severity);
static void severityToStr(char* buff, size_t buff_size, fracSeverity sev);

/*********************\

 Function definitions

\*********************/
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
    if(simplify)
        fracSimplifyFraction64(frac);
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
    int64_t scalar = abs64(frac1->b) > abs64(frac2->b) ? abs64(frac1->b) : abs64(frac2->b);
    int64_t max_LCD = abs64(frac1->b) * abs64(frac2->b);
    int64_t LCD;

    for(LCD = scalar; LCD<max_LCD; LCD+=scalar)
        if(LCD % frac1->b == 0 && LCD % frac2->b == 0)
            break;

    return LCD;
}

static void formatMSGOutputToBuffer(char *buff, size_t size, fracFraction64 *frac, const char *form)
{
    char tmp_buff[FRAC_MSG_BUFFER_SIZE];
    size_t i, tmp_buffer_size = 0;
    memset(buff, 0, size);

    for(i = 0; i < size && form[i] != '\0'; i++)
    {
        if(form[i]=='%')
            tmp_buffer_size+=snprintf(tmp_buff + tmp_buffer_size,FRAC_MSG_BUFFER_SIZE, "%lli", form[++i] == 'a' ? frac->a : frac->b);
        else
            tmp_buff[tmp_buffer_size++] = form[i];
    }

    if(tmp_buffer_size>size)
        logMSG("can't write to dump msg, memory corruption detected, change buffer size", FRAC_ERROR);
    else
        memcpy(buff, tmp_buff, size);
}

void FRAC_API fracDumpFraction64(FILE* file, fracFraction64* frac, const char* form)
{
    char buff[FRAC_MSG_BUFFER_SIZE];

    if(form)
        formatMSGOutputToBuffer(buff, FRAC_MSG_BUFFER_SIZE, frac, form);
    else
        snprintf(buff, FRAC_MSG_BUFFER_SIZE, "%lli/%lli", frac->a, frac->b);

    fprintf(file,"%s", buff);
}

static int64_t abs64(const int64_t a)
{
return a >= 0 ? a : -a;
}

static FractionSplitToLCD splitToNumerators(fracFraction64 *frac1, fracFraction64 *frac2)
{
    FractionSplitToLCD dat;
    dat.LCD = fracLCDFraction64(frac1, frac2);
    dat.frac1_num = dat.LCD/frac1->b * frac1->a;
    dat.frac2_num = dat.LCD/frac2->b * frac2->a;
    return dat;
}

fracFraction64* FRAC_API fracAddFraction64H(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 * retfrac = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    fracSetFraction64(retfrac,dat.frac1_num + dat.frac2_num,dat.LCD);
    return retfrac;
}

fracFraction64 FRAC_API fracAddFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 retfrac;
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    fracSetFraction64(&retfrac,dat.frac1_num + dat.frac2_num,dat.LCD);
    return retfrac;
}

void FRAC_API fracAddOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    fracSetFraction64(frac1,dat.frac1_num + dat.frac2_num,dat.LCD);
}

fracFraction64* FRAC_API fracSubFraction64H(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 * retfrac = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    fracSetFraction64(retfrac,dat.frac1_num - dat.frac2_num,dat.LCD);
    return retfrac;
}

fracFraction64 FRAC_API fracSubFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 retfrac;
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    fracSetFraction64(&retfrac,dat.frac1_num - dat.frac2_num,dat.LCD);
    return retfrac;
}

void FRAC_API fracSubOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    fracSetFraction64(frac1,dat.frac1_num - dat.frac2_num,dat.LCD);
}

int64_t FRAC_API fracComFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    FractionSplitToLCD dat = splitToNumerators(frac1, frac2);
    return dat.frac1_num > dat.frac2_num ? 1 :  dat.frac1_num == dat.frac2_num ? 0 : -1;
}

double FRAC_API fracPowDoubleFraction64(const double num, fracFraction64* frac)
{
    double power = pow(num, (double)frac->a);
    double sqrt = pow(power, 1.0/(double)frac->b);
    return sqrt;
}

fracFraction64* FRAC_API fracPowFraction64H(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64* retfrac = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));

    logMSG("Power operation should not be called on fracFraction64, use floating point base fractions", FRAC_WARNING);

    fracSetFraction64(retfrac, (int64_t)fracPowDoubleFraction64((double)frac1->a, frac2),
                      (int64_t)fracPowDoubleFraction64((double)frac1->b, frac2));

    return retfrac;
}

fracFraction64  FRAC_API fracPowFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    fracFraction64 retfrac;
    logMSG("Power operation should not be called on fracFraction64, use floating point base fractions", FRAC_WARNING);

    fracSetFraction64(&retfrac, (int64_t)fracPowDoubleFraction64((double)frac1->a, frac2),
                      (int64_t)fracPowDoubleFraction64((double)frac1->b, frac2));
    return retfrac;
}

void FRAC_API fracPowOverwriteFraction64(fracFraction64* frac1, fracFraction64* frac2)
{
    logMSG("Power operation should not be called on fracFraction64, use floating point base fractions", FRAC_WARNING);

    fracSetFraction64(frac1, (int64_t)fracPowDoubleFraction64((double)frac1->a, frac2),
                      (int64_t)fracPowDoubleFraction64((double)frac1->b, frac2));
}

static void logMSG(const char* msg, fracSeverity sev)
{
    char buff[FRAC_MSG_BUFFER_SIZE];
    if(sev < severity) return;

    severityToStr(buff,FRAC_MSG_BUFFER_SIZE, sev);
    fprintf(stderr, "[%s] %s\n", buff, msg);
}

static void severityToStr(char* buff, size_t buff_size, fracSeverity sev)
{
    if(buff_size<8) return;
    switch (sev) {
        case FRAC_NONE:
            break;
        case FRAC_WARNING:
            snprintf(buff, buff_size, "WARNING");
            break;
        case FRAC_ERROR:
            snprintf(buff, buff_size, "ERROR");
            break;
        default:
            snprintf(buff, buff_size, "UNKNOWN");
    }
}

void FRAC_API fracSetLogLvl(fracSeverity sev)
{
    severity = sev;
}

void FRAC_API fracSimplifyFraction64(fracFraction64* frac)
{
    int64_t max_sim = frac->a > frac->b ? frac->a : frac->b;
    for(int64_t i = 2; i <= max_sim; i++)
    {
        if(frac->a%i == 0 && frac->b%i == 0)
        {
            frac->a /= i;
            frac->b /= i;
            fracSimplifyFraction64(frac);
        }
    }
}

void FRAC_API fracSetDefaultSimplification(const int state)
{
    simplify = state;
}

long double FRAC_API fracFloatFraction64(fracFraction64* frac/*, int8_t precision*/)
{
    // TODO: presion set
    return  (long double)frac->a / (long double)frac->b;
}
fracFraction64* FRAC_API fracCreateFloatFraction64H(const long double num, const int8_t precision)
{
    fracFraction64* frac = (fracFraction64*)allocator.alloc(sizeof(fracFraction64));
    int64_t scalar = (int64_t)pow(10, precision);
    fracSetFraction64(frac, (int64_t)(num*scalar),scalar);
    return frac;
}

fracFraction64 FRAC_API fracCreateFloatFraction64(const long double num, const int8_t precision)
{
    fracFraction64 frac;
    int64_t scalar = (int64_t)pow(10, precision);
    fracSetFraction64(&frac, (int64_t)(num*scalar),scalar);
    return frac;
}