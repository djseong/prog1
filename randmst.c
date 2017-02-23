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


// finds Euclidean distance between two points with the same dimension
float distance(vertex point_a, vertex point_b, int dimension)
{
    float sum = pow(point_a.x - point_b.x, 2);

    if (dimension >= 2)
    {
        sum += pow(point_a.y - point_b.y, 2);
    }
    if (dimension >= 3)
    {
        sum += pow(point_a.z - point_b.z, 2);
    }
    if (dimension == 4)
    {
        sum += pow(point_a.w - point_b.w, 2);
    }
    return sqrt(sum);
}


// prints array
void print_array(int size, float **arr)
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf(" %f", arr[i][j]);
        }
        printf("\n");
    }
}

// prints vertex lists
void print_vertex_list(int size, vertex vertex_list[size], int dimension)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("(%f", vertex_list[i].x);
        if (dimension >= 2)
        {
            printf(", %f", vertex_list[i].y);
        }
        if (dimension >= 3)
        {
            printf(", %f", vertex_list[i].z);
        }
        if (dimension == 4)
        {
            printf(", %f", vertex_list[i].w);
        }
        printf(")\n");
    }
    printf("\n");
}

float** generate_matrix (int size, float **array, int dimension)
{
    int i,j;
    int counter = 1;
    vertex vertex_list [size];

    // initializes array to all 0s
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++) 
        {
            array[i][j] = 0.0;
        }
    }

        // for dimension 0, the weight of each edge is a random var
    if (dimension == 0)
    {
        // assigns a random float between 0 and 1 to upper triangle of array
        for (i = 0; i < size; i++)
        {
            for (j = counter; j < size; j++) 
            {
                array[i][j] = random_float();
            }
            counter++;
        }
    }
    // for all other dimensions, the weight of each edge is the Euclidean distance between two vertices
    // first randomly choose each component of each vertex, then calculate the Euclidean distance between each pair of vertices
    else
    {
        // assigns a random float between 0 and 1 for each component of each vertex
        for (i = 0; i < size; i++)
        {
            vertex_list[i].x = random_float();

            if (dimension >= 2)
            {
                vertex_list[i].y = random_float();
            }
            if (dimension >= 3)
            {
                vertex_list[i].z = random_float();
            }
            if (dimension == 4)
            {
                vertex_list[i].w = random_float();
            }
        }
        
        //print_vertex_list(size, vertex_list, dimension);
        // printf("\n");
        
        counter = 0;
        // assigns top triangle of array to the corresponding distances between vertices
        for(i = 0; i < size - 1; i++)
        {
            for(j = counter; j < size; j++)
            {
                array[i][j] = distance(vertex_list[i], vertex_list[j], dimension); 
            }
            counter++;
        }
    }
    

    //reflects upper triangle of array to lower triangle
    counter = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < counter; j++) 
        {
            array[i][j] = array[j][i];
        }
        counter++;
    }

    return array;
}




int main( int argc, char *argv[] )
{
    srand(time(NULL));

    // sets commandline arguments to variables
    int numpoints = atoi(argv[1]);
    int dimension = atoi(argv[3]);
    int trials = atoi(argv[2]); 
    float total = 0.0; 
    
    int size = numpoints;
    float **array;
    array = malloc(size * sizeof(*array));
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = malloc(size * sizeof(**array));
    }
    
 // array = generate_matrix(size, array, dimension);    
     //print_array(size, array);
      // printf("%n"); 
    // printf("Result for mst:\n");
    // prim(array, size);

    for (i = 0; i < trials; i++) {
        array = generate_matrix(size, array, dimension); 
        //print_array(size, array); 
        //printf("done generating\n"); 
        total += primHeap(array, size);
        //prim(array, size); 
    }

    printf("Result for %d trials using mst heap: %f\n", trials, total/(float) trials); 

    return 0;
}
