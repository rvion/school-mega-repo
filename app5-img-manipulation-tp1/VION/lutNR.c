/* --------------- */
/* --- lutNR.c --- */
/* --------------- */

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

/* ------------------- */
uint8* alloc_ui8lut(void)
/* ------------------- */
{
    return ui8vector(0, 255);
}
/* -------------------- */
void free_ui8lut(uint8 *L)
/* -------------------- */
{
    free_ui8vector(L, 0, 255);
}
/* -------------------- */
void zero_ui8lut(uint8 *L)
/* -------------------- */
{
    zero_ui8vector(L, 0, 255);
}    
/* ------------------------------------------------- */
void display_ui8lut(uint8 *L, char *format, char *name)
/* ------------------------------------------------- */
{
    display_ui8vector(L, 0, 255, format, name);
}
/* -------------------------------------------------- */
void init_ui8lut(uint8 *L, uint8 threshold, uint8 value)
/* -------------------------------------------------- */
{
    int i;
    for(i=0; i<threshold; i++) {
        L[i] = 0;
    }
    for(i=threshold; i<=255; i++) {
        L[i] = value;
    }
}
/* --------------------------------------------------------------------------- */
void apply_ui8lut(uint8 **X, int i0, int i1, int j0, int j1, uint8 *L, uint8 **Y)
/* --------------------------------------------------------------------------- */
{
    uint8 x, y;
    int i, j;
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //Y[i][j] = L[X[i][j]];
            x = X[i][j];
            y = L[x];
            Y[i][j] = y;
        }
    }
}
/* ------------------------------------------------------------------------------------------------ */
void binary_threshold_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 threshold, uint8 **Y)
/* ------------------------------------------------------------------------------------------------ */
{
    uint8 *L;
    
    L = alloc_ui8lut();
    init_ui8lut(L, threshold, 1);
    
    apply_ui8lut(X, i0, i1, j0, j1, L, Y);
    
    free_ui8lut(L);
}
/* ------------------------------------------------------------------------------------------------------ */
void threshold_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 threshold, uint8 value, uint8 **Y)
/* ------------------------------------------------------------------------------------------------------ */
{
    uint8 *L;
    L = alloc_ui8lut();
    init_ui8lut(L, threshold, value);
    
    apply_ui8lut(X, i0, i1, j0, j1, L, Y);
    
    free_ui8lut(L);
}
/* ------------------------------------------------------------------------------- */
void double_intensity_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ------------------------------------------------------------------------------- */
{
    int j;
    uint8 *L;
    L = alloc_ui8lut();
    for(j=0;   j<=127; j++) { L[j] = 2*j; }
    for(j=128; j<=255; j++) { L[j] = 255; }

    apply_ui8lut(X, i0, i1, j0, j1, L, Y);
    
    free_ui8lut(L);
}
/* ----------------------------------------------------------------------- */
void gray2bin_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ----------------------------------------------------------------------- */
{
    uint8 *L;
    L = alloc_ui8lut();
    init_ui8lut(L, 1, 1);
    apply_ui8lut(X, i0, i1, j0, j1, L, Y);
    free_ui8lut(L);
}
/* ----------------------------------------------------------------------- */
void bin2gray_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ----------------------------------------------------------------------- */
{
    uint8 *L;
    L = alloc_ui8lut();
    init_ui8lut(L, 1, 255);
    apply_ui8lut(X, i0, i1, j0, j1, L, Y);
    free_ui8lut(L);
}