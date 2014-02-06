/* --------------------- */
/* --- histogramNR.h --- */
/* --------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __HISTOGRAM_NR_H__
#define __HISTOGRAM_NR_H__

#ifdef __cplusplus
extern "C" {
#endif

uint32* alloc_ui32histogram(           int i0, int i1);
void     free_ui32histogram(uint32* H, int i0, int i1);

void    zero_ui32histogram(uint32 *H, int i0, int i1);
void display_ui32histogram(uint32 *H, int i0, int i1, char *format, char *name);
    
void ui32histogram_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint32 *H);

void ui32histogram_equalize_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);

int calc_otsu_threshold_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1);
int calc_otsu_threshold_ui32vector(uint32 *H, int i0, int i1); 

#ifdef __cplusplus
}
#endif

#endif // __LUT_NR_H__