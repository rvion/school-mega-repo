/* ------------------ */
/* --- filterNR.c --- */
/* ------------------ */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"
//#include "util.h"
//#include "kernel.h"

//#include "all.h"
//#include "mem.h"
//#include "outils.h"

#include "gauss.h"
#include "filterNR.h"

/* ---------------------------- */
float32** alloc_kernel(int radius)
/* ---------------------------- */
{
    float32 **K;
    K = f32matrix(-radius, radius, -radius, radius);
    return K;
}
/* ----------------------------------- */
void free_kernel(float32 **K, int radius)
/* ----------------------------------- */
{
    free_f32matrix(K, -radius, radius, -radius, radius);

}
/* ---------------------------------------------------------------- */
void display_kernel(float32 **K, int radius, char *format, char *name)
/* ---------------------------------------------------------------- */
{
    display_f32matrix(K, -radius, +radius, -radius, +radius, format, name);
}
/* ------------------------------------------------------- */
void init_gaussian_kernel(float32 **K, int radius, int sigma)
/* ------------------------------------------------------- */
{
    int i, j;
    float32 x, sx = 0.0f;

    for(i=-radius; i<=radius; i++) {
        for(j=-radius; j<=radius; j++) {
            x = gauss2D(sigma, i, j);
            sx += x;
            K[i][j] = x;
        }
    }
    for(i=-radius; i<=radius; i++) {
        for(j=-radius; j<=radius; j++) {
            K[i][j] /= sx;
        }
    }
}
/* ------------------------------------------- */
void init_average_kernel(float32 **K, int radius)
/* ------------------------------------------- */
{
    int i, j;
    float32 x, sx = (2*radius+1)*(2*radius+1);

    for(i=-radius; i<=radius; i++) {
        for(j=-radius; j<=radius; j++) {
            x = 1.0f / sx;
            K[i][j] = x;
        }
    }
}
/* ------------------------------------------------------------------------------------------------------- */
void convolve_kernel_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, float32 **K, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------------------- */
{
    int i, j;
    int ii, jj;

    uint8 **T;
    float32 y;

    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {

            y = 0.0f;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    y += T[i+ii][j+jj] * K[ii][jj];
                }
            }
            if(y<0.0f) y = 0.0f;
            if(y>255.0f) y = 255.0f;

            Y[i][j] = (uint8) y;
        }
    }
    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
}

/* ------------------------------------------------- */
void sort_selection_ui8vector(uint8 *X, int i0, int i1)
/* ------------------------------------------------- */
{
    int c,d;
    uint8 swap;
    for (c = i0; c < i1; c++) {
        for (d = i0 ; d < i1 - c; d++) {
            if (X[d] > X[d+1]){
            /* For decreasing order use < */
                swap = X[d];
                X[d] = X[d+1];
                X[d+1] = swap;
            }
        }
    }
}
/* --------------------------------------------------------------------------------- */
void median_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* --------------------------------------------------------------------------------- */
{
    int i, j;
    int ii, jj;
    int k;
    uint8 **T;
    float32 y;
    uint8 *vec;
    vec = ui8vector(0,(2*radius+1)*(2*radius+1));
    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            k = 0;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    //y += T[i+ii][j+jj] * K[ii][jj];
                    vec[k]= T[i+ii][j+jj];//X[ii][jj];
                    k ++;
                }
            }
            if(y<0.0f) y = 0.0f;
            if(y>255.0f) y = 255.0f;

            sort_selection_ui8vector(vec,0,k);
            Y[i][j] = (uint8) vec[radius*radius];
        }
    }
    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    //free_ui8vector(vec);
}
