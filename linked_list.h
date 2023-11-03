#pragma once

typedef struct node {
  int value;
  struct node *next;
} node;

node *make_node(const int v, node *q);

// exercise 1
void print_list(node *p);

// exercise 2
int sum_squares(node *p);

// exercise 3
node *map(node *p, int(*f)(int));

int square(const int x);

