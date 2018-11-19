#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
// stores a freeMethod function pointer in TNODE struct
typedef void (*FM)(void * ptr);
// stores a displayMethod function pointer in TNODE struct
typedef void (*DM)(void * ptr, FILE *fp);

struct set {
  DA * store;
  int repIndex; // index of set representative
  FM free;
  DM display;
};

static void setRepIndex(SET *s, int i);
static int getRepIndex(SET *s);
////////////////////////////////////////////////////////////////////////////////
extern SET *newSET(void) {
  SET * s = malloc(sizeof(SET));
  s->store = newDA();
  s->repIndex = -1;
  s->free = 0;
  s->display = 0;
}

extern void setSETdisplay(SET *s, void (*d)(void *, FILE *)) {
  s->display = d;
}

extern void setSETfree(SET *s, void (*f)(void *)) {
  s->free = f;
}

extern int makeSET(SET *d, void *value) {
  DA * array = s->store;
  insertDAback(array, value);
  setRepIndex(d, sizeDA(array));
  return getRepIndex(d);
}

extern int findSET(SET *d, int index) {

}

extern int unionSET(SET *d, int index1, int index2);

extern void displaySET(SET *d, FILE *fp);

extern int debugSET(SET *d, int level);

extern void freeSET(SET *d);

////////////////////////////////////////////////////////////////////////////////
static void setRepIndex(SET *s, int i) {
  s->repIndex = i;
}

static int getRepIndex(SET *s) {
  return s->repIndex;
}
