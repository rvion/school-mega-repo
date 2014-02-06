/* ----------------------- */
/* --- test_morphoNR.c --- */
/* ----------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>

#include "def.h"
#include "nrutil.h"
#include "morphoNR.h"
#include "my_paths.h"

/* ------------------------------------------------------------------- */
void routine_basic_morpho(char *src_path, char *filename, char *dst_path)
/* ------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep;

    int k;
    int radius;
    int ndigit = 1; // nombre de chiffre pour coder le rayon
    long i0, i1, j0, j1;
    uint8 **X, **Y;

    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    radius = 1; sep = "_E_";
    k = radius;
    erosion_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 2; sep = "_E_";
    k = radius;
    erosion_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 1; sep = "_D_";
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 2; sep = "_D_";
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 3; sep = "_D_";
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 1; sep = "_O_";
    k = radius;
    opening_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 1; sep = "_C_";
    k = radius;
    closing_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    free_ui8matrix(X, i0, i1, j0, j1);
    free_ui8matrix(Y, i0, i1, j0, j1);
}
/* ---------------------- */
void test_basic_morpho(void)
/* ---------------------- */
{
    char *noise_path;
    char *morpho_path;

    puts("-------------------------");
    puts("--- test_basic_morpho ---");
    puts("-------------------------");

    noise_path = IMAGE_NOISE_PATH;
    morpho_path = IMAGE_MORPHO_PATH;

    // a faire sur les carres
    routine_basic_morpho(noise_path, "carre8_IN_005", morpho_path);
}
/* -------------------------------------------------------------------- */
void routine_binary_morpho(char *src_path, char *filename, char *dst_path)
/* -------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep;

    int k;
    int radius;
    int ndigit = 1;
    long i0, i1, j0, j1;
    uint8 **X, **Y;

    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    // ---------------
    // --- erosion ---
    // ---------------
    sep = "_E_";

    radius = 1; // parametre
    k = radius;
    erosion_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ----------------
    // --- dilation ---
    // ----------------
    sep = "_D_";

    radius = 1; // parametre
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 3; // parametre
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ---------------
    // --- opening ---
    // ---------------
    sep = "_O_";

    radius = 1; // parametre
    k = radius;
    opening_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ---------------
    // --- closing ---
    // ---------------
    sep = "_C_";

    radius = 1; // parametre
    k = radius;
    closing_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // free
    free_ui8matrix(X, i0, i1, j0, j1);
    free_ui8matrix(Y, i0, i1, j0, j1);
}
/* ----------------------- */
void test_binary_morpho(void)
/* ----------------------- */
{
    char *contour_path;
    char *morpho_path;

    puts("--------------------------");
    puts("--- test_binary_morpho ---");
    puts("--------------------------");


    contour_path  = IMAGE_CONTOUR_PATH;
    morpho_path = IMAGE_MORPHO_PATH;

    // routine_binary_morpho(contour_path, "carre64_GN_01_FGLG_08_MD_007", morpho_path); puts("");
    routine_binary_morpho(contour_path, "carre64_GN_01_S_T_064",       morpho_path); puts("");
}
/* ------------------------------------------------------------- */
void routine_morpho(char *src_path, char *filename, char *dst_path)
/* ------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep;

    int k;
    int radius;
    int ndigit = 1;
    long i0, i1, j0, j1;
    uint8 **X, **Y;

    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    // ---------------
    // --- erosion ---
    // ---------------
    sep = "_E_";

    radius = 1; // parametre
    k = radius;
    erosion_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ----------------
    // --- dilation ---
    // ----------------
    sep = "_D_";

    radius = 1; // parametre
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    radius = 3; // parametre
    k = radius;
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ---------------
    // --- opening ---
    // ---------------
    sep = "_O_";

    radius = 1; // parametre
    k = radius;
    opening_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ---------------
    // --- closing ---
    // ---------------
    sep = "_C_";

    radius = 1; // parametre
    k = radius;
    closing_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // -------------------------------------------
    // --- alternate sequential filter opening ---
    // -------------------------------------------
    sep = "_ASFO_";
    radius = 1; // parametre
    k = radius;
    alternate_sequential_filter_opening_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // -------------------------------------------
    // --- alternate sequential filter closing ---
    // -------------------------------------------
    sep = "_ASFC_";
    radius = 1; // parametre
    k = radius;
    alternate_sequential_filter_closing_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // free
    free_ui8matrix(X, i0, i1, j0, j1);
    free_ui8matrix(Y, i0, i1, j0, j1);
}
/* ---------------- */
void test_morpho(void)
/* ---------------- */
{
    char *src_path;
    char *noise_path;
    char *morpho_path;

    puts("-------------------");
    puts("--- test_morpho ---");
    puts("-------------------");

    src_path    = IMAGE_SRC_PATH;
    noise_path  = IMAGE_NOISE_PATH;
    morpho_path = IMAGE_MORPHO_PATH;


    routine_morpho(src_path, "lena",    morpho_path); puts("");
    routine_morpho(src_path, "bureau",  morpho_path); puts("");
    routine_morpho(src_path, "IceteaG", morpho_path); puts("");
    routine_morpho(src_path, "IceteaB", morpho_path); puts("");
}
/* ------------------------------------------ */
int test_morphoNR(int argc, const char * argv[])
/* ------------------------------------------ */
{
    puts("=====================");
    puts("=== test_morphoNR ===");
    puts("=====================");

    test_basic_morpho(); // tests unitaires valider les fonctions erosion/dilatation ouverture/fermeture
    test_binary_morpho();
    test_morpho();

    return 0;
}
