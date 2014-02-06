# APP5 TP1 filtrage images

#### Rémi Vion

Toutes les images sont dans le dossier VION/images

### Introduction

Le but de ce TP est de d’implanter en C différentes opérateurs de TI et de les tester sur des images réelles et de synthèse.


### Travail à faire

    ajouter les codes d’opérateurs manquant dans les fichiers filterNRC, lutNRC et morphoNR.

Fait, sauf pour la FGL

    ajouter des noms d’images à traiter ou à retraiter (image avec bruit gaussien ou avec bruit impul- sionnel) dans les fonctions test_.

Fait

    ajouter des nouveaux appels à des fonctions de traitement (nouvelle valeur de paramètre) dans les fonctions routine_.

Fait

### Bruitage

    Les fonctions de bruitage (bruit gaussien, bruit impulsionnel) sont fournies, tout comme la fonction pour générer des images contenant un carré dont le niveau de gris est séparé de celui du fond d’un certain écart.

    Bruiter les images de synthèse avec du bruit gaussien et du bruit impulsionnel. Un exemple est fourni, en faire d’autres.
    qu’observe-t-on ?

On observe que les images générées sont bruitées
Les différents débuitages marchent plus ou moins bien selon les types de buitage et de combien les images ont été buitées.

### Débruitage

    Coder la fonction effectuant un opérateur de lissage de type moyenneur (average en anglais) en s’inspirant du lissage gaussien fourni.
    Coder la fonction effectuant un opérateur de lissage de type médian (basé sur un tri classique).
    tester les filtres de débruitage sur du bruit additionnel ou du bruit impulsionnel

```cpp

/* ------------------------------------------------- */
void sort_selection_ui8vector(uint8 *X, int i0, int i1)
/* ------------------------------------------------- */
{
    int c,d;
    uint8 swap;
    for (c = i0; c < i1; c++) {
        for (d = i0 ; d < i1 - c; d++) {
            if (X[d] > X[d+1]){
            /* For decreasing order use < */
                swap = X[d];
                X[d] = X[d+1];
                X[d+1] = swap;
            }
        }
    }
}
/* --------------------------------------------------------------------------------- */
void median_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* --------------------------------------------------------------------------------- */
{
    int i, j;
    int ii, jj;
    int k;
    uint8 **T;
    float32 y;
    uint8 *vec;
    vec = ui8vector(0,(2*radius+1)*(2*radius+1));
    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            k = 0;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    //y += T[i+ii][j+jj] * K[ii][jj];
                    vec[k]= T[i+ii][j+jj];//X[ii][jj];
                    k ++;
                }
            }
            if(y<0.0f) y = 0.0f;
            if(y>255.0f) y = 255.0f;

            sort_selection_ui8vector(vec,0,k);
            Y[i][j] = (uint8) vec[radius*radius];
        }
    }
    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    //free_ui8vector(vec);
}
```

### Détection de contours

    Coder la fonction effectuant le calcul de la norme L1 du gradient de FGL.
    Tester les deux opérateurs sur des images sans bruit, puis avec bruit.
    Seuiller les images (soit avec un seuil manuel, soit avec l’opérateur d’Otsu).

voici mon sobel:

```cpp
/* -------------------------------------------------------------------- */
void sobel_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, uint8 **Y)
/* -------------------------------------------------------------------- */
{
    int i, j;
    int ii, jj;

    uint8 **T;
    float32 y;

    sint8 **Kx;
    Kx = si8matrix(-1,1, -1, 1);
    Kx[-1][-1]=-1;
    Kx[0][-1]=-2;
    Kx[1][-1]=-1;

    Kx[-1][0]=0;
    Kx[0][0]=0;
    Kx[1][0]=0;

    Kx[-1][1]=1;
    Kx[0][1]=2;
    Kx[1][1]=1;

    sint8 **Ky;
    Ky = si8matrix(-1,1, -1, 1);
    Ky[-1][-1]=-1;
    Ky[0][-1]=0;
    Ky[1][-1]=1;

    Ky[-1][0]=-2;
    Ky[0][0]=0;
    Ky[1][0]=2;

    Ky[-1][1]=-1;
    Ky[0][1]=0;
    Ky[1][1]=1;


    T = ui8matrix(i0-1, i1+1, j0-1, j1+1);
    zero_ui8matrix(T, i0-1, i1+1, j0-1, j1+1);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, 1);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {

            y = 0.0f;
            for(ii=-1; ii<=1; ii++) {
                for(jj=-1; jj<=1; jj++) {
                    y += T[i+ii][j+jj] * Kx[ii][jj];
                }
            }
            Y[i][j] = (uint8) fabs(y/8);
        }
    }

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {

            y = 0.0f;
            for(ii=-1; ii<=1; ii++) {
                for(jj=-1; jj<=1; jj++) {
                    y += T[i+ii][j+jj] * Ky[ii][jj];
                }
            }
            
            Y[i][j] += (uint8) fabs(y/8);
            if(Y[i][j]<0.0f) Y[i][j] = 0.0f;
            if(Y[i][j]>255.0f) Y[i][j] = 255.0f;
        }
    }

    free_ui8matrix(T, i0-1, i1+1, j0-1, j1+1);
    free_ui8matrix(Kx, -1, 1, -1, 1);
    free_ui8matrix(Ky, -1, 1, -1, 1);
}
```

Il marche bien,

### Morphologie Mathématique

    Implanter les opérateurs suivants :
        érosion et dilatation, pour des images binaires et en niveaux de gris,
        ouverture et fermeture (qui réaliseront des appels aux fonctions précédentes),
        filtres alternés séquentiels, basés sur un ensembles d’ouverture et sur un ensemble de fermetures
    tester les différents opérateurs sur des images avec ou sans bruit impulsionnel.

tout est dans le fichier

    morphoNR.c

```cpp

/* ----------------------------------------------------------- */
uint8** alloc_structuring_element(int i0, int i1, int j0, int j1)
/* ----------------------------------------------------------- */
{
    uint8 **SE;
    SE = ui8matrix(i0, i1, j0, j1);
    return SE;
}
/* ------------------------------------------------------------------- */
void free_structuring_element(uint8 **SE, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------------- */
{
    free_ui8matrix(SE, i0, i1, j0, j1);
}
/* ------------------------------------------------------------------------------------------------ */
void display_structuring_element(uint8 **SE, int i0, int i1, int j0, int j1, char *format, char *name)
/* ------------------------------------------------------------------------------------------------ */
{
    display_ui8matrix(SE, i0, i1, j0, j1, format, name);
}
/* ----------------------------------------------------------------------------------------- */
void binary_erosion_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------------- */
{
    //commentme
    // work only for black and white images
    int i, j;
    int ii, jj;

    uint8 **T;
    uint8 y;

    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            y=1;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    y = y & T[i+ii][j+jj];
                }
            }
            Y[i][j] = (uint8) y;
        }
    }

    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
}
/* ----------------------------------------------------------------------------------------- */
void binary_dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------------- */
{
    //commentme finishme
    // X should be in [0,1]
    int i, j;
    int ii, jj;

    uint8 **T;
    uint8 y;

    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            y = 0;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    y = y | T[i+ii][j+jj];
                }
            }
            Y[i][j] = (uint8) y;
        }
    }

    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
}
/* ------------------------------------------------------------------------------------------ */
void binary_closing_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------ */
{
    //commentme
    binary_dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    binary_erosion_ui8matrix (Y, i0, i1, j0, j1, radius, Y);
}
/* ------------------------------------------------------------------------------------------ */
void binary_opening_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------ */
{
    //commentme
    binary_erosion_ui8matrix (X, i0, i1, j0, j1, radius, Y);
    binary_dilation_ui8matrix(Y, i0, i1, j0, j1, radius, Y);
}
/* ---------------------------------------------------------------------------------- */
void erosion_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
    //commentme finishme
    int i, j;
    int ii, jj;

    uint8 **T;
    uint8 y;

    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {

            y = 255;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    y = y & T[i+ii][j+jj];
                }
            }
            Y[i][j] = (uint8) y;
        }
    }


    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
}
/* ----------------------------------------------------------------------------------- */
void dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------- */
{
    //commentme finishme
    int i, j;
    int ii, jj;

    uint8 **T;
    uint8 y;

    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius);
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            y=0;
            for(ii=-radius; ii<=radius; ii++) {
                for(jj=-radius; jj<=radius; jj++) {
                    y = y | T[i+ii][j+jj];
                }
            }
            Y[i][j] = (uint8) y;
        }
    }



    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
}
/* ---------------------------------------------------------------------------------- */
void closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
    //commentme
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    erosion_ui8matrix (Y, i0, i1, j0, j1, radius, Y);
}
/* ---------------------------------------------------------------------------------- */
void opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
    //commentme
    erosion_ui8matrix (X, i0, i1, j0, j1, radius, Y);
    dilation_ui8matrix(Y, i0, i1, j0, j1, radius, Y);
}
/* -------------------------------------------------------------------------------------------------------------- */
void alternate_sequential_filter_opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* -------------------------------------------------------------------------------------------------------------- */
{
    int r;

    for(r=1; r<=radius; r++) {
        if(r==1) {opening_ui8matrix(X, i0, i1, j0, j1, r, Y);}
        else {opening_ui8matrix(Y, i0, i1, j0, j1, r, Y);}
    }
}
/* -------------------------------------------------------------------------------------------------------------- */
void alternate_sequential_filter_closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* -------------------------------------------------------------------------------------------------------------- */
{
    int r;

    for(r=1; r<=radius; r++) {
        if(r==1) {closing_ui8matrix(X, i0, i1, j0, j1, r, Y);}
        else {closing_ui8matrix(Y, i0, i1, j0, j1, r, Y);}
    }
}
```

les fonctions de test marchent aussi,
J'ai ajouté un morpho dilatation 6 dans le code pour essayer de bien fermer le contour/carre64_GN_01_S_T_064.pgm
