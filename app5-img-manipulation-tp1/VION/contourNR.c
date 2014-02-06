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
#include "lutNR.h"
#include "contourNR.h"


/* ---------------------------------------------------------------------- */
void roberts_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ---------------------------------------------------------------------- */
{
}

/* --------------------------------------------------------------------------------- */
void fgl_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, float32 alpha, uint8 **Y)
/* --------------------------------------------------------------------------------- */
{
}

/* ---------------------------------------------------------------------- */
void max_dir_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ---------------------------------------------------------------------- */
{
}
/* -------------------------------------------------------------------------- */
void max_dir_ext_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* -------------------------------------------------------------------------- */
{
}
/* -------------------------------------------------------------------- */
void sobel_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* -------------------------------------------------------------------- */
{
    int i, j;
    int ii, jj;

    uint8 **T;
    float32 y;

    sint8 **Kx;
    Kx = si8matrix(-1,1, -1, 1);
    Kx[-1][-1]=-1;
    Kx[0][-1]=-2;
    Kx[1][-1]=-1;

    Kx[-1][0]=0;
    Kx[0][0]=0;
    Kx[1][0]=0;

    Kx[-1][1]=1;
    Kx[0][1]=2;
    Kx[1][1]=1;

    sint8 **Ky;
    Ky = si8matrix(-1,1, -1, 1);
    Ky[-1][-1]=-1;
    Ky[0][-1]=0;
    Ky[1][-1]=1;

    Ky[-1][0]=-2;
    Ky[0][0]=0;
    Ky[1][0]=2;

    Ky[-1][1]=-1;
    Ky[0][1]=0;
    Ky[1][1]=1;


    T = ui8matrix(i0-1, i1+1, j0-1, j1+1);
    zero_ui8matrix(T, i0-1, i1+1, j0-1, j1+1);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, 1);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {

            y = 0.0f;
            for(ii=-1; ii<=1; ii++) {
                for(jj=-1; jj<=1; jj++) {
                    y += T[i+ii][j+jj] * Kx[ii][jj];
                }
            }
            Y[i][j] = (uint8) fabs(y/8);
        }
    }

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {

            y = 0.0f;
            for(ii=-1; ii<=1; ii++) {
                for(jj=-1; jj<=1; jj++) {
                    y += T[i+ii][j+jj] * Ky[ii][jj];
                }
            }
            
            Y[i][j] += (uint8) fabs(y/8);
            if(Y[i][j]<0.0f) Y[i][j] = 0.0f;
            if(Y[i][j]>255.0f) Y[i][j] = 255.0f;
        }
    }

    free_ui8matrix(T, i0-1, i1+1, j0-1, j1+1);
    free_ui8matrix(Kx, -1, 1, -1, 1);
    free_ui8matrix(Ky, -1, 1, -1, 1);
}
