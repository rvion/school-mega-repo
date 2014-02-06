/* -------------- */
/* --- muti.h --- */
/* -------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __MUTIL_H__
#define __MUTIL_H__

#include "def.h"

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif


#define FREQ 2.3e9

#define CHRONO(X,dt) tmin = 1e10; for(r=0; r<run; r++) { t0 = chrono(); for(i=0;i<iter;i++) X;  t1 = chrono(); dt = t1-t0; if(dt<tmin) tmin = dt; } dt = dt*FREQ/(iter*n)

uint8 ui8min2(uint8 x0, uint8 x1);
uint8 ui8min3(uint8 x0, uint8 x1, uint8 x2);
uint8 ui8min4(uint8 x0, uint8 x1, uint8 x2, uint8 x3);

uint8 ui8max2(uint8 x0, uint8 x1);
uint8 ui8max3(uint8 x0, uint8 x1, uint8 x2);
uint8 ui8max4(uint8 x0, uint8 x1, uint8 x2, uint8 x3);

uint16 ui16min2(uint16 x0, uint16 x1);
uint16 ui16min3(uint16 x0, uint16 x1, uint16 x2);
uint16 ui16min4(uint16 x0, uint16 x1, uint16 x2, uint16 x3);

uint16 ui16max2(uint16 x0, uint16 x1);
uint16 ui16max3(uint16 x0, uint16 x1, uint16 x2);
uint16 ui16max4(uint16 x0, uint16 x1, uint16 x2, uint16 x3);

/*
uint8 ui8rand(void);
uint32 ui32rand(void);
uint32 f32rand(void);

void rand_ui8vector(uint8 *X, int i0, int i1);
void rand_ui32vector(uint32 *X, int i0, int i1);
void rand_f32vector(float32 *X, int i0, int i1);

int getIter(int size);
int getIterAV(int size);

float32 gauss(float32 sigma, float32 x);
float32 gauss2(float32 sigma, float32 x, float32 y);

double cpp(double t, int n);
*/
    
#ifdef __cplusplus
}
#endif

#endif /* __TRI_H__ */
