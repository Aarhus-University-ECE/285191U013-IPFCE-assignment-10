#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node
{
   int value;
   struct node * next;
} node;

node *make_node (int v, node * q);
void free_list (node * p);
void print_list (node * p);
int sum_squares (node * p);
node *map (node * p, int (*f) (int));
int square (int x);

#endif // LINKED_LIST_H