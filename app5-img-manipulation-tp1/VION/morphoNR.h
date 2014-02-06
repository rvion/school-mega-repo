/* ------------------ */
/* --- morphoNR.h --- */
/* ------------------ */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __MORPHO_NR_H__
#define __MORPHO_NR_H__

#ifdef __cplusplus
extern "C" {
#endif

uint8** alloc_structuring_element(int i0, int i1, int j0, int j1);
void free_structuring_element    (uint8 **SE, int i0, int i1, int j0, int j1);
void display_structuring_element (uint8 **SE, int i0, int i1, int j0, int j1, char *format, char *name);

void binary_erosion_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void binary_dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void binary_opening_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void binary_closing_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
    
void erosion_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void opening_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void closing_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);

void alternate_sequential_filter_opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);
void alternate_sequential_filter_closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y);

#ifdef __cplusplus
}
#endif

#endif // __MORPHO_NR_H__
