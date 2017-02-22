#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <float.h> 

struct heapNode {
  int vertex; 
  float value; 
};

struct minHeap {
  int size; 
  int capacity;
  struct heapNode **array; 
};

struct heapNode* createMinNode (int vertex, float value) { 
  struct heapNode* node = malloc(sizeof(struct heapNode)); 
  node->vertex = vertex; 
  node->value = value; 
  return node; 
}

struct minHeap* createMinHeap(int capacity) {
  struct minHeap* heap = malloc(sizeof(struct minHeap)); 
  heap->size = 0;
  heap->capacity = capacity; 
  heap->array = (struct heapNode**) malloc(sizeof(struct heapNode*) * capacity); 
  return heap; 
}

void initializeHeap(struct minHeap* h) {
  int i; 
  for (i = 0; i < h->capacity; i++) {
    h->array[i] = createMinNode(i, FLT_MAX); 
  }
  h->array[0]->value = 0;
  h->size = 1; 
}
  
void swap(int a, int b, struct minHeap* h) {
  struct heapNode* temp = h->array[a]; 
  h->array[a] = h->array[b]; 
  h->array[b] = temp;
}

void minHeapify(struct minHeap* minHeap, int root) {
  int left = root * 2 + 1; 
  int right = root * 2 + 2; 
  int smallest = root; 
  if (minHeap->size > left && 
    minHeap->array[left]->value < minHeap->array[root]->value) {
    smallest = left;  
  }
  if (minHeap->size >= right && 
    minHeap->array[right]->value < minHeap->array[smallest]->value) {
    smallest = right; 
  }
  if (smallest != root) {
     swap(root, smallest, minHeap); 
     minHeapify(minHeap, smallest); 
  }
}

struct heapNode* deleteMin(struct minHeap* h) {
  struct heapNode* min = h->array[0]; 
  int last = h->size - 1; 
  h->array[0] = h->array[last]; 
  h->size--; 
  minHeapify(h, 0); 
  return min; 
}

void insertHeap(struct minHeap* h, struct heapNode* v) {
  int location; 
  h->size++; 
  location = h->size - 1; 
  h->array[h->size - 1] = v; 
  int parent = location/2; 
  while (h->array[0] != v && h->array[parent]->value > v->value) {
    swap(parent, location, h); 
    location = parent; 
    parent = location/2; 
  }
}

int isEmpty(struct minHeap* h) {
  return (h->size == 0); 
}

int notInTree(int *s, int i) {
  if (s[i] == 1) {
    return 0;
  }
  else {
    return 1;
  }
}

void checkPrim(struct heapNode** p, float **g, int v) {
  int i; 
  for (i = 0; i < v; i++) {
    if (p[i]) {
      printf("Vertex: %d to vertex %d with weight %f\n", i, (p[i]->vertex), g[p[i]->vertex][i]); 
    }
  }
}

void printHeap(struct minHeap* h) {
  int i; 
  int s = h->size; 
  int p; 
  for (i = 0; i < s; i++) {
    if (h->array[i]->value == FLT_MAX) {
      p = 100;
    }
    else {
      p = h->array[i]->value; 
    }
    printf("%d\n", p); 
  }
}

void testHeap(struct minHeap* heap) {
  printf("original heap:\n"); 
  printHeap(heap); 
  struct heapNode* min = deleteMin(heap); 
  printf("min extracted: %f\n", min->value); 
  printHeap(heap); 
  struct heapNode* insert = malloc(sizeof(struct heapNode)); 
  insert->vertex = heap->size-1; 
  insert->value = 1; 
  insertHeap(heap, insert); 
  printf("after insertion:\n");
  printHeap(heap); 
}

void prim(float **graph, int v) {
  float dist[v]; 
  struct heapNode** prev = (struct heapNode**) malloc(sizeof(struct heapNode) * v); 
  struct heapNode* heap_v; 
  float weight;
  int s[v]; 
  int i; 
  for (i = 0; i < v; i++) {
    dist[i] = FLT_MAX; 
    prev[i] = NULL; 
  }
  dist[0] = 0.0;
  struct minHeap* heap = createMinHeap(v); 
  initializeHeap(heap);

  while(!isEmpty(heap)) { 
    heap_v = deleteMin(heap); 
    s[heap_v->vertex] = 1;
    for (i = 0; i < v; i++) {
      weight = graph[heap_v->vertex][i];
      if (weight && notInTree(s, i)) {
        if (dist[i] > weight) {
          dist[i] = weight;
          prev[i] = heap_v; 
          struct heapNode* newnode = createMinNode(i, dist[i]);
          insertHeap(heap, newnode);  
        }
      } 
    }
  }
  checkPrim(prev, graph, v); 
}

int main() {
  int i;
  int j; 
  float **x; 
  int d = 5;
  x = malloc(d * sizeof(*x)); 
  for (i = 0; i < d; i++) {
    x[i] = malloc(d * sizeof(**x)); 
  }
  x[0][0] = 0; 
  x[0][1] = 8; 
  x[0][2] = 2; 
  x[0][3] = 6;
  x[0][4] = 7; 
  x[1][0] = 8; 
  x[1][1] = 0; 
  x[1][2] = 4;
  x[1][3] = 1;
  x[1][4] = 8; 
  x[2][0] = 2; 
  x[2][1] = 4; 
  x[2][2] = 0;
  x[2][3] = 5;
  x[2][4] = 9;
  x[3][0] = 6; 
  x[3][1] = 1; 
  x[3][2] = 5; 
  x[3][3] = 0;
  x[3][4] = 10; 
  x[4][0] = 7;
  x[4][1] = 8;
  x[4][2] = 9; 
  x[4][3] = 10;  
  // for (i = 0; i < d; i++) {
  //   for (j = 0; j < d; j++) {
  //     x[i][j] = 2;
  //   }
  // }
  // for (i = 0; i < d; i++) {
  //   printf("[");
  //   for (j = 0; j < d; j++) {
  //     printf("%d,", x[i][j]); 
  //   }
  //   printf("]\n");
  // }
  prim(x, d); 
}
