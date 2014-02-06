/* ------------------ */
/* --- filetrNR.h --- */
/* ------------------ */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __FILTER_NR_H__
#define __FILTER_NR_H__

#ifdef __cplusplus
extern "C" {
#endif

float32** alloc_kernel(int radius);
void free_kernel(float32 **K, int radius);
void display_kernel(float32 **K, int radius, char *format, char *name);
    
void init_gaussian_kernel(float32 **K, int radius, int sigma);
void init_average_kernel(float32 **K, int radius);
    
void convolve_kernel_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, float32 **K, int radius, uint8 **Y);

void median_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);

    
void median3_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
void moyen_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int W,  uint8 **Y);


#ifdef __cplusplus
}
#endif

#endif // __FILTER_NR_H__