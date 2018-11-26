//
// Created by Chance Tudor on 11/25/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "da.h"
#include "queue.h"
#include "rbt.h"
#include "set.h"
#include "string.h"
#include "integer.h"
#include "scanner.h"


typedef enum {
    false = 0, true = 1
}bool;

typedef struct vertWrapper {
    int index;
    int value;
}vertWrapper;

typedef struct EDGE {
    INTEGER *weight;
    int src;
    int dest;
}EDGE;

typedef struct VERTEX {
    int value;
    bool visited;
    DA *EDGEList;
}VERTEX;

EDGE * newEDGE(int ev) {
    EDGE* newEDGE = (EDGE*)malloc(sizeof(EDGE));
    assert(newEDGE != NULL);
    newEDGE->weight = newINTEGER(ev);

    return newEDGE;
}

void displayEDGE (void *x, FILE* fp) {
    EDGE *y = x;
    fprintf(fp, "%d", y->dest);
    fprintf(fp, "(%d)", y->src);
    displayINTEGER(y->weight, fp);
}

VERTEX* newVERTEX(int x) {
    VERTEX* newVERTEX = (VERTEX*)malloc(sizeof(VERTEX));
    assert(newVERTEX != 0);
    newVERTEX->value = x;
    newVERTEX->visited = false;
    newVERTEX->EDGEList = newDA();
    setDAdisplay(newVERTEX->EDGEList, displayEDGE);

    return newVERTEX;
}

void displayVERTEX(void* x, FILE *fp) {
    VERTEX* y = x;
    fprintf(fp, "%d", y->value);
}


VERTEX *findVERTEX(VERTEX **VERTEXArray, int value, int numVertices);

EDGE **sortEDGEs(QUEUE *breadthFirst);

int compareEDGE(void *, void*);
int compareEDGE2(void *, void*);
int  comparevertWrapper(void *, void*);
int findVERTEXIndex2(RBT *t, int v);
int findVERTEXIndex(VERTEX **VERTEXArray, int value, int numVertices);

void displayGRAPH(FILE *fp, int numSets, VERTEX **VERTEXArray, int numVertices);
void TopDownMergeSort(int A[], int B[], int n);
void TopDownSplitMerge(int B[], int iBegin, int iEnd, int A[]);
void TopDownMerge(int A[], int iBegin, int iMiddle, int iEnd, int B[]);
void CopyArray(int A[], int iBegin, int iEnd, int B[]);
void addEDGE(VERTEX*, EDGE*);
void TopDownMergeSortEDGE(EDGE* A[], EDGE* B[], int n);
void TopDownSplitMergeEDGE(EDGE* B[], int iBegin, int iEnd, EDGE* A[]);
void TopDownMergeEDGE(EDGE* A[], int iBegin, int iMiddle, int iEnd, EDGE* B[]);
void CopyArrayEDGE(EDGE* A[], int iBegin, int iEnd, EDGE* B[]);
void TopDownMergeSortEDGENew(void* A[], void* B[], int n);
void TopDownSplitMergeEDGENew(void* B[], int iBegin, int iEnd, void* A[]);
void TopDownMergeEDGENew(void* A[], int iBegin, int iMiddle, int iEnd, void* B[]);
void CopyArrayEDGENew(void* A[], int iBegin, int iEnd, void* B[]);
void TopDownMergeSortEDGE2(EDGE* A[], EDGE* B[], int n);
void TopDownSplitMergeEDGE2(EDGE* B[], int iBegin, int iEnd, EDGE* A[]);
void TopDownMergeEDGE2(EDGE* A[], int iBegin, int iMiddle, int iEnd, EDGE* B[]);
void CopyArrayEDGE2(EDGE* A[], int iBegin, int iEnd, EDGE* B[]);
void TopDownMergeSortNew(void* A[], void* B[], int n);
void TopDownSplitMergeNew(void* B[], int iBegin, int iEnd, void* A[]);
void TopDownMergeNew(void* A[], int iBegin, int iMiddle, int iEnd, void* B[]);
void CopyArrayNew(void* A[], int iBegin, int iEnd, void* B[]);
void displayVertWrapper(void *, FILE *);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char*argv[]) {
    for(int a = 1; a < argc; a++) {
        if(strcmp("-v", argv[a]) == 0) {
            printf("Chance Tudor\n");
            exit(0);
        }
    }

    FILE* inputFile;
    if (argc != 2) {
        printf("Usage: ./kruskal (input file)\n");
        exit(0);
    }

    bool noInput = true;
    inputFile = fopen(argv[1], "r");
    if(fopen(argv[1], "r")) {
        noInput = false;
    }
    if(noInput == true) {
        exit(0);
    }

    int v1 = 0;
    int v2 = 0;
    int weight = 1;
    DA *EDGEs = newDA();
    setDAdisplay(EDGEs, displayEDGE);
    DA *vertices = newDA();
    setDAdisplay(vertices, displayINTEGER);

    while(noInput == false) {
        char *firstCommand = readToken(inputFile);
        if(!feof(inputFile)) {
            if(strcmp(";", firstCommand) != 0) {
                v1 = 0;
                v2 = 0;
                weight = 1;

                v1 = atoi(firstCommand);

                char *secondCommand = readToken(inputFile); v2 = atoi(secondCommand);
                char *thirdCommand = readToken(inputFile);

                if(isdigit(atoi(thirdCommand))) {
                    char *fourthCommand = readToken(inputFile);
                    if(fourthCommand) fourthCommand = '\0';
                }

                if(strcmp(thirdCommand, ";") != 0) {
                    weight = atoi(thirdCommand);
                }

                EDGE *newEDGE = (EDGE*)malloc(sizeof(EDGE*));
                assert(newEDGE != 0);
                newEDGE->weight = newINTEGER(weight);
                newEDGE->src = v1;
                newEDGE->dest = v2;


                int tempIndex = sizeDA(EDGEs);
                for (int i = 0; i < tempIndex; i++) {
                    EDGE* tempEDGE = getDA(EDGEs, i);
                    if (tempEDGE->src == newEDGE->src && tempEDGE->dest == newEDGE->dest)	//if already exists{
                        tempEDGE->weight = newEDGE->weight; //update to newest weight
                    }
                }

                insertDA(EDGEs, tempIndex, newEDGE);

                tempIndex = sizeDA(vertices);
                INTEGER *iV1 = newINTEGER(v1);
                insertDA(vertices, tempIndex, iV1);
                tempIndex = sizeDA(vertices);
                INTEGER *iV2 = newINTEGER(v2);
                insertDA(vertices, tempIndex, iV2);
            }

        }
        else {
            break;
        }

    }

    int i = 0;

    int numVertices2 = sizeDA(vertices);
    void **VERTEXArray = malloc(sizeof(void *) * numVertices2);
    for(i = 0; i < sizeDA(vertices); i++) {
        VERTEXArray[i] = getDA(vertices, i);
    }

    void *VERTEXBuffer[numVertices2];

    int numEDGEs2 = sizeDA(EDGEs);
    void **EDGEArray = malloc(sizeof(void *) * numEDGEs2);
    for(i = 0; i < sizeDA(EDGEs); i++) {
        EDGEArray[i] = getDA(EDGEs, i);
    }

    void *EDGEBuffer[numEDGEs2];

    TopDownMergeSortNew(VERTEXArray, VERTEXBuffer, numVertices2);
    TopDownMergeSortEDGENew(EDGEArray, EDGEBuffer, numEDGEs2);

    SET* graph2 = newSET();
    setSETdisplay(graph2, displayEDGE);
    DA* sets2 = newDA();
    setDAdisplay(sets2, displayINTEGER);

    RBT *VERTEXTree = newRBT(comparevertWrapper);
    setRBTdisplay(VERTEXTree, displayVertWrapper);
    VERTEX **VERTEXList2 = (VERTEX**)malloc(sizeof(VERTEX*) * numVertices2);

    int j = 0;
    int numSets = 0;

    for(i = 0; i < numVertices2; i++) {
        if(i == 0) {

            int index = makeSET(graph2, VERTEXArray[i]);
            numSets++;
            int tempIndex2 = sizeDA(sets2);
            insertDA(sets2, tempIndex2, newINTEGER(index));
            VERTEXArray[j] = VERTEXArray[i];


            vertWrapper *newValue = malloc(sizeof(vertWrapper));
            newValue->value = getINTEGER(VERTEXArray[i]);
            newValue->index = index;

            insertRBT(VERTEXTree, newValue);
            VERTEXList2[j] = newVERTEX(getINTEGER(VERTEXArray[j]));

            j++;
        }
        else if ((i > 0) && (getINTEGER(VERTEXArray[i]) != getINTEGER(VERTEXArray[i-1]))) {
            int index = makeSET(graph2, VERTEXArray[i]);
            numSets++;
            int tempIndex3 = sizeDA(sets2);
            insertDA(sets2, tempIndex3, newINTEGER(index));
            VERTEXArray[j] = VERTEXArray[i];

            vertWrapper *newValue = malloc(sizeof(vertWrapper));
            newValue->value = getINTEGER(VERTEXArray[i]);
            newValue->index = index;

            insertRBT(VERTEXTree, newValue);
            VERTEXList2[j] = newVERTEX(getINTEGER(VERTEXArray[j]));

            j++;
        }
    }

    VERTEXArray = realloc(VERTEXArray, j * sizeof(void*));
    assert(VERTEXArray != 0);
    VERTEXList2 = realloc(VERTEXList2, j * sizeof(VERTEX*));
    assert(VERTEXList2 != 0);
    int numVertices3 = sizeDA(sets2);


    for(i = 0; i < numEDGEs2; i++) {
        EDGE *currEDGE = EDGEArray[i];
        int u = findVERTEXIndex2(VERTEXTree, currEDGE->src);
        int v = findVERTEXIndex2(VERTEXTree, currEDGE->dest);

        if(findSET(graph2, u) != findSET(graph2, v)) {
            unionSET(graph2, u, v);
            numSets--;
            VERTEX* src = VERTEXList2[u];
            VERTEX* dst = VERTEXList2[v];

            addEDGE(src, currEDGE);
            addEDGE(dst, currEDGE);
        }
    }

    displayGRAPH(stdout, numSets, VERTEXList2, numVertices3);

    if(inputFile) { fclose(inputFile); }
    return 0;
}


void displayGRAPH(FILE *fp, int numSets, VERTEX **VERTEXArray, int numVertices) {

    int i = 0;
    for(i = 0; i < numVertices; i++) {
        VERTEXArray[i]->visited = false;
    }


    for(i = 0; i < numSets; i++) {
        int totalWeight = 0;

        int level = 0;
        QUEUE *breadthFirst = newQUEUE();
        setQUEUEdisplay(breadthFirst, displayEDGE);
        QUEUE *vert  		= newQUEUE();
        setQUEUEdisplay(vert, displayVERTEX);

        int firstIndex = 0;
        while(VERTEXArray[firstIndex]->visited)
            firstIndex++;

        int nonVisitedCount = 0;
        for(int k = 0; k < numVertices; k++) {
            if(!VERTEXArray[k]->visited)
                nonVisitedCount++;
        }

        if(firstIndex > numVertices) break;
        if(numVertices >= 1) {
            fprintf(fp, "%d: ", level);
            displayVERTEX(VERTEXArray[firstIndex], fp);
            VERTEXArray[firstIndex]->visited = true;
            printf("\n");

            level++;

        }
        if(numVertices > 1) {
            VERTEX *first = VERTEXArray[firstIndex];

            for(int j = 0; j < sizeDA(first->EDGEList); j++) {
                EDGE *currEDGE = getDA(first->EDGEList, j);

                if(currEDGE->src != first->value) {
                    int temp = currEDGE->src;
                    currEDGE->src = currEDGE->dest;
                    currEDGE->dest = temp;
                }

                enqueue(breadthFirst, currEDGE);
                int index = findVERTEXIndex(VERTEXArray, currEDGE->dest, numVertices);
                VERTEX* currVERTEX = VERTEXArray[index];
                VERTEXArray[index]->visited = true;

                enqueue(vert, currVERTEX);
            }
        }

        while(sizeQUEUE(breadthFirst) != 0) {
            int size = sizeQUEUE(breadthFirst);
            fprintf(fp, "%d: ", level);

            EDGE **sortedList = sortEDGEs(breadthFirst);

            int j =0;
            for(j = 0; j < size; j++) {
                EDGE *curr = sortedList[j];
                VERTEX *currVERTEX = findVERTEX(VERTEXArray, curr->dest, numVertices);

                displayEDGE(curr, fp);

                VERTEX *previousVERTEX = findVERTEX(VERTEXArray, curr->src, numVertices);
                int k = 0;
                for(k = 0; k < sizeDA(currVERTEX->EDGEList); k++) {
                    EDGE *currEDGE = getDA(currVERTEX->EDGEList, k);

                    if(currEDGE->src != currVERTEX->value) {
                        int temp = currEDGE->src;
                        currEDGE->src = currEDGE->dest;
                        currEDGE->dest = temp;
                    }

                    if(currEDGE->dest != previousVERTEX->value) {
                        enqueue(breadthFirst, currEDGE);
                        int index = findVERTEXIndex(VERTEXArray, currEDGE->dest, numVertices);
                        VERTEX* currVERTEX = VERTEXArray[index];
                        VERTEXArray[index]->visited = true;
                        enqueue(vert, currVERTEX);
                    }

                }

                totalWeight += getINTEGER(curr->weight);
                if(j < (size-1)) fprintf(fp, " ");
                else fprintf(fp, "\n");
            }
            level++;
        }
        fprintf(fp, "weight: %d\n", totalWeight);
    }

}

int compareEDGE(void *first, void* second) {
    EDGE *x = first;
    EDGE *y = second;

    if(getINTEGER(x->weight) != getINTEGER(y->weight)) { return compareINTEGER(x->weight, y->weight); }

    else {
        int es1 = x->src;
        int ed1 = x->dest;
        int es2 = y->src;
        int ed2 = y->dest;


        int minv1 = 0;
        int minv2 = 0;
        if(es1 < ed1) minv1 = es1;
        else minv1 = ed1;

        if(es2 < ed2) minv2 = es2;
        else minv2 = ed2;


        if(minv1 == minv2) {
            int temp1 = 0;
            int temp2 = 0;
            if(es1 == minv1) temp1 = ed1;
            else temp1 = es1;

            if(es2 == minv2) temp2 = ed2;
            else temp2 = es2;

            return(compareINTEGER(newINTEGER(temp1), newINTEGER(temp2)));
        }
        else {
            return (compareINTEGER(newINTEGER(minv1), newINTEGER(minv2)));
        }
    }
}

int compareVERTEX(void *first, void* second) {
    INTEGER *x = first;
    INTEGER *y = second;

    return compareINTEGER(x, y);
}


void TopDownMergeSortEDGE(EDGE* A[], EDGE* B[], int n) {
    CopyArrayEDGE(A, 0, n ,B);
    TopDownSplitMergeEDGE(B, 0, n, A);
}

void TopDownSplitMergeEDGE(EDGE* B[], int iBegin, int iEnd, EDGE* A[]) {
    if(iEnd - iBegin < 2)
        return;
    int iMiddle = (iEnd + iBegin) / 2;

    TopDownSplitMergeEDGE(A, iBegin, iMiddle, B);
    TopDownSplitMergeEDGE(A, iMiddle, iEnd, B);

    TopDownMergeEDGE(B, iBegin, iMiddle, iEnd, A);

}

void TopDownMergeEDGE(EDGE* A[], int iBegin, int iMiddle, int iEnd, EDGE* B[]) {
    int i = iBegin, j = iMiddle, k = 0;

    for(k = iBegin; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd || (compareEDGE(A[i], A[j]) <= 0))) {
            B[k] = A[i];
            i++;
        }
        else {

            B[k] = A[j];
            j++;
        }
    }
}

void CopyArrayEDGE(EDGE* A[], int iBegin, int iEnd, EDGE* B[]) {
    int k = 0;
    for(k = iBegin; k < iEnd; k++) {
        B[k] = A[k];
    }
}


void TopDownMergeSort(int A[], int B[], int n) {

    CopyArray(A, 0, n ,B);
    TopDownSplitMerge(B, 0, n, A);
}

void TopDownSplitMerge(int B[], int iBegin, int iEnd, int A[]) {
    if(iEnd - iBegin < 2)
        return;
    int iMiddle = (iEnd + iBegin) / 2;

    TopDownSplitMerge(A, iBegin, iMiddle, B);
    TopDownSplitMerge(A, iMiddle, iEnd, B);

    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

void TopDownMerge(int A[], int iBegin, int iMiddle, int iEnd, int B[]) {
    int i = iBegin, j = iMiddle, k = 0;

    for(k = iBegin; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i++;
        }
        else {
            B[k] = A[j];
            j++;
        }
    }
}

void CopyArray(int A[], int iBegin, int iEnd, int B[]) {
    int k = 0;
    for(k = iBegin; k < iEnd; k++) {
        B[k] = A[k];
    }
}

VERTEX * findVERTEX(VERTEX **VERTEXArray, int value, int numVertices) {
    int i = 0;

    for(i = 0; i < numVertices; i++) {
        VERTEX* curr = VERTEXArray[i];
        if(curr->value == value)
            return curr;
    }
    return NULL;
}

int findVERTEXIndex(VERTEX **VERTEXArray, int value, int numVertices) {
    int i = 0;
    for(i = 0; i < numVertices; i++) {
        VERTEX* curr = VERTEXArray[i];
        if(curr->value == value)
            return i;
    }
    return 0;
}

void addEDGE(VERTEX* v, EDGE* e) {

    int tempIndex = sizeDA(v->EDGEList);
    insertDA(v->EDGEList, tempIndex, e);

}

EDGE ** sortEDGEs(QUEUE *breadthFirst) {

    EDGE **unsortedEDGEArray = malloc(sizeof(EDGE*) * sizeQUEUE(breadthFirst));
    assert(unsortedEDGEArray != 0);
    int i = 0;
    int size = sizeQUEUE(breadthFirst);

    for(i = 0; i < size; i++) {
        unsortedEDGEArray[i] = dequeue(breadthFirst);

    }

    EDGE *buffer[size];


    TopDownMergeSortEDGE2(unsortedEDGEArray, buffer, size);

    return unsortedEDGEArray;
}



void TopDownMergeSortEDGE2(EDGE* A[], EDGE* B[], int n) {

    CopyArrayEDGE2(A, 0, n ,B);
    TopDownSplitMergeEDGE2(B, 0, n, A);
}

void TopDownSplitMergeEDGE2(EDGE* B[], int iBegin, int iEnd, EDGE* A[]) {
    if(iEnd - iBegin < 2)
        return;
    int iMiddle = (iEnd + iBegin) / 2;

    TopDownSplitMergeEDGE2(A, iBegin, iMiddle, B);
    TopDownSplitMergeEDGE2(A, iMiddle, iEnd, B);

    TopDownMergeEDGE2(B, iBegin, iMiddle, iEnd, A);

}

void TopDownMergeEDGE2(EDGE* A[], int iBegin, int iMiddle, int iEnd, EDGE* B[]) {
    int i = iBegin, j = iMiddle, k = 0;

    for(k = iBegin; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd || (compareEDGE2(A[i], A[j]) <= 0))) {
            B[k] = A[i];
            i++;
        }
        else {
            B[k] = A[j];
            j++;
        }
    }
}

void CopyArrayEDGE2(EDGE* A[], int iBegin, int iEnd, EDGE* B[]) {
    int k = 0;
    for(k = iBegin; k < iEnd; k++) {
        B[k] = A[k];
    }
}

int compareEDGE2(void *first, void* second) {


    EDGE *x = first;
    EDGE *y = second;

    int ed1 = getINTEGER(x->weight);
    int ed2 = getINTEGER(y->weight);

    int ed3 = x->dest;
    int ed4 = y->dest;

    int ed5 = x->src;
    int ed6 = y->src;

    if(compareINTEGER(newINTEGER(ed1), newINTEGER(ed2)) == 0) { //if equal weight
        if(compareINTEGER(newINTEGER(ed5), newINTEGER(ed6)) == 0) { //if equal source
            return compareINTEGER(newINTEGER(ed3), newINTEGER(ed4));	//sort by VERTEX
        }
        return compareINTEGER(newINTEGER(ed5), newINTEGER(ed6)); //sort by source
    }

    return compareINTEGER(newINTEGER(ed1), newINTEGER(ed2));	//sort by weight

}


void TopDownMergeSortNew(void* A[], void* B[], int n) {
    CopyArrayNew(A, 0, n ,B);
    TopDownSplitMergeNew(B, 0, n, A);
}

void TopDownSplitMergeNew(void* B[], int iBegin, int iEnd, void* A[]) {
    if(iEnd - iBegin < 2)
        return;
    int iMiddle = (iEnd + iBegin) / 2;

    TopDownSplitMergeNew(A, iBegin, iMiddle, B);
    TopDownSplitMergeNew(A, iMiddle, iEnd, B);

    TopDownMergeNew(B, iBegin, iMiddle, iEnd, A);
}

void TopDownMergeNew(void* A[], int iBegin, int iMiddle, int iEnd, void* B[]) {
    int i = iBegin, j = iMiddle, k = 0;

    for(k = iBegin; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd ||	(compareINTEGER(A[i], A[j]) <= 0))) {
            B[k] = A[i];
            i++;
        }
        else {
            B[k] = A[j];
            j++;
        }
    }
}

void CopyArrayNew(void* A[], int iBegin, int iEnd, void* B[]) {
    int k = 0;
    for(k = iBegin; k < iEnd; k++) {
        B[k] = A[k];
    }
}


void TopDownMergeSortEDGENew(void* A[], void* B[], int n) {
    CopyArrayEDGENew(A, 0, n ,B);
    TopDownSplitMergeEDGENew(B, 0, n, A);
}

void TopDownSplitMergeEDGENew(void* B[], int iBegin, int iEnd, void* A[]) {
    if(iEnd - iBegin < 2)
        return;
    int iMiddle = (iEnd + iBegin) / 2;

    TopDownSplitMergeEDGENew(A, iBegin, iMiddle, B);
    TopDownSplitMergeEDGENew(A, iMiddle, iEnd, B);

    TopDownMergeEDGENew(B, iBegin, iMiddle, iEnd, A);

}

void TopDownMergeEDGENew(void* A[], int iBegin, int iMiddle, int iEnd, void* B[]) {
    int i = iBegin, j = iMiddle, k = 0;

    for(k = iBegin; k < iEnd; k++) {
        if(i < iMiddle && (j >= iEnd || (compareEDGE(A[i], A[j]) <= 0))) {
            B[k] = A[i];
            i++;
        }
        else {
            B[k] = A[j];
            j++;
        }
    }
}

void CopyArrayEDGENew(void* A[], int iBegin, int iEnd, void* B[]) {
    int k = 0;
    for(k = iBegin; k < iEnd; k++) {
        B[k] = A[k];
    }
}


void displayVertWrapper(void *v, FILE *fp) {
    vertWrapper *x = v;
    fprintf(fp, "%d", x->value);
}

int comparevertWrapper(void *x, void *y) {
    vertWrapper *first = x;
    vertWrapper *second = y;

    return compareINTEGER(newINTEGER(first->value), newINTEGER(second->value));
}

int findVERTEXIndex2(RBT *t, int v) {
    vertWrapper *findNode = malloc(sizeof(vertWrapper));
    assert(findNode != 0);

    findNode->value = v;
    findNode->index = -1;

    int index = -1;

    findNode = findRBT(t, findNode);

    index = findNode->index;


    return index;
}