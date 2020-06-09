#include <math.h>
#include <stdlib.h>

#ifndef FT_MAXLEN
#define FT_MAXLEN 0x1000000L
#endif

#ifndef FT_PHMASK
#define FT_PHMASK 0x0FFFFFFL
#endif

#include "fosc.h"

using namespace daisysp;

void FOsc::Init(float sample_rate, float* wavetable)
{
    freq_ = 400;
    amp_ = 0.4;
    iphs_ = 0.f;
    ftp_ = ftp;

    mod_ = 1.0;
    car_ = 1.0;
    indx_ = 1.0;

    cphs_ = mphs_ = (int32_t)(iphs_ * FT_MAXLEN);
}

float FOsc::Process()
{
    float *ftp;

    float  amp, cps, fract, v1, v2, car, fmod, cfreq, mod;
    float  xcar, xmod, ndx, *ftab;
    int32_t  mphs, cphs, minc, cinc, lobits;
    float  sicvt = p->ft->sicvt;
    float  *ft;

    ftp = ftp_;
    ft = ftp->tbl;
    lobits = ftp->lobits;
    mphs = mphs_;
    cphs = cphs_;
    cps  = freq_;
    amp  = amp_;
    xcar = car_;
    xmod = mod_;

    car = cps * xcar;
    mod = cps * xmod;
    ndx = indx_ * mod;
    minc = (int32_t)(mod * sicvt);
    mphs &= FT_PHMASK;
    fract = ((mphs) & ftp->lomask) * ftp->lodiv;
    ftab = ft + (mphs >> lobits);
    v1 = ftab[0];

    if(ftab[0] == p->ft->tbl[p->ft->size - 1]) {
        v2 = p->ft->tbl[0];
    } else {
        v2 = ftab[1];
    }

    fmod = (v1 + (v2 - v1) * fract) * ndx;
    mphs += minc;
    cfreq = car + fmod;
    cinc = (int32_t)(cfreq * sicvt);
    cphs &= FT_PHMASK;
    fract = ((cphs) & ftp->lomask) * ftp->lodiv;
    ftab = ft + (cphs >>lobits);
    v1 = ftab[0];

    if(ftab[0] == p->ft->tbl[p->ft->size - 1]) {
        v2 = p->ft->tbl[0];
    } else {
        v2 = ftab[1];
    }

    *out = (v1 + (v2 - v1) * fract) * amp;
    cphs += cinc;
    mphs_ = mphs;
    cphs_ = cphs;

}
