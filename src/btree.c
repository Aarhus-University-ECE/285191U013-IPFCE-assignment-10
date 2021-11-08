#include "btree.h"

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>


struct node * Insert (int x, struct node *t)
{
  if (Empty (t))
    {
      t = malloc (sizeof (struct node));
      t->item = x;
      t->right = NULL;
      t->left = NULL;
    }
  else if (x > t->item)
    t->right = Insert (x, t->right);

  else
    t->left = Insert (x, t->left);

  return t;
}

struct node * Remove (int x, struct node *t)
{
  if (Empty (t))
    return NULL;
  else if (t->item == x)
    {

      // node with only one child or no child 
      if (t->left == NULL)
	{
	  struct node *temp = t->right;
	  free (t);
	  return temp;
	}
      else if (t->right == NULL)
	{
	  struct node *temp = t->left;
	  free (t);
	  return temp;
	}
      else
	{
	  struct node *temp = t->right;
	  while (temp->left)
	    temp = temp->left;
	  assert (temp->left == NULL);
	  temp->left = t->left;
	  return t->right;

	}

      // If we have more than one child we need to search the next inorder... 

    }
  else if (x > t->item)
    t->right = Remove (x, t->right);

  else
    t->left = Remove (x, t->left);

  return t;
}


int Contains (int x, struct node *t)
{

  if (Empty (t))
    return 0;

  else if (t->item == x)
    return 1;

  else if (x > t->item)
    return Contains (x, t->right);

  else
    return Contains (x, t->left);

}


struct node * Initialize (struct node *t)
{
  t = NULL;
  return t;
}

int Empty (struct node *t)
{
  return (t == NULL);
}

int Full (struct node *t)
{
  if (Empty (t))
    return true;



  // If leaf node 
  else if (t->left == NULL && t->right == NULL)
    return true;

  // If both left and right are not NULL, and left & right subtrees 
  // are full 
  if ((t->left) && (t->right))
    return (Full (t->left) && Full (t->right));

  else
    return false;
}
