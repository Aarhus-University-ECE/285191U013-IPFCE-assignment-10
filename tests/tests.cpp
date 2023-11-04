#include <catch2/catch_test_macros.hpp>

extern "C" {
#include <assert.h>
#include "btree.h"
#include "linked_list.h"
}

void free_list(node* list) {
	node* it = list;
	while (it != NULL) {
		node* next = it->next;
		free(it);
		it = next;
	}
}

TEST_CASE("sum_squares") {

	// exercise 2
	{
		node*	  list = make_node(1, make_node(2, make_node(3, make_node(4, make_node(5, NULL)))));
		const int sum = sum_squares(list);
		REQUIRE(sum == 55);
		free_list(list);
	}
	{
		node*	  list = NULL;
		const int sum = sum_squares(list);
		REQUIRE(sum == 0);
	}
	{
		node*	  list = make_node(1, NULL);
		const int sum = sum_squares(list);
		REQUIRE(sum == 1);
		free_list(list);
	}
}

TEST_CASE("map") {
	// exercise 3
	{
		node* list = make_node(1, NULL);
		node* mapped_list = map(list, square);
		node* it = mapped_list;
		REQUIRE(it->data == 1);
		it = it->next;
		REQUIRE(it == NULL);
		const int sum = sum_squares(mapped_list);
		REQUIRE(sum == 1);
		free_list(list);
		free_list(mapped_list);
	}
	{
		node* list = make_node(1, make_node(2, make_node(3, NULL)));
		node* mapped_list = map(list, square);
		node* it = mapped_list;
		REQUIRE(it->data == 1);
		it = it->next;
		REQUIRE(it->data == 4);
		it = it->next;
		REQUIRE(it->data == 9);
		it = it->next;
		REQUIRE(it == NULL);

		const int sum = sum_squares(mapped_list);
		// 1^2 + 4^2 + 9^2 = 1 + 16 + 81 = 98
		REQUIRE(sum == square(1) + square(4) + square(9));

		node* mapped_mapped_list = map(mapped_list, square);
		it = mapped_mapped_list;
		REQUIRE(it->data == 1);
		it = it->next;
		REQUIRE(it->data == 16);
		it = it->next;
		REQUIRE(it->data == 81);
		it = it->next;
		REQUIRE(it == NULL);

		const int mapped_sum = sum_squares(mapped_mapped_list);
		// 1^2 + 16^2 + 81^2 = 1 + 256 + 6561 = 6818
		REQUIRE(mapped_sum == square(1) + square(16) + square(81));
		free_list(list);
		free_list(mapped_list);
	}
}

bool is_binary_search_tree(btree_node *root) {
    if (root == NULL) {
        return true;
    }

    if (root->left != NULL && root->left->item >= root->item) {
        return false;
    }

    if (root->right != NULL && root->right->item <= root->item) {
        return false;
    }

    return is_binary_search_tree(root->left) && is_binary_search_tree(root->right);
}

void btree_free(btree_node *root) {
	if (root == NULL) {
		return;
	} else {
		btree_free(root->left);
		btree_free(root->right);
		free(root);
	}
}

btree_node *btree_allocate(int item) {
	btree_node *root = (btree_node*)malloc(sizeof(btree_node));
	assert(root != NULL);
	root->item = item;
	root->left = NULL;
	root->right = NULL;
	return root;
}

TEST_CASE("btree_empty") {
	btree_node* root = NULL;
	REQUIRE(btree_empty(root));

	root = (btree_node*)malloc(sizeof(btree_node));
	root->item = 42;
	root->left = NULL;
	root->right = NULL;
	REQUIRE(!btree_empty(root));
}


TEST_CASE("btree_insert") {
	btree_node* root = NULL;
	root = btree_insert(42, root);
	REQUIRE(root->item == 42);
	root = btree_insert(17, root);
	REQUIRE(root->left->item == 17);
	root = btree_insert(100, root);
	REQUIRE(root->right->item == 100);

	btree_free(root);
}


TEST_CASE("btree_contains") {
	btree_node* root = NULL;
	root = btree_allocate(42);
	REQUIRE(btree_contains(42, root));

	btree_node *left = btree_allocate(17);
	btree_node *right = btree_allocate(100);
	root->left = left;
	root->right = right;

	REQUIRE(btree_contains(42, root));
	REQUIRE(btree_contains(17, root));
	REQUIRE(btree_contains(100, root));

	btree_node *right_left = btree_allocate(50);
	right->left = right_left;

	// pp_btree_node(root, 4, 0);

	REQUIRE(btree_contains(42, root));
	REQUIRE(btree_contains(17, root));
	REQUIRE(btree_contains(100, root));
	REQUIRE(btree_contains(50, root));

	btree_node *right_left_left = btree_allocate(48);
	right_left->left = right_left_left;

	// pp_btree_node(root, 4, 0);

	REQUIRE(btree_contains(42, root));
	REQUIRE(btree_contains(17, root));
	REQUIRE(btree_contains(100, root));
	REQUIRE(btree_contains(50, root));
	REQUIRE(btree_contains(48, root));

	btree_free(root);
}

TEST_CASE("btree_remove") {
	btree_node* root = NULL;
	root = btree_allocate(20);

	btree_node *left = btree_allocate(5);
	root->left = left;
	btree_node *left_left = btree_allocate(1);
	left->left = left_left;
	btree_node *left_right = btree_allocate(15);
	left->right = left_right;
	btree_node * left_right_left = btree_allocate(9);
	left_right->left = left_right_left;
	btree_node * left_right_left_right = btree_allocate(12);
	left_right_left->right = left_right_left_right;
	btree_node *left_right_left_left = btree_allocate(7);
	left_right_left->left = left_right_left_left;

	btree_node *right = btree_allocate(30);
	root->right = right;
	btree_node *right_left = btree_allocate(25);
	right->left = right_left;
	btree_node *right_right = btree_allocate(40);
	right->right = right_right;
	btree_node *right_right_right = btree_allocate(45);
	right_right->right = right_right_right;
	btree_node *right_right_right_left = btree_allocate(42);
	right_right_right->left = right_right_right_left;

	//               20
	//             /    \
	//            /      \
	//           5       30
	//         /   \     /\
	//        /     \   /  \
	//       1      15 25  40
	//            /          \
	//           /            \
	//          9             45
	//        /   \          /
	//       /     \        /
	//      7      12      42

	// There are 4 cases that the btree_remove() function has too handle
	// 1. The node to be removed is a leaf
	root = btree_remove(25, root);
	pp_btree_node(root, 4, 0);

	//               20
	//             /    \
	//            /      \
	//           5       30
	//         /   \      \
	//        /     \      \
	//       1      15     40
	//            /          \
	//           /            \
	//          9             45
	//        /   \          /
	//       /     \        /
	//      7      12      42

	REQUIRE(root != NULL);
	REQUIRE(root->item == 20);
	REQUIRE(root->left != NULL);
	REQUIRE(root->left->item == 5);
	REQUIRE(root->left->left != NULL);
	REQUIRE(root->left->left->item == 1);
	REQUIRE(root->left->left->left == NULL); // 1 has no left child
	REQUIRE(root->left->left->right == NULL); // 1 has no right child
	REQUIRE(root->left->right != NULL);
	REQUIRE(root->left->right->item == 15);
	REQUIRE(root->left->right->left != NULL);
	REQUIRE(root->left->right->right == NULL); // 15 has no right child
	REQUIRE(root->left->right->left->item == 9);
	REQUIRE(root->left->right->left->left != NULL);
	REQUIRE(root->left->right->left->left->item == 7);
	REQUIRE(root->left->right->left->left->left == NULL); // 7 has no left child
	REQUIRE(root->left->right->left->left->right == NULL); // 7 has no right child
	REQUIRE(root->left->right->left->right != NULL);
	REQUIRE(root->left->right->left->right->item == 12);
	REQUIRE(root->left->right->left->right->left == NULL); // 12 has no left child
	REQUIRE(root->left->right->left->right->right == NULL); // 12 has no right child

	REQUIRE(root->right != NULL);
	REQUIRE(root->right->item == 30);
	REQUIRE(root->right->left == NULL); // 30 has no left child
	REQUIRE(root->right->right != NULL);
	REQUIRE(root->right->right->item == 40);
	REQUIRE(root->right->right->left == NULL); // 40 has no left child
	REQUIRE(root->right->right->right != NULL);
	REQUIRE(root->right->right->right->item == 45);
	REQUIRE(root->right->right->right->right == NULL); // 45 has no right child
	REQUIRE(root->right->right->right->left != NULL);
	REQUIRE(root->right->right->right->left->item == 42);
	REQUIRE(root->right->right->right->left->left == NULL); // 42 has no left child
	REQUIRE(root->right->right->right->left->right == NULL); // 42 has no right child

	// 2. The node to be removed has only has a left child
	root = btree_remove(45, root);
	pp_btree_node(root, 4, 0);

	//               20
	//             /    \
	//            /      \
	//           5       30
	//         /   \      \
	//        /     \      \
	//       1      15     40
	//            /          \
	//           /            \
	//          9             42
	//        /   \          
	//       /     \        
	//      7      12      

	REQUIRE(root != NULL);
	REQUIRE(root->item == 20);
	REQUIRE(root->left != NULL);
	REQUIRE(root->left->item == 5);
	REQUIRE(root->left->left != NULL);
	REQUIRE(root->left->left->item == 1);
	REQUIRE(root->left->left->left == NULL); // 1 has no left child
	REQUIRE(root->left->left->right == NULL); // 1 has no right child
	REQUIRE(root->left->right != NULL);
	REQUIRE(root->left->right->item == 15);
	REQUIRE(root->left->right->right == NULL); // 15 has no right child
	REQUIRE(root->left->right->left != NULL);
	REQUIRE(root->left->right->left->item == 9);
	REQUIRE(root->left->right->left->left != NULL);
	REQUIRE(root->left->right->left->left->item == 7);
	REQUIRE(root->left->right->left->left->left == NULL); // 7 has no left child
	REQUIRE(root->left->right->left->left->right == NULL); // 7 has no right child
	REQUIRE(root->left->right->left->right != NULL);
	REQUIRE(root->left->right->left->right->item == 12);
	REQUIRE(root->left->right->left->right->left == NULL); // 12 has no left child
	REQUIRE(root->left->right->left->right->right == NULL); // 12 has no right child


	REQUIRE(root->right != NULL);
	REQUIRE(root->right->item == 30);
	REQUIRE(root->right->left == NULL); // 30 has no left child
	REQUIRE(root->right->right != NULL);
	REQUIRE(root->right->right->item == 40);
	REQUIRE(root->right->right->left == NULL); // 40 has no left child
	REQUIRE(root->right->right->right != NULL);
	REQUIRE(root->right->right->right->item == 42);
	REQUIRE(root->right->right->right->left == NULL); // 42 has no left child
	REQUIRE(root->right->right->right->right == NULL); // 42 has no right child

	// 3. The node to be removed has only has a right child

	root = btree_remove(30, root);
	pp_btree_node(root, 4, 0);

	//               20
	//             /    \
	//            /      \
	//           5       40
	//         /   \      \
	//        /     \      \
	//       1      15     42
	//            /          
	//           /            
	//          9             
	//        /   \          
	//       /     \        
	//      7      12      

	REQUIRE(root != NULL);
	REQUIRE(root->item == 20);
	REQUIRE(root->left != NULL);
	REQUIRE(root->left->item == 5);
	REQUIRE(root->left->left != NULL);
	REQUIRE(root->left->left->item == 1);
	REQUIRE(root->left->left->left == NULL); // 1 has no left child
	REQUIRE(root->left->left->right == NULL); // 1 has no right child
	REQUIRE(root->left->right != NULL);
	REQUIRE(root->left->right->item == 15);
	REQUIRE(root->left->right->right == NULL); // 15 has no right child
	REQUIRE(root->left->right->left != NULL);
	REQUIRE(root->left->right->left->item == 9);
	REQUIRE(root->left->right->left->left != NULL);
	REQUIRE(root->left->right->left->left->item == 7);
	REQUIRE(root->left->right->left->left->left == NULL); // 7 has no left child
	REQUIRE(root->left->right->left->left->right == NULL); // 7 has no right child
	REQUIRE(root->left->right->left->right != NULL);
	REQUIRE(root->left->right->left->right->item == 12);

	REQUIRE(root->right != NULL);
	REQUIRE(root->right->item == 40);
	REQUIRE(root->right->left == NULL); // 40 has no left child
	REQUIRE(root->right->right != NULL);
	REQUIRE(root->right->right->item == 42);
	REQUIRE(root->right->right->left == NULL); // 42 has no left child
	REQUIRE(root->right->right->right == NULL); // 42 has no right child

	// 4. The node to be removed has both left and right children
	root = btree_remove(5, root);
	pp_btree_node(root, 4, 0);

	//               20
	//             /    \
	//            /      \
	//           7       40
	//         /   \      \
	//        /     \      \
	//       1      15     42
	//            /          
	//           /            
	//          9             
	//           \          
	//            \        
	//            12      
	
	REQUIRE(root != NULL);
	REQUIRE(root->item == 20);
	REQUIRE(root->left != NULL);
	REQUIRE(root->left->item == 7);
	REQUIRE(root->left->left != NULL);
	REQUIRE(root->left->left->item == 1);
	REQUIRE(root->left->left->left == NULL); // 1 has no left child
	REQUIRE(root->left->left->right == NULL); // 1 has no right child
	REQUIRE(root->left->right != NULL);
	REQUIRE(root->left->right->item == 15);
	REQUIRE(root->left->right->right == NULL); // 15 has no right child
	REQUIRE(root->left->right->left != NULL);
	REQUIRE(root->left->right->left->item == 9);
	REQUIRE(root->left->right->left->left == NULL); // 9 has no left child
	REQUIRE(root->left->right->left->right != NULL);
	REQUIRE(root->left->right->left->right->item == 12);
	REQUIRE(root->left->right->left->right->left == NULL); // 12 has no left child
	REQUIRE(root->left->right->left->right->right == NULL); // 12 has no right child

	REQUIRE(root->right != NULL);
	REQUIRE(root->right->item == 40);
	REQUIRE(root->right->left == NULL); // 40 has no left child
	REQUIRE(root->right->right != NULL);
	REQUIRE(root->right->right->item == 42);
	REQUIRE(root->right->right->left == NULL); // 42 has no left child
	REQUIRE(root->right->right->right == NULL); // 42 has no right child	
	
	btree_free(root);
}


// Test entire btree API
TEST_CASE("btree") {
	//               20
  //             /    \
  //            /      \
  //           5       30
  //         /   \     /\
  //        /     \   /  \
  //       1      15 25  40
  //            /          \
  //           /            \
  //          9             45
  //        /   \          /
  //       /     \        /
  //      7      12      42
  
	btree_node* root = NULL;
	REQUIRE(btree_empty(root));

	const int values[] = { 20, 5, 1, 15, 9, 7, 12, 30, 25, 40, 45, 42 };
	// const int len = sizeof(values) / sizeof(values[0]);
	// for (int i = 0; i < len; i++) {
	// 	root = btree_insert(values[i], root);
	// }

	root = btree_insert(values[0], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[1], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[2], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[3], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[4], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[5], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[6], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[7], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[8], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[9], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[10], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	// pp_btree_node(root, 4, 0);

	root = btree_insert(values[11], root);
	REQUIRE(!btree_empty(root));
	REQUIRE(!btree_full(root));
	REQUIRE(is_binary_search_tree(root));
	pp_btree_node(root, 4, 0);

	REQUIRE(btree_contains(20, root));
	REQUIRE(btree_contains(5, root));
	REQUIRE(btree_contains(1, root));
	REQUIRE(btree_contains(15, root));
	REQUIRE(btree_contains(9, root));
	REQUIRE(btree_contains(7, root));
	REQUIRE(btree_contains(12, root));
	REQUIRE(btree_contains(30, root));
	REQUIRE(btree_contains(25, root));
	REQUIRE(btree_contains(40, root));
	REQUIRE(btree_contains(45, root));
	REQUIRE(btree_contains(42, root));

	const int value_not_it_btree = -5;
	REQUIRE(!btree_contains(value_not_it_btree, root));
	// REQUIRE(btree_remove(value_not_it_btree, root) == NULL);


	// 

	// // (B) and (C)

	// root = Insert(3, root);

	// REQUIRE(Contains(3, root) == 1);

	// root = Remove(3, root);

	// REQUIRE(Contains(20, root) == 1);
	// REQUIRE(Contains(5, root) == 1);
	// REQUIRE(Contains(1, root) == 1);
	// REQUIRE(Contains(15, root) == 1);
	// REQUIRE(Contains(9, root) == 1);
	// REQUIRE(Contains(7, root) == 1);
	// REQUIRE(Contains(12, root) == 1);
	// REQUIRE(Contains(30, root) == 1);
	// REQUIRE(Contains(25, root) == 1);
	// REQUIRE(Contains(40, root) == 1);
	// REQUIRE(Contains(45, root) == 1);
	// REQUIRE(Contains(42, root) == 1);

	// REQUIRE(Contains(2, root) == 0);
	// REQUIRE(Contains(3, root) == 0);

	// // (D) and (E)
	// root = Insert(-1, root);
	// root = Insert(-1, root);
	// root = Remove(-1, root);
	// REQUIRE(Contains(-1, root) == 1);
	// root = Remove(-1, root);
	// REQUIRE(Contains(-1, root) == 0);

	// root = Remove(45, root);
	// root = Remove(42, root);
	// root = Insert(16, root);

	// REQUIRE(Contains(20, root) == 1);
	// REQUIRE(Contains(5, root) == 1);
	// REQUIRE(Contains(1, root) == 1);
	// REQUIRE(Contains(15, root) == 1);
	// REQUIRE(Contains(9, root) == 1);
	// REQUIRE(Contains(7, root) == 1);
	// REQUIRE(Contains(12, root) == 1);
	// REQUIRE(Contains(30, root) == 1);
	// REQUIRE(Contains(25, root) == 1);
	// REQUIRE(Contains(40, root) == 1);
	// REQUIRE(Contains(45, root) == 0);
	// REQUIRE(Contains(42, root) == 0);
	// REQUIRE(Contains(16, root) == 1);

	// root = Remove(7, root);

	// REQUIRE(Contains(16, root) == 1);
	// REQUIRE(Contains(20, root) == 1);
	// REQUIRE(Contains(5, root) == 1);jjj
	// REQUIRE(Contains(1, root) == 1);
	// REQUIRE(Contains(15, root) == 1);
	// REQUIRE(Contains(9, root) == 1);
	// REQUIRE(Contains(7, root) == 0);
	// REQUIRE(Contains(12, root) == 1);
	// REQUIRE(Contains(30, root) == 1);
	// REQUIRE(Contains(25, root) == 1);
	// REQUIRE(Contains(40, root) == 1);
	// REQUIRE(Contains(45, root) == 0);

	// root = Remove(1, root);
	// root = Remove(7, root);
	// root = Remove(12, root);
	// root = Remove(9, root);
	// root = Remove(15, root);
	// root = Remove(5, root);
	// root = Remove(42, root);
	// root = Remove(45, root);
	// root = Remove(25, root);
	// root = Remove(40, root);
	// root = Remove(30, root);
	// root = Remove(20, root);
	// root = Remove(16, root);


	btree_free(root);
}
