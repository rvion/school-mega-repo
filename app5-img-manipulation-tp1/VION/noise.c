/* --------------- */
/* --- noise.h --- */
/* --------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <math.h>

#include "def.h"
#include "random.h"
#include "noise.h"


/* ------------------------------------------------ */
float32 gaussian_noise(float32 average, float32 sigma)
/* ------------------------------------------------ */
{
    // not thread safe
    
    static long seed = 0x101; // not for multi-threaded purpose
    float g, r;

    g = gasdev(&seed);
    r = average + sigma * g;
    
    return r;
}
/* -------------------------------------------------------------------------------------------- */
void gaussian_noise_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, float32 sigma, uint8 **Y)
/* -------------------------------------------------------------------------------------------- */
{
    int i, j;
    float32 x, y, g;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            x = X[i][j];
            g = gaussian_noise(0.0f, sigma);
            y = x + g;
            if(y<0.0f) y = 0.0f;
            if(y>255.0f) y = 255.0f;
            Y[i][j] = (uint8) y;
        }
    }
}
/* --------------------------------------------------------------------------------------------- */
void impulse_noise_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, float32 percent, uint8 **Y)
/* --------------------------------------------------------------------------------------------- */
{
    int i, j;
    float32 r;
    
    static long seed = 0x101; // not for multi-threaded purpose
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            r = ran1(&seed);
            if(r>percent) {
                Y[i][j] = X[i][j];
            } else {
                Y[i][j] = 255;
            }
        }
    }
}
/* ------------------------------------------------------------------------- */
float32 mean_square_error(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ------------------------------------------------------------------------- */
{
    int i, j;
    float32 x, y;
    float32 se, n, mse;
    
    n = (i1-i0+1)*(j1-j0+1);
    
    se = 0.0f;
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            x = X[i][j];
            y = Y[i][j];
            se += (x-y)*(x-y);
        }
    }
    mse = se / n;
    return mse;
}
/* ------------------------------------------------------------ */
float32 psnr(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* ------------------------------------------------------------ */
{
    float32 mse;
    float32 psnr;
    
    mse = mean_square_error(X, i0, i1, j0, j1, Y);
    if(mse != 0.0f) {
        psnr = 10 * (log10(255*255) / log10(mse));
    } else {
        psnr = 0.0;
    }
    return psnr;
}
