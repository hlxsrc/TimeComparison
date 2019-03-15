/*
 * Name: rng.c
 * Objetive: Write random numbers in a txt
 * Input: n will be the number of random numbers to create
 * Output: .inp file with the random numbers already created
 * Notes: rng.c uses "PCG" which is "A Family of Better Random 
 *        Number Generators" in order to create random numbers
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "pcg_basic.h"

#define MAX_STRING_LEN 80

/* Serial functions */
void usage(char* prog_name);
void rngToFile(char *name, int size, int *array);

/* Main function */
int main(int argc, char** argv)
{
    
    int n=10;
    int rounds=5;
    int randomNumber=0;
    bool nondeterministic_seed = false;
    
    int i;
    int *container;
    
    // String that will compose the name of the file
    char ext[MAX_STRING_LEN] = {'.','i','n','p'};
    char sn[MAX_STRING_LEN];

    // Read command-line options
    ++argv;
    --argc;
    if (argc > 0 && strcmp(argv[0], "-r") == 0) {
        nondeterministic_seed = true;
        ++argv;
        --argc;
    }
    if (argc > 0) {
        n = atoi(argv[0]);
    }

    pcg32_random_t rng;

    // pcg32_srandom_r takes two 64-bit constants (the initial state, and the
    // rng sequence selector; rngs with different sequence selectors will
    // *never* have random sequences that coincide, at all) - the code below
    // shows three possible ways to do so.

    if (nondeterministic_seed) {
        // Seed with external entropy -- the time and some program addresses
        // (which will actually be somewhat random on most modern systems).
        pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, 
			      (intptr_t)&rounds);
    } else {
        // Seed with a fixed constant
        pcg32_srandom_r(&rng, 42u, 54u);
    }
    
    // Convert int to string
    sprintf(sn, "%d", n);
    
    // Join two strings
    strcat(sn, ext);
        
    // Creates dynamic array
    container = malloc(n * sizeof *container);
    
    /* Get some ramdom numbers */
    printf("Number:");
    for (i = 0; i < n; ++i) {
        randomNumber = (int)pcg32_boundedrand_r(&rng, 1000);
        printf("%d ", randomNumber);
        container[i] = randomNumber;
    }
    printf("\n");
    rngToFile(sn,n,container);
    
    return 0;
}


/*------------------------------------------------------------------
 * Function:  usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void usage (char* prog_name) {
   fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
   exit(0);
}  

/*-------------------------------------------------------------------
 * Function:  rngToFile
 * Purpose:   writes random numbers to a file
 */
void rngToFile(char *name, int size, int *array)
{
    FILE *numbers=fopen(name, "w");
    int j=0;

    for(j=0;j<size;j++)
    {
        fprintf(numbers, "%d\n", array[j]);
    }

    fclose(numbers);
} 
