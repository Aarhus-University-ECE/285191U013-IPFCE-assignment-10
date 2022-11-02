#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "linked_list.h"

// File for sandboxing and trying out code
int main(int argc, char **argv)
{
	  node* ns = make_node(1, make_node(2, make_node(3, make_node(4, make_node(5, NULL)))));
	  print_list(ns);
	  // sum the squares of the values in the list
	  int sum = sum_squares(ns);
	  printf("sum of squares = %d\n", sum);
	  // free the list
	  free_list(ns);
	  // print the list again
	  ns = NULL;
	  print_list(ns);
	  // sum the squares of the values in the list
	  sum = sum_squares(ns);
	  printf("sum of squares = %d\n", sum);
	  // free the list
	  free_list(ns);
	  ns = NULL;

	ns = make_node (1,NULL);
	
	//ns contains one node with the value 1
	node *mns = map (ns, square);
	sum=sum_squares(ns);
	assert(sum==1);
	free_list(ns);
	ns = NULL;
  	ns = make_node (1,
			make_node (2,
				   make_node (3,
					      NULL)));
	//ns is 1->2->3
  	mns = map (ns, square);
	free_list(ns);
	ns = NULL;
	//ns is 1->4->9
	sum=sum_squares(mns);
	free_list(mns);
	mns = NULL;
	//1+16+81 = 98
	printf("sum of squares = %d\n", sum);
	assert(sum==98);

	
    return 0;
}