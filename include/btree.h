#ifndef BTREE_H
#define BTREE_H

struct node
{
  int item;
  struct node *left;
  struct node *right;
};

int Empty (struct node *t);
static struct node * Insert (int x, struct node *t);
static struct node * Remove (int x, struct node *t);
static int Contains (int x, struct node *t);
static struct node * Initialize (struct node *t);
static int Full (struct node *t);

#endif // BTREE_H