#pragma once

#include <stdbool.h>

typedef struct btree_node {
	int				   item;
	struct btree_node* left;
	struct btree_node* right;
} btree_node;

btree_node* initialize(btree_node* root);

btree_node* insert(const int x, btree_node* root);
btree_node* remove(const int x, btree_node* root);

bool empty(btree_node* root);
bool contains(const int x, btree_node* root);
bool full(btree_node* root);


