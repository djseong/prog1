#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mst-heap.c"
#include "mst.c" 

// struct for vertices with up to 4 dimensions
typedef struct vertex {
    float x;
    float y;
    float z;
    float w;
}vertex;

//generates a random float between 0 and 1, inclusive
float random_float(void)
{
    return (double) rand() / ((double) RAND_MAX);
}

// prints array
void print_array(int height, int width, float **arr)
{
    int i,j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            printf(" %f", arr[i][j]);
        }
        printf("\n");
    }
}

float** generate_matrix (int height, int width, float **arr)
{
    int i,j;   
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            arr[i][j] = random_float();
        }
    }
    
    return arr;
}



int main( int argc, char *argv[] )
{
    srand(time(NULL));

    // sets commandline arguments to variables
    int flag = atoi(argv[1]);
    int numpoints = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int dimension = atoi(argv[4]); 
    float total = 0.0; 

    // for the case where dimension == 0, we will generate one list, but we will treat it differently
    // than we would treat a dimensoion 2 list
    int dim_num = dimension;
    if (dimension == 0)
    {
        dim_num = 1;
    }

    float **array;
    array = malloc(dim_num * sizeof(*array));
    int i;
    for (i = 0; i < dim_num; i++)
    {
        array[i] = malloc(numpoints * sizeof(**array));
    }
    int result = -2; 
    int free_num = dim_num; 
    FILE *fp = stdout; 
   if (flag == 1) {
        result = 0; 
        fp = fopen("result.txt", "a"); 
        if (fp == NULL) {
            printf("error\n");
            return -1; 
        }
    }
    if (flag == 1) {
        fprintf(fp, "%s %d %d %d %d\n", "./randmst", flag, numpoints, trials, dimension);
    }
    do {
        if (result == 1)
            result = 2; 
        total = 0.0; 
        clock_t start; 
        clock_t diff; 
        int duration = 0; 
        if (flag == 1)
            free_num = result; 
        array = malloc(free_num * sizeof(*array));
        if (flag == 1) {
            fprintf(fp, "%d %s\n", free_num, "dimension");
        }
        for (i = 0; i < free_num; i++)
        {
            array[i] = malloc(numpoints * sizeof(**array));
        }
        for (i = 0; i < trials; i++) {
            start = clock(); 
            if (flag == 1) {
                array = generate_matrix(result, numpoints, array); 
                total += primHeap(array, numpoints, result);
            }
            else {
                array = generate_matrix(dim_num, numpoints, array); 
                total += primHeap(array, numpoints, dimension);
            }
            diff = clock() - start; 
            duration = diff/ CLOCKS_PER_SEC; 
            if (flag == 1) {
                fprintf(fp, "%s %s %s %s %d %s %d\n",
                "Time", "taken", "for", "trial", i+1, ":", duration);
            }
        }
        if (flag == 1) {
            fprintf(fp, "%s %s %d %s %s %f\n", "Result", "for", trials, "trials", ":", total/(float)trials); 
        }
        else {
            fprintf(fp, "%f %d %d %d\n", total/(float)trials, numpoints, trials, dimension);
        }
        for (i = 0; i < free_num; i++)
        {
            free(array[i]); 
        }
        free(array); 
        result++; 
    } while (result > 0 && result < 5); 
    return 0;
}
