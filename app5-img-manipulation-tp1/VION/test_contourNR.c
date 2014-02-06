/* ------------------------ */
/* --- test_contourNR.c --- */
/* ------------------------ */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>

#include "def.h"
#include "nrutil.h"
#include "noise.h"
#include "lutNR.h"
#include "histogramNR.h"
#include "contourNR.h"
#include "my_paths.h"

/* ------------------------------------------------------------ */
void routine_sobel(char *src_path, char *filename, char *dst_path)
/* ------------------------------------------------------------ */
{
    char complete_filename[1024];
    char *sep = "_S";
    uint8 **X, **Y;
    long i0, i1, j0, j1;
    
    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);
    
    sobel_ui8matrix(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_extension(dst_path, filename, sep, "pgm", complete_filename); puts(complete_filename);
    double_intensity_ui8matrix(Y, i0, i1, j0, j1, Y);
    
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    free_ui8matrix(Y, i0, i1, j0, j1);
}    
/* --------------- */
void test_sobel(void)
/* --------------- */
{
    char *noise_path   = IMAGE_NOISE_PATH;
    char *denoise_path = IMAGE_DENOISE_PATH;
    char *contour_path = IMAGE_CONTOUR_PATH;
    
    puts("------------------------");
    puts("--- test_sobel part1 ---");
    puts("------------------------");
    
    
    routine_sobel(noise_path,   "carre64_GN_01",      contour_path);
    // routine_sobel(denoise_path, "carre64_IN_005_M_1", contour_path);
    
    routine_sobel(noise_path,   "carre16_GN_02",      contour_path);
    routine_sobel(denoise_path, "carre16_IN_005_M_1", contour_path);

    routine_sobel(noise_path, "carre16_GN_05", contour_path);
    routine_sobel(noise_path, "carre16_GN_10", contour_path);    
}
/* ---------------------------------------------------------- */
void routine_fgl(char *src_path, char *filename, char *dst_path)
/* ---------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep1 = "_FGL_";
    char *sep2 = "_FGLG_";
    int k;
    int ndigit = 2;
    uint8 **X, **Y, **Z;
    long i0, i1, j0, j1;
    
    float32 alpha;
    
    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);
    Z = ui8matrix(i0, i1, j0, j1);
    
    /*alpha = 0.4; // parametre
    k = (int) (10*alpha);
    fgl_ui8matrix(X, i0, i1, j0, j1, alpha, Y);
    //roberts_ui8matrix(Y, i0, i1, j0, j1, Z);
    sobel_ui8matrix(Y, i0, i1, j0, j1, Z);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep1, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep2, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Z, i0, i1, j0, j1, complete_filename);*/
    
    alpha = 0.8; // parametre
    k = (int) (10*alpha);
    fgl_ui8matrix(X, i0, i1, j0, j1, alpha, Y);
    roberts_ui8matrix(Y, i0, i1, j0, j1, Z);
    //sobel_ui8matrix(Y, i0, i1, j0, j1, Z);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep1, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep2, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Z, i0, i1, j0, j1, complete_filename);
    
    double_intensity_ui8matrix(Z, i0, i1, j0, j1, Z);
    double_intensity_ui8matrix(Z, i0, i1, j0, j1, Z);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, "VISU", k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Z, i0, i1, j0, j1, complete_filename);
    
    // free
    free_ui8matrix(X, i0, i1, j0, j1);
    free_ui8matrix(Y, i0, i1, j0, j1);
}    
/* ------------- */
void test_fgl(void)
/* ------------- */
{
    char *src_path     = IMAGE_SRC_PATH;
    char *noise_path   = IMAGE_NOISE_PATH;
    char *denoise_path = IMAGE_DENOISE_PATH;
    char *contour_path = IMAGE_CONTOUR_PATH;
    
    puts("------------------------");
    puts("--- test_fgl part1 ---");
    puts("------------------------");
    
    // seuillage sans pre-traitement
    //routine_fgl(noise_path, "carre8_GN_01", contour_path);
    
    routine_fgl(src_path,     "carre64",            contour_path);
    routine_fgl(noise_path,   "carre64_GN_01",      contour_path);
    routine_fgl(denoise_path, "carre64_IN_005_M_1", contour_path);
    
  }
/* ----------------------------------------------------------------------------------------- */
void routine_contour_threshold(char *src_path, char *filename, uint8 threshold, char *dst_path)
/* ----------------------------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep;
    int k;
    int optimal_threhsold;
    int ndigit = 3; // nombre de chiffres pour coder le seuil
    uint8 value = 255;
    uint8 **X, **Y;
    long i0, i1, j0, j1;
    
    puts("=================================");
    printf(" === %s ===\n", filename);
    puts("=================================");
    
    k = threshold;
    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);
    
    display_ui8matrix(X, i0, i1, j0, j1, "%4d", filename);
        
    puts("\n=============================================\n");
    
    sep = "_T_";
    threshold_ui8matrix(X, i0, i1, j0, j1, threshold, value, Y);
    display_ui8matrix(Y, i0, i1, j0, j1, "%4d", "Thresold");
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    
    puts("\n=============================================\n");
    
    sep = "_OTSU_";
    optimal_threhsold = calc_otsu_threshold_ui8matrix(X, i0, i1, j0, j1);
    k = optimal_threhsold;
    threshold_ui8matrix(X, i0, i1, j0, j1, optimal_threhsold, value, Y);
    display_ui8matrix(Y, i0, i1, j0, j1, "%4d", "Otsu threshold");   
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
   
    free_ui8matrix(Y, i0, i1, j0, j1);
}    
/* --------------------------- */
void test_contour_threshold(void)
/* --------------------------- */
{
    char *noise_path = IMAGE_CONTOUR_PATH;
    char *src_path     = IMAGE_SRC_PATH;
    //char *denoise_path = IMAGE_CONTOUR_PATH;
    char *threshold_path = IMAGE_CONTOUR_PATH;
    
    puts("----------------------------");
    puts("--- test_threshold part1 ---");
    puts("----------------------------");
    
    // routine_contour_threshold(noise_path, "carre64_GN_01_FGLG_08", 12, threshold_path);
    routine_contour_threshold(noise_path, "carre64_GN_01_S", 64, threshold_path);
    // routine_contour_threshold(noise_path, "carre64_GN_01_S", 20, threshold_path);
}
/* ------------------------------------------- */
int test_contourNR(int argc, const char * argv[])
/* ------------------------------------------- */
{
    puts("======================");
    puts("=== test_contourNR ===");
    puts("======================");
    
    test_sobel();
    // test_fgl();
    
    test_contour_threshold();
    return 0;
}
