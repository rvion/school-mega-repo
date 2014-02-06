/* ------------------- */
/* --- contourNR.h --- */
/* ------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __CONTOUR_NR_H__
#define __CONTOUR_NR_H__

#ifdef __cplusplus
extern "C" {
#endif

void roberts_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
void sobel_ui8matrix  (uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
void fgl_ui8matrix    (uint8 **X, int i0, int i1, int j0, int j1, float32 alpha, uint8 **Y);

void max_dir_ui8matrix    (uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);
void max_dir_ext_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y);

#ifdef __cplusplus
}
#endif

#endif // __CONTOUR_NR_H__