/**
 * In diesem Modul..
 *  
 * @file btree.c
 * @author Dominik Krakau
 *
 * @date 2019-01-04
 */

#include <stdlib.h>
#include <stdbool.h>

#include "btree.h"

#define FREE_TREE(TREE) { free((TREE)->root);           \
                          free((TREE)->destroy_data);   \
                          free((TREE)->print);          \
                          (TREE) = NULL; }

#define CHECK_TREE(TREE) {(TREE) == NULL ? exit(EXIT_FAILURE): (TREE);}

//static void PRINT_DATA_FCT print_fct;

//static void print_recursive(BTREE_NODE *node, int level_count);

extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data, 
                        PRINT_DATA_FCT print_data)
{
    BTREE *new_tree = malloc(sizeof (BTREE));
    CHECK_TREE(new_tree);
    
//    print_fct = print_data;
    
    new_tree->size = 1;
    new_tree->destroy_data = destroy_data;
    new_tree->print = print_data;
    new_tree->root = btreenode_new(data);

    return new_tree;
}

extern BTREE *btree_clone(BTREE *tree)
{
    
    BTREE *cloned_tree = NULL;
    
    return cloned_tree;
}

extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    
}

extern bool btree_equals(BTREE *tree1, BTREE *tree2)
{
    BTREE_NODE root_tree1 = btree_get_root(tree1);
    BTREE_NODE root_tree2 = btree_get_root(tree2);
    
    bool is_equals = false;
    
    is_equals = btreenode_get_data(root_tree1) == btreenode_get_data(root_tree2);
    
    while(is_equals)
    {
        
        is_equals = btreenode_get_data(btreenode_get_left(root_tree1));
    }
    
    return false;
}

extern BTREE_NODE *btree_get_root(BTREE *tree)
{
    CHECK_TREE(tree);
    
    return tree->root;
}

extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data)
{
    BTREE merged_tree = malloc(sizeof (BTREE));
    CHECK_TREE(merged_tree);
    
    merged_tree->root = btreenode_new(data);
    merged_tree->size += left->size + right->size;
    merged_tree->root->left = btree_get_root(left); // alternative left->root;
    merged_tree->root->right = btree_get_root(right);
    merged_tree->destroy_data =  left->destroy_data;
    merged_tree->print = left->destroy_data;
   
    FREE_TREE(left);
    FREE_TREE(right);
    
    return merged_tree;
}

extern void btree_print(BTREE *tree)
{
    CHECK_TREE(tree);
}

//static void print_recursive(BTREE_NODE *node, int level_count) {
//    int i;
//
//    if (node == NULL) {
//        return;
//    }
//
//    for (i = 0; i < level_count; i++) {
//        printf("    ");
//    }
//    printf("|-- ");
//
//    btreenode_print(node, print_fct);
//
//    level_count++;
//    print_recursive(node->left, level_count);
//    print_recursive(node->right, level_count);
//}
