#include "linked_list.h"
/*
 * Linked list
 */

#include <stdio.h>		/* printf */
#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */

/* terminal node at the end of the list */
node SENTINEL = { 0, 0 };

/* functions to create lists */
node *make_node (int v, node * q)
{
  node *p = malloc (sizeof (node));
  p->value = v;

  if (q == &SENTINEL)
    p->next = &SENTINEL;
  else
    p->next = q;
  return p;
}

/* free all nodes in the list p */
void free_list (node * p)
{
  node *q = p;
  while (q != &SENTINEL)
    {
      node *t = q->next;
      free (q);
      q = t;
    }
}


/* print list to console */
void print_list (node * p)
{
    // Add your code for exercise 1
}

int sum_squares (node * p)
{
    // Add your code for excercise 2
}

node *map (node * p, int (*f) (int))
{
    // Add your code for excercise 3
}


int square (int x)
{
  return x * x;
}
