#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <float.h> 
#include <math.h> 

struct heapNode {
  int vertex; 
  float value; 
};

struct minHeap {
  int size; 
  int capacity;
  struct heapNode **array; 
};

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

struct heapNode* createMinNode (int v, float val) { 
  struct heapNode* node = malloc(sizeof(struct heapNode)); 
  node->vertex = v; 
  node->value = val; 
  return node; 
}

struct minHeap* createMinHeap(int capacity) {
  struct minHeap* heap = malloc(sizeof(struct minHeap)); 
  heap->size = 0;
  heap->capacity = capacity; 
  heap->array = (struct heapNode**) malloc(sizeof(struct heapNode*) * capacity); 
  return heap; 
}

void initializeMinHeap(struct minHeap* h, int* index) {
  // int i; 
  // for (i = 0; i < h->capacity; i++) {
  //   struct heapNode* node = createMinNode(i, FLT_MAX); 
  //   h->array[i] = node; 
  //   index[i] = -1; 
  // }
  h->array[0] = createMinNode(0, 0); 
  //h->array[0]->value = 0.0;
  index[0] = 0; 
  h->size = 1; 
}
  
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

void heapInsert(struct minHeap* h, struct heapNode* v, int* index, int search) {
  int i; 
  int location; 
  int check = 0; 

  int heapIndex = index[search]; 
  if (heapIndex != -1) {
    location = heapIndex; 
    h->array[heapIndex]->value = v->value; 
    v = h->array[heapIndex];
    check = 1; 
  }

  if (check == 0) {
    h->size++; 
    location = h->size - 1;
    h->array[location] = v; 
    index[v->vertex] = location; 
  }
  
  int parent = location/2; 
  while (h->array[0] != v && h->array[parent]->value > v->value) {
    swap(parent, location, h, index); 
    location = parent; 
    parent = location/2; 
  }
}

int isHeapEmpty(struct minHeap* h) {
  return (h->size == 0); 
}

int heapNotInTree(int *s, int i) {
  if (s[i] == 1) {
    return 0;
  }
  else {
    return 1;
  }
}

void heapCheckPrim(struct heapNode** p, float **g, int v) {
  int i; 
  for (i = 0; i < v; i++) {
    if (p[i]) {
      printf("Vertex: %d to vertex %d with weight %f\n", i, (p[i]->vertex), g[p[i]->vertex][i]); 
    }
  }
}

float sumPrim(struct heapNode **p, float **g, int v) {
  int i; 
  float sum = 0.0; 
  for (i = 0; i < v; i++) {
    if (p[i]) {
       sum += g[p[i]->vertex][i];
    }
  }
  return sum; 
} 

float sqDistance(float x1, float y1, float x2, float y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); 
}



void testHeap(struct minHeap* heap) {
  printf("original heap:\n"); 
  printHeap(heap); 
  struct heapNode* min;// = heapDeleteMin(heap); 
  printf("min extracted: %f\n", min->value); 
  printHeap(heap); 
  struct heapNode* insert = malloc(sizeof(struct heapNode)); 
  insert->vertex = heap->size-1; 
  insert->value = 1; 
//heapInsert(heap, insert); 
  printf("after insertion:\n");
  printHeap(heap); 
}

void printIndex(int *index, int v) { 
  int i; 
  for (i = 0; i < v; i++) {
    printf("vertex: %d at heap index: %d\n", i, index[i]);
  }
}

float primHeap(float **graph, int v) {
  float dist[v]; 
  int* index = malloc(sizeof(int) * v); 
  struct heapNode* heap_v; 
  float weight;
  float sum = 0.0; 
  int s[v]; 
  int x; 
  for (x = 0; x < v; x++) {
    dist[x] = FLT_MAX; 
    index[x] = -1; 
    s[x] = 0;
  }
  dist[0] = 0.0;
  struct minHeap* heap = createMinHeap(v); 
  initializeMinHeap(heap,index);

  // printf("initial heap:\n"); 
  // printHeap(heap); 

  while(!isHeapEmpty(heap)) { 
    heap_v = heapDeleteMin(heap, index);
    //printf("deleted vertex: %d with value %f\n", heap_v->vertex, heap_v->value); 
    //printHeap(heap);
    // printf("index after delete:\n"); 
    // printIndex(index, v); 
    sum += heap_v->value; 
    //printf("vertex: %d\n", heap_v->vertex); 
   // printf("%d\n", heap_v->vertex); 
    s[heap_v->vertex] = 1;
    for (x = 0; x < v; x++) {
      weight = sqDistance(graph[0][heap_v->vertex], 
        graph[1][heap_v->vertex], graph[0][x], graph[1][x]);
     // weight = graph[heap_v->vertex][x];
      if (weight != 0 && heapNotInTree(s, x) == 1) {
        if (dist[x] > weight) {
          //float old = dist[x]; 
          dist[x] = weight;
          //prev[x] = heap_v; 
          struct heapNode* newnode = createMinNode(x, dist[x]);
          heapInsert(heap, newnode, index, x);
          //printf("after insertion vertex %d value %f:\n", newnode->vertex, newnode->value);
          //printHeap(heap);   
          // printf("index after insert: \n"); 
          // printIndex(index, v); 
        }
      }   
    }
    free(heap_v);  

  }
  //heapCheckPrim(prev, graph, v); 
  //return sumPrim(prev, graph, v); 
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
