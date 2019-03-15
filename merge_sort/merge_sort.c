/*
 * Name: merge_sort.c
 * Objetive: Sort numbers using merge sort algorithm
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
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
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
    /* Merge sort starts */
    mergeSort(arr, 0, n - 1); 
    /* Merge sort finishes */
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
 * Function:  mergeSort
 * Purpose:   implements mergeSort algorithm, l is for left index 
 *            and r is right index of the sub-array of arr to be sorted
 */

void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

/*-------------------------------------------------------------------
 * Function:  merge
 * Purpose:   Merges two subarrays of arr[]. 
 *            First subarray is arr[l..m] 
 *            Second subarray is arr[m+1..r] 
 */
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
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
