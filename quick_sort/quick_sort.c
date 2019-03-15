/*
 * Name: quick_sort.c
 * Objetive: Sort numbers using quick sort algorithm
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
void quickSort(int arr[], int low, int high);
int partition (int arr[], int low, int high);
void swap(int* a, int* b);
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
    /* Quick sort starts */
    quickSort(arr, 0, n-1); 
    /* Quick sort finishes */
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
 * Function:  quickSort
 * Purpose:   implements quickSort algorithm
 *            arr[] --> Array to be sorted, 
 *            low  --> Starting index, 
 *            high  --> Ending index 
 */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}

/*-------------------------------------------------------------------
 * Function:  partition
 * Purpose:   This function takes last element as pivot, places 
 *            the pivot element at its correct position in sorted 
 *            array, and places all smaller (smaller than pivot) 
 *            to left of pivot and all greater elements to right 
 *            of pivot
 */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

/*-------------------------------------------------------------------
 * Function:  swap
 * Purpose:   swap two elements 
 */
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
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
