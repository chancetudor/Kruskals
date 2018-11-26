#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "da.h"
#include "integer.h"

typedef enum {false = 0, true = 1} bool;

typedef void (*FM)(void * ptr); // typedef declaration to store a freeMethod function pointer in DA struct
typedef void (*DM)(void * ptr, FILE *fp);

struct set {
    FM free;
    DM display;
    DA *representatives;
    int numReps;
    int level;
};

typedef struct VERTEX VERTEX;
struct VERTEX {
    int repIndex;
    int isRep;
    int index;
    void * value;
    int rank;
};

typedef struct EDGE EDGE;
struct EDGE {
    INTEGER* weight;
};


int rank(SET *d, VERTEX *v);

VERTEX * newVERTEX(int rep, void* store) {
    VERTEX *newVERTEX = (VERTEX*)malloc(sizeof(VERTEX));
    assert(newVERTEX != 0);

    newVERTEX->repIndex = rep;
    newVERTEX->index = 0;
    newVERTEX->value = store;
    newVERTEX->rank = 0;
    newVERTEX->isRep = 1;


    return newVERTEX;
}

extern SET *newSET(void) {

    SET *newSet = (SET*)malloc(sizeof(SET));
    assert(newSet != 0);
    newSet->display = 0;
    newSet->free = 0;
    newSet->representatives = newDA();
    assert(newSet->representatives != 0);
    newSet->numReps = 0;
    newSet->level = 0;

    return newSet;
}

extern void  setSETdisplay(SET *s,void (*d)(void * ptr,FILE * fp)) {
    s->display = d;
}
extern void  setSETfree(SET *s,void (*d)(void * ptr)) {
    s->free = d;
}

extern int makeSET(SET *d,void* value) {
    VERTEX * newValue = newVERTEX(0, value);
    newValue->repIndex = sizeDA(d->representatives);
    newValue->index = newValue->repIndex;
    int tempIndex = sizeDA(d->representatives);
    insertDA(d->representatives, tempIndex, newValue);
    d->numReps++;

    return (sizeDA(d->representatives)-1);
}

extern int findSET(SET *d,int index) {

    VERTEX *value = getDA(d->representatives, index);


    if(value->index != value->repIndex) {
        value->repIndex = findSET(d, value->repIndex);
    }

    return value->repIndex;
}

extern int unionSET(SET *d,int index1,int index2) {
    if(findSET(d, index1) == findSET(d, index2)) return 0;
    d->numReps--;
    VERTEX *v1 = getDA(d->representatives, index1);
    VERTEX *v2 = getDA(d->representatives, index2);
    VERTEX *v1Rep = v1; while(v1Rep->index != v1Rep->repIndex) {v1Rep = getDA(d->representatives, v1Rep->repIndex);}
    VERTEX *v2Rep = v2; while(v2Rep->index != v2Rep->repIndex) {v2Rep = getDA(d->representatives, v2Rep->repIndex);}


    if(rank(d, v1Rep) > rank(d, v2Rep)) {

        v2Rep->repIndex = v1Rep->repIndex;
        v2Rep->isRep = 0;
        //v2Rep->rank++;

    }
    else if(rank(d, v1Rep) < rank(d, v2Rep)) {

        v1Rep->repIndex = v2Rep->repIndex;
        v1Rep->isRep = 0;
        //v1Rep->rank++;

    }
    else {

        if(v1Rep->repIndex < v2Rep->repIndex) {

            v2Rep->repIndex = v1Rep->repIndex;
            //v2Rep->rank++;
            v1Rep->rank++;
            //v2Rep->isRep = 1;
            v2Rep->isRep = 0;
            v1Rep->isRep = 1;
        }
        else {

            v1Rep->repIndex = v2Rep->repIndex;
            //v1Rep->rank++;
            v2Rep->rank++;
            v2Rep->isRep = 1;
            v1Rep->isRep = 0;

        }
    }

    return 1;

}

extern void displaySET(SET *d, FILE *fp) {

    int i = 0;

    for(i = 0; i < sizeDA(d->representatives); i++) {
        fprintf(fp, "%d: ", i);
        VERTEX *currVERTEX = getDA(d->representatives, i);
        d->display(currVERTEX->value, fp);
        if(currVERTEX->isRep == 1) {
            fprintf(fp, "(%d)", currVERTEX->rank);
        }
        while(currVERTEX->index != currVERTEX->repIndex) {

            currVERTEX = getDA(d->representatives, currVERTEX->repIndex);

            fprintf(fp, " ");
            d->display(currVERTEX->value, fp);

        }
        fprintf(fp, "\n");
    }

    return;

}

int rank(SET *d, VERTEX *v) {
    if(v->repIndex == v->index) return v->rank;
    else return rank(d, getDA(d->representatives, v->repIndex));

}

extern int   debugSET(SET *d,int level) {
    d->level = level;
    return 0;
}

extern void  freeSET(SET *d) {
    if(d->numReps == 0) {
        free(d);
        return;
    }

    for(int i = 0; i < sizeDA(d->representatives); i++) {
        VERTEX *currVERTEX = getDA(d->representatives, i);
        free(currVERTEX->value);
        free(currVERTEX);
    }

    freeDA(d->representatives);
    free(d);
}