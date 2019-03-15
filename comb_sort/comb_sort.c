/*
 * Name: comb_sort.c
 * Objetive: Sort numbers using bubble sort algorithm
 * Input: an .inp file with values to be sorted
 * Output: .inp file with the random numbers already sorted
 * Notes: 
 *        
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LEN 80

char path[MAX_STRING_LEN] = "";

/* Serial functions */
void combSort(int arr[], int n);
void swap(int *xp, int *yp);
int getNextGap(int gap);
void arrToFile(char *name, int *array, int size);
char* stringComposer(int n, int mode);
void usage (char* prog_name);

/* Main function */
int main(int argc, char** argv)
{ 
    int i, n;
    int *arr;
    char* file_name;
    
    FILE *fp;
    
    clock_t start, end;
    double cpu_time_used;
    
    int file_status=1;
       
    // Receives arguments
    if (argc != 2)
      usage(argv[0]);

    n = atoi(argv[1]);
        
    // Gets the name of input file
    file_name = stringComposer(n,1);
    
    // Extracts data from input file
    if ((fp = fopen (file_name, "r")) == NULL){
        file_status = 0;
    }

    if(file_status != 0) {
                
        // Creates dynamic array
        arr = malloc(n * sizeof *arr);
        
        for (i = 0; i < n; i++)
            fscanf(fp, "%d", &arr[i]);
        
        fclose(fp);
    }
    
    // Measures the time 
    start = clock();
    /* Bubble sort starts */
    combSort(arr, n); 
    /* Bubble sort finishes */
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    FILE *time_dat = fopen("time.dat", "a+");
    fprintf(time_dat, "%d %.7f\n", n, cpu_time_used);
    fclose(time_dat);
    
    // Gets the name of output file
    file_name = stringComposer(n,0);
    
    arrToFile(file_name,arr,n); 
    return 0; 
} 
 
/*-------------------------------------------------------------------
 * Function:  combSort
 * Purpose:   implements combSort algorithm, uses swap to swapp the 
 *            adjacent elements if they are in the wrong order
 */
void combSort(int a[], int n) 
{ 
    // Initialize gap 
    int gap = n; 
  
    // Initialize swapped as true to make sure that 
    // loop runs 
    bool swapped = true; 
  
    // Keep running while gap is more than 1 and last 
    // iteration caused a swap 
    while (gap != 1 || swapped == true) 
    { 
        // Find next gap 
        gap = getNextGap(gap); 
  
        // Initialize swapped as false so that we can 
        // check if swap happened or not 
        swapped = false; 
  
        // Compare all elements with current gap 
        for (int i=0; i<n-gap; i++) 
        { 
            if (a[i] > a[i+gap]) 
            { 
                swap(&a[i], &a[i+gap]); 
                swapped = true; 
            } 
        } 
    } 
} 

/*-------------------------------------------------------------------
 * Function:  swap
 * Purpose:   swaps the adjacent elements 
 */
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

/*-------------------------------------------------------------------
 * Function:  getNextGap
 * Purpose:   find gap between elements 
 */
int getNextGap(int gap) 
{ 
    // Shrink gap by Shrink factor 
    gap = (gap*10)/13; 
  
    if (gap < 1) 
        return 1; 
    
    return gap; 
} 

/*-------------------------------------------------------------------
 * Function:  rngToFile
 * Purpose:   writes random numbers to a file
 */
void arrToFile(char *name, int *array, int size)
{
    FILE *numbers=fopen(name, "w");
    int j=0;

    for(j=0;j<size;j++)
    {
        fprintf(numbers, "%d\n", array[j]);
    }

    fclose(numbers);
}

/*------------------------------------------------------------------
 * Function:  stringComposer
 * Purpose:   joins the strings that will compose the name of the file
 * In arg :   prog_name
 */
char* stringComposer(int n, int mode) 
{
    char input[MAX_STRING_LEN] = "/home/hlxs/ada/input/";
    char output[MAX_STRING_LEN] = "output/";
    char ext[MAX_STRING_LEN] = ".inp";
    char sn[MAX_STRING_LEN] = "";
    memset(path,0,strlen(path));
   
    if (mode == 0)
        strcat(path,output);
    else   
        strcat(path,input);
       
    // Convert int to string
    sprintf(sn, "%d", n);
    
    // Join two strings
    strcat(sn, ext);
    strcat(path,sn);
        
    return path;
} 

/*------------------------------------------------------------------
 * Function:  usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void usage (char* prog_name) 
{
   fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
   exit(0);
}  
