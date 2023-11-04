#pragma once

#include <stdbool.h>

typedef struct btree_node {
	int				   data;
	struct btree_node* left;
	struct btree_node* right;
} btree_node;

btree_node* btree_insert(const int x, btree_node* root);
btree_node* btree_remove(const int x, btree_node* root);

bool btree_empty(btree_node* root);
bool btree_contains(const int x, btree_node* root);
bool btree_full(btree_node* root);

/// Pretty print a btree_node tree
/// @param root The root of the tree
/// @param indent_by The number of spaces to indent by at each level
/// @param depth The current depth of the tree. (When called with root, depth = 0)
void pp_btree_node(const btree_node* root, const int indent_by, const int depth);
