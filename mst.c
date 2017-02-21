#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

int deleteMin(int heap[], int v) {
  int i; 
  int minIndex = 0;
  int minValue = INT_MAX; 
  for (i = 0; i < v; i++) {
    if (heap[i] < minValue && heap[i] != -1) {
      minIndex = i; 
      minValue = heap[i]; 
    }
  }
  heap[minIndex] = -1; 
  return minIndex; 
}

void insertHeap(int vertex, int distance, int heap[], int v) {
  heap[vertex] = distance; 
}

int isEmpty(int heap[], int v) {
  int i; 
  for (i = 0; i < v; i++) {
    if (heap[i] != -1) {
      return 1; 
    }
  }
  return 0; 
}

void initializeHeap(int heap[], int v, int start) {
  int i; 
  for (i = 0; i < v; i++) {
    heap[i] = -1;
  }
  heap[start] = 0; 
}

int notInTree(int *s, int i) {
  if (s[i] == 1) {
    return 0;
  }
  else {
    return 1;
  }
}

void checkPrim(int* p, int **g, int v) {
  int i; 
  for (i = 0; i < v; i++) {
    if (p[i] != -1) {
      printf("Vertex: %d to vertex %d with weight %d\n", i, p[i], g[p[i]][i]); 
    }
  }
}

void prim(int **graph, int v) {
  int dist[v]; 
  int prev[v];
  int heap[v]; 
  int heap_v; 
  int weight;
  int s[v]; 
  int i; 
  for (i = 0; i < v; i++) {
    dist[i] = INT_MAX; 
    prev[i] = -1; 
  }
  dist[0] = 0;
  initializeHeap(heap, v, 0);
  // for (i = 0; i < v; i++) {
  //   printf("%d\n", heap[i]);
  // }
  while(isEmpty(heap, v) == 1) { 
  // int x;
  // int l;
  //for (x = 0; x < 4; x++) {
    // printf("heap start\n");
    // for (l = 0; l < v; l++) {
    //   printf("%d\n", heap[l]);
    // }
   // printf("heap done\n");
    heap_v = deleteMin(heap, v); 
   // printf("min vertex: %d\n", heap_v);
    s[heap_v] = 1;
    for (i = 0; i < v; i++) {
      weight = graph[heap_v][i];
      if (weight && notInTree(s, i)) {
        if (dist[i] > weight) {
          dist[i] = weight;
          prev[i] = heap_v; 
          //printf("YO\n");
          insertHeap(i, dist[i], heap, v);  
        }
      } 
    }
  }
  checkPrim(prev, graph, v); 
}

int main() {
  int i;
  int j; 
  int **x; 
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
