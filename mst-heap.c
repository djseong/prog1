#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <float.h> 
#include <math.h> 

// Data structure for a node in heap
struct heapNode {
  int vertex; 
  float value; 
};

// Data structure for min heap
struct minHeap {
  int size; 
  int capacity;
  struct heapNode **array; 
};

// Debugging function to print heap
void printHeap(struct minHeap* h) {
  int i; 
  int s = h->size; 
  float p; 
  for (i = 0; i < s; i++) {
    if (h->array[i]->value == FLT_MAX) {
      p = 100.0;
    }
    else {
      p = h->array[i]->value; 
    }
    printf("vertex %d value %f\n", h->array[i]->vertex, p); 
  }
  printf("size: %d\n", h->size); 
}

// Create min heap node
struct heapNode* createMinNode (int v, float val) {
  struct heapNode* node = malloc(sizeof(struct heapNode)); 
  node->vertex = v; 
  node->value = val; 
  return node; 
}

// Create min heap
struct minHeap* createMinHeap(int capacity) {
  struct minHeap* heap = malloc(sizeof(struct minHeap)); 
  heap->size = 0;
  heap->capacity = capacity; 
  heap->array = (struct heapNode**) malloc(sizeof(struct heapNode*) * capacity); 
  return heap; 
}

// Put first vertex into heap
void initializeMinHeap(struct minHeap* h, int* index) {
  h->array[0] = createMinNode(0, 0); 
  index[0] = 0; 
  h->size = 1; 
}
  
// Swap two nodes in heap
void swap(int a, int b, struct minHeap* h, int* index) {
  int tempIndex = index[h->array[a]->vertex]; 
  index[h->array[a]->vertex] = index[h->array[b]->vertex];
  index[h->array[b]->vertex] = tempIndex; 
  struct heapNode* temp = h->array[a]; 
  h->array[a] = h->array[b]; 
  h->array[b] = temp;
}

void minHeapify(struct minHeap* minHeap, int* index, int root) {
  int left = root * 2 + 1; 
  int right = root * 2 + 2; 
  int smallest = root; 
  if (minHeap->size > left && 
    minHeap->array[left]->value < minHeap->array[root]->value) {
    smallest = left;  
  }
  if (minHeap->size > right && 
    minHeap->array[right]->value < minHeap->array[smallest]->value) {
    smallest = right; 
  }
  if (smallest != root) {
     swap(root, smallest, minHeap, index); 
     minHeapify(minHeap, index, smallest); 
  }
}

struct heapNode* heapDeleteMin(struct minHeap* h, int* index) {
  if (isHeapEmpty(h)) {
    return NULL; 
  }
  struct heapNode* min = h->array[0]; 
  index[min->vertex] = -1; 
  struct heapNode* last = h->array[h->size - 1]; 
  if (h->size != 1)
    index[last->vertex] = 0; 
  h->array[0] = last;
  h->size--; 
  minHeapify(h, index, 0); 
  return min; 
}

void heapInsert(struct minHeap* h, float dist, int* index, int search) {
  int i; 
  int location; 
  int check = 0; 
  struct heapNode* track; 

  // If node exists in tree, update it
  int heapIndex = index[search]; 
  if (heapIndex != -1) {
    location = heapIndex; 
    h->array[heapIndex]->value = dist; 
    track = h->array[heapIndex]; 
    check = 1; 
  }

  // Else malloc new node
  if (check == 0) {
    struct heapNode* newnode = createMinNode(search, dist);
    h->size++; 
    location = h->size - 1;
    h->array[location] = newnode; 
    index[newnode->vertex] = location; 
    track = newnode; 
  }
  
  int parent = location/2; 
  while (h->array[0] != track && h->array[parent]->value > track->value) {
    swap(parent, location, h, index); 
    location = parent; 
    parent = location/2; 
  }
}

int isHeapEmpty(struct minHeap* h) {
  return (h->size == 0); 
}

// Check if node is in mst
int heapNotInTree(int *s, int i) {
  if (s[i] == 1) {
    return 0;
  }
  else {
    return 1;
  }
}

// Calculate distance up to 4th dimension
float distance(float x1, float y1, float z1, float d1,
 float x2, float y2, float z2, float d2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + 
    pow(z1 - z2, 2) + pow(d1 - d2, 2)); 
}

// Debugging function to print index array
void printIndex(int *index, int v) { 
  int i; 
  for (i = 0; i < v; i++) {
    printf("vertex: %d at heap index: %d\n", i, index[i]);
  }
}

// Prim's algorithim
float primHeap(float **graph, int v, int d) {
  float dist[v]; 
  int* index = malloc(sizeof(int) * v); 
  struct heapNode* heap_v; 
  float weight;
  float sum = 0.0; 
  int s[v]; 
  int x; 
  int id = 0; 
  for (x = 0; x < v; x++) {
    dist[x] = FLT_MAX; 
    index[x] = -1; 
    s[x] = 0;
  }
  dist[0] = 0.0;
  struct minHeap* heap = createMinHeap(v); 
  initializeMinHeap(heap,index);
  while(!isHeapEmpty(heap)) { 
    heap_v = heapDeleteMin(heap, index);
    id++; 
    sum += heap_v->value; 
    s[heap_v->vertex] = 1;
    for (x = 0; x < v; x++) {
      // Find weight in appropriate dimension
      if (d == 0) {
        weight = (float) rand() / ((float) RAND_MAX);
      }
      if (d == 2) {
        weight = distance(graph[0][heap_v->vertex], 
        graph[1][heap_v->vertex], 0.0, 0.0, 
        graph[0][x], graph[1][x], 0.0, 0.0);
      }
      else if (d == 3) {
        weight = distance(graph[0][heap_v->vertex], 
        graph[1][heap_v->vertex], graph[2][heap_v->vertex], 0.0, 
        graph[0][x], graph[1][x], graph[2][x], 0.0);
      }
      else if (d == 4) {
        weight = distance(graph[0][heap_v->vertex], 
        graph[1][heap_v->vertex], graph[2][heap_v->vertex], graph[3][heap_v->vertex], 
        graph[0][x], graph[1][x], graph[2][x], graph[3][x]);
      }
      if (weight != 0 && heapNotInTree(s, x) == 1) {
        if (dist[x] > weight) {
          dist[x] = weight;
          heapInsert(heap, dist[x], index, x);
        }
      }   
    }
    free(heap_v); 
  }
  free(index);
  free(heap->array); 
  free(heap); 
  return sum; 
}

// int main() {
//   int i;
//   int j; 
//   float **x; 
//   int d = 4;
//   x = malloc(d * sizeof(*x)); 
//   for (i = 0; i < 2; i++) {
//     x[i] = malloc(d * sizeof(**x)); 
//   }
//   x[0][0] = 0.809272; 
//   x[0][1] = 0.668060; 
//   x[0][2] = 0.825339; 
//   x[0][3] = 0.464037;
//   x[1][0] = 0.852053; 
//   x[1][1] = 0.071834; 
//   x[1][2] = 0.403007;
//   x[1][3] = 0.019544;

//   // x = malloc(d * sizeof(*x)); 
//   // for (i = 0; i < d; i++) {
//   //   x[i] = malloc(d * sizeof(**x)); 
//   // }
  
//   // x[0][0] = 0.; 
//   // x[0][1] = 0.79; 
//   // x[0][2] = 0.45; 
//   // x[0][3] = 0.9;
//   // x[1][0] = 0.79; 
//   // x[1][1] = 0.0; 
//   // x[1][2] = 0.36;
//   // x[1][3] = 0.52;
//   // x[2][0] = 0.45;
//   // x[2][1] = 0.36;
//   // x[2][2] = 0; 
//   // x[2][3] = 0.52; 
//   // x[3][0] = 0.9; 
//   // x[3][1] = 0.2; 
//   // x[3][2] = 0.52; 
//   // x[3][3] = 0; 

//   // for (i = 0; i < d; i++) {
//   //   for (j = 0; j < d; j++) {
//   //     x[i][j] = 2;
//   //   }
//   // }
//   // for (i = 0; i < d; i++) {
//   //   printf("[");
//   //   for (j = 0; j < d; j++) {
//   //     printf("%d,", x[i][j]); 
//   //   }
//   //   printf("]\n");
//   // }
//   printf("%f\n", primHeap(x, d)); 
// }
