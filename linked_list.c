#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

node *make_node(const int v, node *q) {
  node *p = (node*) malloc(sizeof(node));
  if (p == NULL) {
    fprintf(stderr, "%s:%d Failed to allocate memory\n", __FILE__, __LINE__);
    exit(1);
  }

  p->value = v;
  p->next = q;
  return p;
}

// exercise 1
void print_list(node *p) {

}

// exercise 2
int sum_squares(node *p) {
  return -1;
}

// exercise 3
node *map(node *p, int(*f)(int)) { 
  return NULL; 
}

int square(const int x) { return x * x; }

// example of another function that can be passed to map
// returns the sign of the number
// -1 if negative, 0 if zero, 1 if positive
int sign(const int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
