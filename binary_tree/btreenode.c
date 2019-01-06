/**
 * In diesem Modul..
 *  
 * @file btreenode.c
 * @author Dominik Krakau
 *
 * @date 2019-01-04
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "btree.h"

#define CHECK_NODE(NODE) {(NODE) == NULL ? exit(EXIT_FAILURE): (NODE);}

extern BTREE_NODE *btreenode_new(void *data)
{
    BTREE_NODE *new_node = malloc(sizeof (BTREE_NODE));
    CHECK_NODE(new_node);

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;   

    return new_node;
}

extern BTREE_NODE *btreenode_clone(BTREE_NODE *node)
{
    BTREE_NODE *cloned_node = NULL;
            
    if(node != NULL)
    {
        cloned_node = btreenode_new(node->data);
        cloned_node->left = btreenode_clone(node->left);
        cloned_node->right = btreenode_clone(node->right);
    }
    
    return cloned_node;
}

bool btreenode_equals(BTREE_NODE *node1, BTREE_NODE *node2) {
    
    return (node1 != NULL && node2 != NULL
            && node1->data == node2->data
            && node1->left == node2->left
            && node1->right == node2->right);
}


extern void btreenode_destroy(BTREE_NODE **node, DESTROY_DATA_FCT destroy_data)
{
    if(*node == NULL)
    {
        return;
    }
    
    if(destroy_data != NULL)
    {
        destroy_data(&((*node)->data));
    }
    
    btreenode_destroy(&((*node)->left), destroy_data);
    btreenode_destroy(&((*node)->right), destroy_data);
    
    free(*node);
    *node = NULL;
}

extern void *btreenode_get_data(BTREE_NODE *node)
{
    CHECK_NODE(node);

    return node->data;
}

extern BTREE_NODE *btreenode_get_left(BTREE_NODE *node)
{
    CHECK_NODE(node);

    return node->left;
}

extern BTREE_NODE *btreenode_get_right(BTREE_NODE *node)
{
    CHECK_NODE(node);

    return node->right;
}

extern bool btreenode_is_leaf(BTREE_NODE *node)
{
    CHECK_NODE(node);

    return node->left == NULL && node->right == NULL;
}

extern bool btreenode_set_left(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    CHECK_NODE(parent_node);
    CHECK_NODE(node);
    
    bool has_parent_left_node = parent_node->left == NULL;
    
    if (has_parent_left_node)
    {
        parent_node->left = node;
    }

    return has_parent_left_node;
}

extern bool btreenode_set_right(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    CHECK_NODE(parent_node);
    CHECK_NODE(node);
    
    bool has_parent_right_node = parent_node->right == NULL;
    
    if (has_parent_right_node)
    {
        parent_node->right = node;
    }

    return has_parent_right_node;
}

extern void btreenode_print(BTREE_NODE *node, PRINT_DATA_FCT print_data)
{
    if(node != NULL)
    {
        printf("(%p", (void *) node);
        
        if(print_data != NULL)
        {
            print_data(node->data);
        }
        
        printf(")");
    }
}
