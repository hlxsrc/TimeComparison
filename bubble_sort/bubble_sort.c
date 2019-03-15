/*
 * Name: bubble_sort.c
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

#define MAX_STRING_LEN 80

char path[MAX_STRING_LEN] = "";

/* Serial functions */
void bubbleSort(int arr[], int n);
void swap(int *xp, int *yp);
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
    
    bubbleSort(arr, n); 
    
    // Gets the name of output file
    file_name = stringComposer(n,0);
    
    arrToFile(file_name,arr,n); 
    return 0; 
} 
 
/*-------------------------------------------------------------------
 * Function:  bubbleSort
 * Purpose:   implements bubbleSort algorithm, uses swap to swapp the 
 *            adjacent elements if they are in the wrong order
 */
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
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
