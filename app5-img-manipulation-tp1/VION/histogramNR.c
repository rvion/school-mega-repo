/* --------------------- */
/* --- histogramNR.c --- */
/* --------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"
#include "mutil.h"
#include "lutNR.h"
#include "histogramNR.h"

/* ------------------------------------- */
uint32* alloc_ui32histogram(int i0, int i1)
/* ------------------------------------- */
{
    return ui32vector(i0, i1);
}
/* -------------------------------------------- */
void zero_ui32histogram(uint32 *H, int i0, int i1)
/* -------------------------------------------- */
{
    zero_ui32vector(H, i0, i1);
}
/* ------------------------------------------------------------------------- */
void display_ui32histogram(uint32 *H, int i0, int i1, char *format, char *name)
/* ------------------------------------------------------------------------- */
{
    display_ui32vector(H, i0, i1, format, name);
}
/* -------------------------------------------- */
void free_ui32histogram(uint32* H, int i0, int i1)
/* -------------------------------------------- */
{
    free_ui32vector(H, i0, i1);
}
/* ---------------------------------------------------------------------------- */
void ui32histogram_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint32 *H)
/* ---------------------------------------------------------------------------- */
{
    int i, j;

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            H[X[i][j]]++;
        }
    }
}
/* ------------------------------------------------------ */
void cumsum_ui32vector(uint32 *X, int i0, int i1, uint32 *Y)
/* ------------------------------------------------------ */
{
    // Matlab name
    int i;

    Y[i0] = X[i0];

    for(i=i0+1; i<=i1; i++) {
        Y[i] = Y[i-1] + X[i];
    }
}
/* ------------------------------------------------------------------------------------ */
void mulfrac_ui32histogram_ui8lut(uint32 *X, int i0, int i1, uint32 a, uint32 b, uint8 *Y)
/* ------------------------------------------------------------------------------------ */
{
    int i;
    for(i=i0; i<=i1; i++) {
        Y[i] = (a * X[i] + b/2) / b;
    }
}
/* ------------------------------------------------------------------------------------- */
void ui32histogram_equalize_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ------------------------------------------------------------------------------------- */
{
    uint32 *H, *HC;
    uint8 *L;
    int size = (i1-i0+1)*(j1-j0+1);

    L = alloc_ui8lut(); zero_ui8lut(L);

    H  = alloc_ui32histogram(0, 255); zero_ui32histogram(H,  0, 255);
    HC = alloc_ui32histogram(0, 255); zero_ui32histogram(HC, 0, 255);

    ui32histogram_ui8matrix(X, i0, i1, j0, j1, H);
    cumsum_ui32vector(H, 0, 255, HC);
    mulfrac_ui32histogram_ui8lut(HC, 0, 255, 255, size, L);
    apply_ui8lut(X, i0, i1, j0, j1, L, Y);

    free_ui32histogram(H,  0, 255);
    free_ui32histogram(HC, 0, 255);
    free_ui8lut(L);
}
/* ---------------------------------------------------------------------- */
int calc_otsu_threshold_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1)
/* ---------------------------------------------------------------------- */
{
    int threshold;
    uint32 *H;
    H = alloc_ui32histogram(0, 255);
    zero_ui32histogram(H, 0, 255);
    ui32histogram_ui8matrix(X, i0, i1, j0, j1, H);
    threshold =  calc_otsu_threshold_ui32vector(H, 1, 255);
    free_ui32histogram(H, 0, 255);

    return threshold;
}
/* ---------------------------------- */
float32 somme(uint32 *X, int i0, int i1)
/* ---------------------------------- */
{
    int i;
    float32 s = 0;
    for(i=i0; i<=i1; i++) {
        s += X[i];
    }
    return s;
}
/* ----------------------------------------- */
float32 somme_prod_i(uint32 *X, int i0, int i1)
/* ----------------------------------------- */
{
    int i;
    float32 s = 0;
    for(i=i0; i<=i1; i++) {
        s += X[i] * i;
    }
    return s;
}
/* ----------------------------------------- */
float32 somme_prod_i2(uint32 *X, int i0, int i1)
/* ----------------------------------------- */
{
    int i;
    float32 s = 0;
    for(i=i0; i<=i1; i++) {
        s += X[i] * i*i;
    }
    return s;
}
/* --------------------------------------------------------- */
int calc_otsu_threshold_v0_ui32vector(uint32 *H, int i0, int i1)
/* ---------------------------------------------------------- */
{
    // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
    // slow version (exact implementation of Otsu's original algorithm

    int t, threshold = i0;

    float32 Stot;
    float32 bS, bSx, bSxx;
    float32 fS, fSx, fSxx;

    float32 sb, wb, ub, vb;
    float32 sf, wf, uf, vf;

    float32 v, vmin = 1e39;


    Stot = somme(H, i0, i1);

    for(t=i0; t<=i1; t++) {

        bS   = somme        (H, i0, t-1); fS   = somme        (H, t, i1);
        bSx  = somme_prod_i (H, i0, t-1); fSx  = somme_prod_i (H, t, i1);
        bSxx = somme_prod_i2(H, i0, t-1); fSxx = somme_prod_i2(H, t, i1);

        if((bS == 0.0f) || (fS == 0.0f)) continue;

        sb = bS;
        sf = fS;

        wb = sb / Stot;
        wf = sf / Stot;

        ub = bSx / bS;
        uf = fSx / fS;

        vb = (bS*bSxx - bSx*bSx) / (bS*bS);
        vf = (fS*fSxx - fSx*fSx) / (fS*fS);

        v = wb * vb + wf * vf;

        //printf("t = %d v = %.4f\n", t, v);
        if(v < vmin) {
            vmin = v;
            threshold = t;
        }
    }
    return threshold;
}
/* ---------------------------------------------------------- */
int calc_otsu_threshold_v1_ui32vector(uint32 *H, int i0, int i1)
/* ---------------------------------------------------------- */
{
    // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
    // fast version

    int t, threshold = i0;

    float32 S = 0.0f;
    float32 Sx = 0.0f; // total Sums

    float32 varBetween, varMax = 0.0f;
    float32 sB = 0.0f, sF = 0.0f;
    float32 wB = 0.0f, wF = 0.0f; // weight Background, weight Foreground
    float32 mB, mF;               // mean  Background, mean Foreground

    for(t=i0; t<=i1; t++) {
        S  += H[t];
        Sx += H[t] * t;
    }

    for(t=i0; t<=i1; t++) {
        wB += H[t];
        if(wB == 0) continue;

        wF = S - wB;
        if(wF == 0) continue;

        sB += H[t] * t;
        sF = Sx - sB;

        wB /= S;
        wF /= S;

        mB = sB / wB;
        mF = sF / wF;

        varBetween = wB * wF * (mB - mF)*(mB - mF);
        printf("varBetween[%d] = %.4f\n", t, varBetween);

        if(varBetween > varMax) {
            varMax = varBetween;
            threshold = t;
        }
    }
    return threshold;
}
/* ------------------------------------------------------- */
int calc_otsu_threshold_ui32vector(uint32 *H, int i0, int i1)
/* ------------------------------------------------------- */
{
    return calc_otsu_threshold_v0_ui32vector(H, i0, i1);
}
