/* --------------- */
/* --- lutNR.h --- */
/* --------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __LUT_NR_H__
#define __LUT_NR_H__

#ifdef __cplusplus
extern "C" {
#endif


uint8* alloc_ui8lut(void);
void free_ui8lut(uint8 *L);
void zero_ui8lut(uint8 *L);    

void display_ui8lut(uint8 *L, char *format, char *name);

void init_ui8lut(uint8 *L, uint8 threshold, uint8 value);
void apply_ui8lut(uint8 **X, int i0, int i1, int j0, int j1, uint8 *L, uint8 **Y);

    
void binary_threshold_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 threshold, uint8 **Y);
void        threshold_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 threshold, uint8 value, uint8 **Y);

void ui32histogram_equalize_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
    

// double the value of each pixel: X[i][j] *= 2
void double_intensity_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y); 

void gray2bin_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);// [0..255] -> [0..1]
void bin2gray_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);// [0..1] -> [0..255]


#ifdef __cplusplus
}
#endif

#endif // __LUT_NR_H__