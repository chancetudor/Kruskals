#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "graph.h"
#include "da.h"

static void insertAdj(Graph *g, int s, int d, int weight);
static void insertNode(DArray *adj, int s, int d, int weight);
static Node *newNode(int vertex, int weight);

static Node *newNode(int vertex, int weight) {
  Node *n = (Node *)malloc(sizeof(Node));
  if (n == 0) {
    fprintf(stderr, "Error: out of memory\n");
    exit(1);
  }
  n->vertex = vertex;
  n->weight = weight;
  n->next = NULL;
  return n;
}

Graph *newGraph(void) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  if (g == 0) {
    fprintf(stderr, "Error: out of memory\n");
    exit(1);
  }
  g->size = 0;
  g->adj = newDArray(NULL);
  return g;
}

void readFile(Graph *g, FILE *fp) {
  int weight;
  int x = readInt(fp);
  int y = readInt(fp);
  char *w = readToken(fp);
  while (!feof(fp)) {
    if (strcmp(w, ";") == 0) {
      weight = 1;
    }
    else {
      weight = atoi(w);
      w = readToken(fp);
    }
    insertAdj(g, x, y, weight);
    insertAdj(g, y, x, weight);

    x = readInt(fp);
    y = readInt(fp);
    w = readToken(fp);
  }
}

static void insertAdj(Graph *g, int s, int d, int weight) {
  //Don't include self loops
  if (s == d) return;
  int i;
  //if the source vertex is greater than the size of the adjacency list, insert null in the spaces from adj[size] to adj[s-1]
  for (i = sizeDArray(g->adj); i < s; i++) {
    setDArray(g->adj, i, NULL);
  }
  insertNode(g->adj, s, d, weight);
  g->size = sizeDArray(g->adj);
}

//Inserts edge into the adjacency list, maintains smallest to largest ordering
static void insertNode(DArray *adj, int s, int d, int weight) {
  Node *n = newNode(d, weight);
  Node *head = (s == sizeDArray(adj) ? NULL : getDArray(adj, s));
  if (head == NULL || d < head->vertex) {
    n->next = head;
    setDArray(adj, s, n);
  }
  else {
    Node *temp = head;
    //Traverse the adjacency list until the next item in the list is greater than d
    while (temp->next != NULL && temp->next->vertex <= d) {
      temp = temp->next;
    }
    //If the edge (s,d) already exists then its weight is replaced if it is less than the current weight
    if (temp->vertex == d) {
      if (temp->weight > weight) temp->weight = weight;
    }
    //Otherwise insert the edge in the adjacency list
    else {
      n->next = temp->next;
      temp->next = n;
    }
  }
}
