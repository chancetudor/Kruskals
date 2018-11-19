#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "darray.h"

typedef struct Node
{
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct Graph
{
    DArray *adj;
    int size;
} Graph;

void readFile(Graph *g, FILE *fp);
Graph *newGraph();

#endif // GRAPH_H_INCLUDED
