/* -------------- */
/* --- main.c --- */
/* -------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>

#include "test.h"

int main (int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, dWorld!\n");

    test(argc, argv);

    puts("bye ...");
    return 0;
}
