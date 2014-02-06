/* --------------- */
/* --- mutil.c --- */
/* --------------- */

// misc util

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mutil.h"

#include <string.h> // memset

/* ---------------- */
/* --- routines --- */
/* ---------------- */

/* --------------------------- */
uint8 ui8min2(uint8 x0, uint8 x1)
/* --------------------------- */
{
    if(x0<x1)
        return x0;
    else
        return x1;
}
/* ------------------------------------- */
uint8 ui8min3(uint8 x0, uint8 x1, uint8 x2)
/* ------------------------------------- */
{
    return ui8min2(ui8min2(x0,x1),x2);
}
/* ----------------------------------------------- */
uint8 ui8min4(uint8 x0, uint8 x1, uint8 x2, uint8 x3)
/* ----------------------------------------------- */
{
    return ui8min2(ui8min2(x0,x1),ui8min2(x2,x3));
}
/* --------------------------- */
uint8 ui8max2(uint8 x0, uint8 x1)
/* --------------------------- */
{
    if(x0>x1)
        return x0;
    else
        return x1;
}
/* ------------------------------------- */
uint8 ui8max3(uint8 x0, uint8 x1, uint8 x2)
/* ------------------------------------- */
{
    return ui8max2(ui8max2(x0,x1),x2);
}
/* ----------------------------------------------- */
uint8 ui8max4(uint8 x0, uint8 x1, uint8 x2, uint8 x3)
/* ----------------------------------------------- */
{
    return ui8max2(ui8max2(x0,x1),ui8max2(x2,x3));
}
/* ------------------------------- */
uint16 ui16min2(uint16 x0, uint16 x1)
/* ------------------------------- */
{
    if(x0<x1)
        return x0;
    else
        return x1;
}
/* ------------------------------------------ */
uint16 ui16min3(uint16 x0, uint16 x1, uint16 x2)
/* ------------------------------------------ */
{
    return ui16min2(ui16min2(x0,x1),x2);
}
/* ----------------------------------------------------- */
uint16 ui16min4(uint16 x0, uint16 x1, uint16 x2, uint16 x3)
/* ----------------------------------------------------- */
{
    return ui16min2(ui16min2(x0,x1),ui16min2(x2,x3));
}
/* ------------------------------- */
uint16 ui16max2(uint16 x0, uint16 x1)
/* ------------------------------- */
{
    if(x0>x1)
        return x0;
    else
        return x1;
}
/* ------------------------------------------ */
uint16 ui16max3(uint16 x0, uint16 x1, uint16 x2)
/* ------------------------------------------ */
{
    return ui16max2(ui16max2(x0,x1),x2);
}
/* ----------------------------------------------------- */
uint16 ui16max4(uint16 x0, uint16 x1, uint16 x2, uint16 x3)
/* ----------------------------------------------------- */
{
    return ui16max2(ui16max2(x0,x1),ui16max2(x2,x3));
}
/* ------------- */
uint8 ui8rand(void)
/* ------------- */
{
    static uint32 x=0;
    x = (11 * x + 13) % 17;
    return (uint8) x;
}
/* --------------- */
uint32 ui32rand(void)
/* --------------- */
{
    static uint32 x=0;
    x = (11 * x + 13) % 17;
    return (uint32) x;
}
/* -------------- */
uint32 f32rand(void)
/* -------------- */
{
    static float32 x=0;
    x = (float32) fmod(11 * x + 13, 17);
    return (float32) x ;
}
/* --------------------------------------- */
void rand_ui8vector(uint8 *X, int i0, int i1)
/* --------------------------------------- */
{
    int i;
    
    for(i=i0; i<=i1; i++) {
        X[i] = ui8rand();
    }
}
/* ----------------------------------------- */
void rand_ui32vector(uint32 *X, int i0, int i1)
/* ----------------------------------------- */
{
    int i;
    
    for(i=i0; i<=i1; i++) {
        X[i] = ui32rand();
    }
}
/* ----------------------------------------- */
void rand_f32vector(float32 *X, int i0, int i1)
/* ----------------------------------------- */
{
    int i;
    
    for(i=i0; i<=i1; i++) {
        X[i] = f32rand();
    }
}
/* --------------- */
int getIter(int size)
/* --------------- */
{
    if(size <   32) return 1024;
    if(size <   64) return 64 ;
    if(size <  128) return 8;
    if(size <  256) return 2;
    if(size <  512) return 2;
    if(size < 1024) return 2;
    if(size < 2048) return 1;
    return 2;
}
/* ----------------- */
int getIterAV(int size)
/* ----------------- */
{
    return 3*getIter(size);
}
/* --------------------------------- */
float32 gauss(float32 sigma, float32 x)
/* --------------------------------- */
{
    float32 pi = 3.1415927;
    float32 y;
    y = 1.0f / (sqrt(2*pi)*sigma) * exp(-(x*x)/(2*sigma*sigma));
    return y;
}
/* --------------------------------------------- */
float32 gauss2(float32 sigma, float32 x, float32 y)
/* --------------------------------------------- */
{
    float32 pi = 3.1415927;
    float32 g;
    g = 1.0f / (sqrt(2*pi)*sigma) * exp(-(x*x +y*y)/(2*sigma*sigma));
    return g;
}

/* --------------------- */
double cpp(double t, int n)
/* --------------------- */
{
    double c = n;
    double cpp = t * FREQ / c;
    return cpp;
}
