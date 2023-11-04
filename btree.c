#include "btree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

btree_node *btree_insert(const int x, btree_node *root) {
  return NULL;
}

btree_node *btree_remove(const int x, btree_node *root) {
  return NULL;
}

bool btree_contains(const int x, btree_node *root) {
  return false;
}

bool btree_empty(btree_node *root) {
  return false;
}

bool btree_full(btree_node *root) {
  return false;
}



void pp_btree_node(const btree_node *node, const int indent_by, const int depth) {
    assert(0 < indent_by);
    assert(0 <= depth);

    const char* ANSI_RESET = "\x1b[0m";
    const char* ANSI_RED = "\x1b[31m";
    const char* ANSI_GREEN = "\x1b[32m";
    const char* ANSI_YELLOW = "\x1b[33m";
    const char* ANSI_BLUE = "\x1b[34m";
    const char* ANSI_MAGENTA = "\x1b[35m";
    const char* ANSI_CYAN = "\x1b[36m";
    // const char* ANSI_WHITE = "\x1b[37m";
    const char* ANSI_BOLD = "\x1b[1m";

    const int level = depth / indent_by;
    char *brace_color;
    switch (level % 3) {
        case 0:
            brace_color = (char*) ANSI_MAGENTA;
            break;
        case 1:
            brace_color = (char*) ANSI_YELLOW;
            break;
        case 2:
            brace_color = (char*) ANSI_CYAN;
            break;
    }

    if (node == NULL) {
        printf("%sNULL%s%s;%s\n", ANSI_RED, ANSI_RESET, brace_color, ANSI_RESET);
        return;
    }

    const int whitespace_amount = indent_by + depth;
    printf("(%sbtree_node%s) %s{%s", ANSI_BLUE, ANSI_RESET, brace_color, ANSI_RESET);
    // printf(" (%p)", (void*) node); // print the address in hex
    printf("\n");
    for (int i = 0; i < whitespace_amount; i++) {
        printf(" ");
    }
    printf("%s.item%s  = %s%d%s,\n", ANSI_BOLD, ANSI_RESET, ANSI_GREEN, node->data, ANSI_RESET);
    for (int i = 0; i < whitespace_amount; i++) {
        printf(" ");
    }
    printf("%s.left%s  = ", ANSI_BOLD, ANSI_RESET);
    if (node->left == NULL) {
        printf("%sNULL%s,\n", ANSI_RED, ANSI_RESET);
    } else {
        pp_btree_node(node->left, indent_by, depth + indent_by);
    }
    for (int i = 0; i < whitespace_amount; i++) {
        printf(" ");
    }
    printf("%s.right%s = ", ANSI_BOLD, ANSI_RESET);
    if (node->right == NULL) {
        printf("%sNULL%s,\n", ANSI_RED, ANSI_RESET);
    } else {
        pp_btree_node(node->right, indent_by, depth + indent_by);
    }
    for (int i = 0; i < whitespace_amount - indent_by; i++) {
        printf(" ");
    }
    char comma_or_semicolon = (depth == 0) ? ';' : ',';
    printf("%s}%s%c\n", brace_color, ANSI_RESET, comma_or_semicolon);
}
