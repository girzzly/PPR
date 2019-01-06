/**
 * In diesem Modul..
 *  
 * @file btree.c
 * @author Dominik Krakau
 *
 * @date 2019-01-04
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "btree.h"

#define FREE_TREE(TREE) { free((TREE));      \
                          (TREE) = NULL; }         

#define CHECK_TREE(TREE) { ((TREE) == NULL) ? exit(EXIT_FAILURE) : (TREE); }

static PRINT_DATA_FCT print_fct;

static void btree_print_recursive(BTREE_NODE *node, int level_count);

static bool btree_equals_recursive(BTREE_NODE *root_tree1, BTREE_NODE *root_tree2);

extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data, 
                        PRINT_DATA_FCT print_data)
{
    BTREE *new_tree = malloc(sizeof (BTREE));
    CHECK_TREE(new_tree);
    
    print_fct = print_data;
    
    new_tree->destroy_data = destroy_data;
    new_tree->print = print_data;
    new_tree->root = btreenode_new(data);

    return new_tree;
}

extern BTREE *btree_clone(BTREE *tree)
{
    BTREE_NODE *cloned_root = btreenode_clone(btree_get_root(tree));
    BTREE *cloned_tree = btree_new(cloned_root->data, tree->destroy_data, tree->print);
    
    btreenode_set_left(cloned_tree->root, cloned_root->left);
    btreenode_set_right(cloned_tree->root, cloned_root->right); 
    
    return cloned_tree;
}

extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    if(destroy_data) {
        btreenode_destroy(&((*tree)->root), (*tree)->destroy_data);
    }
    else {
        btreenode_destroy(&((*tree)->root), NULL);
    }  
    
    FREE_TREE(*tree);
}

extern bool btree_equals(BTREE *tree1, BTREE *tree2)
{    
    
    return btree_equals_recursive(btree_get_root(tree1), btree_get_root(tree2));
}

extern BTREE_NODE *btree_get_root(BTREE *tree)
{
    CHECK_TREE(tree);
    
    return tree->root;
}

extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data)
{
    BTREE *merged_tree = malloc(sizeof (BTREE));
    CHECK_TREE(merged_tree);
    
    merged_tree->root = btreenode_new(data);
    merged_tree->root->left = btree_get_root(left); // alternative left->root;
    merged_tree->root->right = btree_get_root(right);
    merged_tree->destroy_data = left->destroy_data;
    merged_tree->print = left->print;
   
    FREE_TREE(left);
    FREE_TREE(right);
    
    return merged_tree;
}

extern void btree_print(BTREE *tree)
{
    CHECK_TREE(tree);
    btree_print_recursive(btree_get_root(tree), 0);
    
    printf("\n");
}

static bool btree_equals_recursive(BTREE_NODE *root_tree1, BTREE_NODE *root_tree2)
{
    if (root_tree1 == NULL && root_tree2 == NULL) 
    {
        return true; 
    }
    else {
        return (root_tree1->data == root_tree2->data && 
            btree_equals_recursive(root_tree1->left, root_tree2->left) && 
            btree_equals_recursive(root_tree1->right, root_tree2->right) );
    }
    
    return false;
}

static void btree_print_recursive(BTREE_NODE *node, int level_count) {

    if (node == NULL) {
        return;
    }
    
    int i;
    for (i = 0; i < level_count; i++) {
        printf("    ");
    }
    printf("|-- ");

    btreenode_print(node, print_fct);
    
    printf("\n");
    
    level_count++;
    btree_print_recursive(node->left, level_count);
    btree_print_recursive(node->right, level_count);
}
