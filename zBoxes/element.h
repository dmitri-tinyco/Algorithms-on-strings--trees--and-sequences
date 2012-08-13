#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element{
  int index;
  const char letter;
  int zValue;
  int left;
  int right;
} ELEMENT;

ELEMENT *el_create(int index, char letter, int zValue, int left, int right) {
    ELEMENT init = {.index = index, .letter = letter, .zValue = zValue, .left = left, .right = right};
    ELEMENT *el = malloc(sizeof *el);
    if (el==NULL) return NULL;
    memcpy(el, &init, sizeof *el);
    return el;
}

int el_release(void *el) {
    free((ELEMENT *)el);
    return 0;
}

int print_element(void *el) {
    printf("%i - %c - %i - %i - %i\n", ((ELEMENT *)el)->index, ((ELEMENT *)el)->letter, ((ELEMENT *)el)->zValue, ((ELEMENT *)el)->left, ((ELEMENT *)el)->right);
    return 0;
}


