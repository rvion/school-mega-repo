/* -------------- */
/* --- test.c --- */
/* -------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>

#include "test_filterNR.h"
#include "test_contourNR.h"
#include "test_morphoNR.h"

/* ---------------------------------- */
int test (int argc, const char * argv[])
/* ---------------------------------- */
{
    puts("test");// insert code here...
    
    test_filterNR(argc, argv); // bruitage et filtrage 
    test_contourNR(argc, argv); // detection de contour et seuillage
    test_morphoNR(argc, argv); //filtrage morphologique (debruitage, et contour)
    return 0;
}
