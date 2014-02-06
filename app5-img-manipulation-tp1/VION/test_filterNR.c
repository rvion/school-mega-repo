/* ----------------------- */
/* --- test_filterNR.c --- */
/* ----------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>

#include "def.h"
#include "nrutil.h"
#include "noise.h"
#include "filterNR.h"
#include "lutNR.h"
#include "histogramNR.h"
#include "my_paths.h"

/* ------------------------------------------------ */
float32 calc_sigma(float32 S, float32 Sx, float32 Sxx)
/* ------------------------------------------------ */
{
    return sqrt((S*Sxx - Sx*Sx)/(S*S));
}
/* ------------------------------------ */
void test_gaussian_noise_computation(void)
/* ------------------------------------ */
{
    int i;
    int n = 10000;
    float32 x, sx, sxx;

    sx = 0.0f; sxx = 0.0f;
    for(i=0; i<n; i++) {
        x = gaussian_noise(0, 10);
        //printf("%10.4f\n", x);
        sx += x;
        sxx += x*x;
    }
    printf("average = %10.4f sigma = %10.4f\n", sx/n, calc_sigma(n, sx, sxx));

    sx = 0.0f; sxx = 0.0f;
    for(i=0; i<n; i++) {
        x = gaussian_noise(0, 20);
        //printf("%10.4f\n", x);
        sx += x;
        sxx += x*x;
    }
    printf("average = %10.4f sigma = %10.4f\n", sx/n, calc_sigma(n, sx, sxx));
}
/* ---------------- */
void test_kernel(void)
/* ---------------- */
{
    float32 **K;
    int r = 3;

    puts("-------------------");
    puts("--- test_kernel ---");
    puts("-------------------");

    K = alloc_kernel(r);
    init_gaussian_kernel(K, r, 2.0f);
    display_kernel(K, r, "%8.3f", "K");

    init_average_kernel(K, r);
    display_kernel(K, r, "%8.3f", "K");
}

/* ------------------------------------------------------------------------------------------ */
void routine_generate_sample(uint8 background, uint8 foreground, char *filename, char *dst_path)
/* ------------------------------------------------------------------------------------------ */
{
    // creation d'un carre d'intensite foreground sur un fond d'intensite background
    char complete_filename[1024];

    //int i, j;
    long size = 32;
    long i0, i1, j0, j1;
    uint8 **X;

    i0 = 0;
    i1 = size-1;
    j0 = 0;
    j1 = size-1;

    X = ui8matrix(0, size-1, 0, size-1);

    init_ui8matrix_param(X, 0, size-1, 0, size-1, background, 0, 0);
    init_ui8matrix_param(X, size/4, size-1-size/4, size/4, size-1-size/4, foreground, 0, 0);

    generate_path_filename_extension(dst_path, filename, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(X, 0, size-1, 0, size-1, complete_filename);

    free_ui8matrix(X, 0, size-1, 0, size-1);
}
/* -------------------- */
void generate_sample(void)
/* -------------------- */
{
    // generates perfect images

    char *dst_path;

    puts("---------------------------");
    puts("--- test_gaussian_noise ---");
    puts("---------------------------");

    dst_path = IMAGE_SRC_PATH;

    puts("\nstart generation");
    routine_generate_sample(128-8/2,  128+8/2,  "carre8",  dst_path);
    routine_generate_sample(128-16/2, 128+16/2, "carre16", dst_path);
    routine_generate_sample(128-32/2, 128+32/2, "carre32", dst_path);
    routine_generate_sample(128-64/2, 128+64/2, "carre64", dst_path);
    puts("done generating\n");
}
/* --------------------------------------------------------------------- */
void routine_gaussian_noise(char *src_path, char *filename, char *dst_path)
/* --------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep = "_GN_"; // Gaussian Noise
    int sigma;
    int ndigit = 2; // codage sur 2 chiffres de la valeur de sigma dans le nom du fichier
    long i0, i1, j0, j1;
    uint8 **X, **Y;
    float32 p;

    // chargement de l'image sans bruit dans X
    // Y doit contenir l'image traitee
    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);


    sigma = 1; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // ajouter ici d'autre instances du bloc de code avec d'autres valeurs de sigma

    sigma = 2; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    sigma = 3; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    sigma = 4; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    sigma = 5; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    sigma = 10; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    sigma = 20; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    sigma = 30; // parametre du bloc de code
    gaussian_noise_ui8matrix(X, i0, i1, j0, j1, (float32) sigma, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, sigma, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // liberation de la memoire
    free_ui8matrix(X, i0, i1, j0, j1);
    free_ui8matrix(Y, i0, i1, j0, j1);
}
/* ------------------------ */
void test_gaussian_noise(void)
/* ------------------------ */
{
    // generates noised images

    char *src_path;
    char *dst_path;

    puts("---------------------------");
    puts("--- test_gaussian_noise ---");
    puts("---------------------------");

    src_path = IMAGE_SRC_PATH;
    dst_path = IMAGE_NOISE_PATH;

    routine_gaussian_noise(src_path, "carre8", dst_path); puts("");
    // ajouter le nom d'autre images a traiter

    routine_gaussian_noise(src_path, "carre16", dst_path); puts("");
    routine_gaussian_noise(src_path, "carre32", dst_path); puts("");
    routine_gaussian_noise(src_path, "carre64", dst_path); puts("");
    
    routine_gaussian_noise(src_path, "lena",    dst_path); puts("");
    routine_gaussian_noise(src_path, "bureau",  dst_path); puts("");
    routine_gaussian_noise(src_path, "IceteaG", dst_path); puts("");
    routine_gaussian_noise(src_path, "IceteaB", dst_path); puts("");
}
/* ---------------------------------------------------------------------- */
void routine_impulse_noise(char *src_path, char *filename, char *noise_path)
/* ---------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep = "_IN_"; // Impulse Noise
    float32 percent;
    int ndigit = 3; // codage du 3 chiffres du pourcentage de bruit impulsionnel dans le nom du fichier
    long i0, i1, j0, j1;
    uint8 **X, **Y;
    float32 p;

    // chargement de l'image et allocation d'une image avec des bords
    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    percent = 0.5f; // parametre du bloc de code
    //printf("%4d : ",(int)(10.0f*percent));
    impulse_noise_ui8matrix(X, i0, i1, j0, j1, percent/100.0f, Y);
    p = psnr(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(noise_path, filename, sep, (int)(10.0f*percent), ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);


    // ajouter ici d'autre instances du bloc de code avec d'autres valeurs de percent

 }
/* ----------------------- */
void test_impulse_noise(void)
/* ----------------------- */
{
    // generates noised images

    char *src_path;
    char *noise_path;

    puts("--------------------------");
    puts("--- test_impulse_noise ---");
    puts("--------------------------");

    src_path = IMAGE_SRC_PATH;
    noise_path = IMAGE_NOISE_PATH;

    routine_impulse_noise(src_path, "carre8",  noise_path); puts("");
    // ajouter le nom d'autre images a traiter

    routine_impulse_noise(src_path, "carre16", noise_path); puts("");
    routine_impulse_noise(src_path, "carre32", noise_path); puts("");
    routine_impulse_noise(src_path, "carre64", noise_path); puts("");
    /*routine_impulse_noise(src_path, "lena",    noise_path); puts("");
    routine_impulse_noise(src_path, "bureau",  noise_path); puts("");*/
}
/* ----------------------------------------------------------------------------------------------------------- */
void routine_smooth_filter(char *src_path, char *noise_path, char *filename0, char *filename, char *denoise_path)
/* ----------------------------------------------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep;

    int k;
    float32 sigma;
    int radius;
    int ndigit;
    long i0, i1, j0, j1;
    uint8 **X0, **X, **Y;
    float32 **K;
    float32 p;

    // chargement de l'image bruitee dans X, et de l'image sans bruit dans X0
    // Y doit contenir l'image traitee
    generate_path_filename_extension(src_path, filename0, "pgm", complete_filename); puts(complete_filename);
    X0 = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    generate_path_filename_extension(noise_path, filename, "pgm", complete_filename); puts(complete_filename);
    X  = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    // ---------------------
    // -- gaussian kernel --
    // ---------------------
    sep = "_G_";
    ndigit = 2; // codage sur 2 chiffre de la valeur de sigma dans le nom du fichier

    sigma = 0.5; // parametre du bloc de code
    k = (int) (10*sigma); // code
    radius = (int) ceil(2*sigma+1);
    printf("sigma = %.1f -> radius = %d\n", sigma, radius);
    K = alloc_kernel(radius);
    init_gaussian_kernel(K, radius, sigma);
    convolve_kernel_ui8matrix(X, i0, i1, j0, j1, K, radius, Y);
    p = psnr(X0, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(denoise_path, filename, sep, k, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    free_kernel(K, radius);

    // -----------------
    // -- average kernel
    // -----------------
    sep = "_A_";
    ndigit = 1; // codage sur 1 chiffre de la valeur de radius dans le nom du fichier

    radius = 1; // parametre du bloc de code
    k = radius; // code
    K = alloc_kernel(radius);
    init_average_kernel(K, radius);
    convolve_kernel_ui8matrix(X, i0, i1, j0, j1, K, radius, Y);
    p = psnr(X0, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(denoise_path, filename, sep, k, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    free_kernel(K, radius);


    // liberation de la memoire
    free_ui8matrix(X0, i0, i1, j0, j1);
    free_ui8matrix(X,  i0, i1, j0, j1);
    free_ui8matrix(Y,  i0, i1, j0, j1);
}
/* ----------------------- */
void test_smooth_filter(void)
/* ----------------------- */
{
    char *src_path;
    char *noise_path;
    char *denoise_path;

    src_path = IMAGE_SRC_PATH;
    noise_path = IMAGE_NOISE_PATH;
    denoise_path = IMAGE_DENOISE_PATH;

    puts("----------------------------------------------");
    puts("--- test_smooth_filter with gaussian noise ---");
    puts("----------------------------------------------");

    // smooth filter for gaussian noise
    routine_smooth_filter(src_path, noise_path, "carre64", "carre64_GN_01", denoise_path);
    // ajouter le nom d'autre images a traiter

   }
/* ----------------------------------------------------------------------------------------------------------- */
void routine_median_filter(char *src_path, char *noise_path, char *filename0, char *filename, char *denoise_path)
/* ----------------------------------------------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep;

    int radius;
    int k;
    int ndigit = 1;
    long i0, i1, j0, j1;
    uint8 **X0, **X, **Y;
    float32 p;

    // chargement de l'image sans bruit dans X0 et de l'image bruitee dans X
    // Y doit contenir l'image traitee
    generate_path_filename_extension(src_path, filename0, "pgm", complete_filename);
    X0 = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    generate_path_filename_extension(noise_path, filename, "pgm", complete_filename);
    X  = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    // -------------------
    // -- median kernel --
    // -------------------
    sep = "_M_";

    radius = 1; // parametre du bloc de code
    k = radius;
    median_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    p = psnr(X0, i0, i1, j0, j1, Y);
    generate_path_filename_sep_k_ndigit_extension(denoise_path, filename, sep, k, ndigit, "pgm", complete_filename);
    printf("%s -> PSNR = %8.2f db\n", complete_filename, p);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    // ajouter ici d'autre instances du bloc de code avec d'autres valeurs de radius
}
/* ----------------------- */
void test_median_filter(void)
/* ----------------------- */
{
    puts("---------------------------");
    puts("--- test_median_filter  ---");
    puts("---------------------------");

    char *src_path;
    char *noise_path;
    char *denoise_path;

    src_path = IMAGE_SRC_PATH;
    noise_path = IMAGE_NOISE_PATH;
    denoise_path = IMAGE_DENOISE_PATH;

    routine_median_filter(src_path, noise_path, "carre8", "carre8_IN_005", denoise_path);
    routine_median_filter(src_path, noise_path, "carre16", "carre16_IN_005", denoise_path);
    routine_median_filter(src_path, noise_path, "carre32", "carre32_IN_005", denoise_path);
    routine_median_filter(src_path, noise_path, "carre64", "carre64_IN_005", denoise_path);
}
/* --------------------------------------------------------------------------------- */
void routine_threshold(char *src_path, char *filename, uint8 threshold, char *dst_path)
/* --------------------------------------------------------------------------------- */
{
    char complete_filename[1024];
    char *sep = "_T_";
    int k;
    int ndigit = 3;
    uint8 value = 255;
    uint8 **X, **Y;
    long i0, i1, j0, j1;

    k = threshold;
    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);

    threshold_ui8matrix(X, i0, i1, j0, j1, threshold, value, Y);
    generate_path_filename_sep_k_ndigit_extension(dst_path, filename, sep, k, ndigit, "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);
    free_ui8matrix(Y, i0, i1, j0, j1);
}
/* ------------------- */
void test_threshold(void)
/* ------------------- */
{
    puts("======================");
    puts("=== test_threshold ===");
    puts("======================");

}
/* -------------------------------- */
void test_histogram_equalization(void)
/* -------------------------------- */
{
    puts("==================================");
    puts("=== test_histogram_equalization===");
    puts("==================================");

    long i0, i1, j0, j1;

    char *filename;
    char complete_filename[1024];
    char     *src_path = IMAGE_SRC_PATH;
    char   *noise_path = IMAGE_NOISE_PATH;
    char *denoise_path = IMAGE_DENOISE_PATH;

    uint8 **X, **Y;

    filename = "carre64_GN_20";

    generate_path_filename_extension(noise_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);
    ui32histogram_equalize_ui8matrix(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_extension(denoise_path, filename, "_HISTO_", "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    // filename = "Hawkes_Bay";
    filename = "femme";

    generate_path_filename_extension(src_path, filename, "pgm", complete_filename); puts(complete_filename);
    X = LoadPGM_ui8matrix(complete_filename, &i0, &i1, &j0, &j1);
    Y = ui8matrix(i0, i1, j0, j1);
    ui32histogram_equalize_ui8matrix(X, i0, i1, j0, j1, Y);
    generate_path_filename_sep_extension(denoise_path, filename, "_HISTO_", "pgm", complete_filename); puts(complete_filename);
    SavePGM_ui8matrix(Y, i0, i1, j0, j1, complete_filename);

    printf("\n -> VOIR FICHIERS DE SORTIES\n");
}
/* -------------- */
void test_otsu(void)
/* -------------- */
{
    // http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
    int t;
    uint32 H[6];

    puts("=================");
    puts("=== test_otsu ===");
    puts("=================");

    H[0] = 8;
    H[1] = 7;
    H[2] = 2;
    H[3] = 6;
    H[4] = 9;
    H[5] = 4;

    printf("\nH[0] = 8;");
    printf("\nH[1] = 7;");
    printf("\nH[2] = 2;");
    printf("\nH[3] = 6;");
    printf("\nH[4] = 9;");
    printf("\nH[5] = 4;");
    t = calc_otsu_threshold_ui32vector(H, 0, 5);
    printf("\n -> threshold = %d\n", t);
}
/* ------------------------------------------ */
int test_filterNR(int argc, const char * argv[])
/* ------------------------------------------ */
{
    puts("=====================");
    puts("=== test_filterNR ===");
    puts("=====================");

    generate_sample(); // guess
    test_gaussian_noise(); // fonctions de bruitage des images
    test_impulse_noise();

    // tests unitaires
    test_kernel();
    
    test_otsu();
    test_histogram_equalization();


    // fonctions de debruitage des images
    test_smooth_filter();
    test_median_filter();

    return 0;
}
