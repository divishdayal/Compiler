// Sugam Garg - 2014A7PS092P, Divish Dayal - 2014A7PS132P

#ifndef _parseTreeDef
#define _parseTreeDef
typedef struct tree_node{
    int num;
    char name[20];
    struct tree_node * lchild;
    struct tree_node * rchild;
    struct tree_node * parent;
    struct tree_node * next;
}tree_node;


typedef struct stack_node{
    int num;
    char name[20];
    struct stack_node * next;
    tree_node * node_tree;
} stack_node;


#endif
