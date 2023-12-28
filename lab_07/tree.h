#ifndef __TREE_H__
#define __TREE_H__

#define BLANK 0
#define COLOR 1

typedef struct tree node_t;

struct tree {
    char value;
    int color;
    node_t* right;
    node_t* left;
};

// базовая работа с деревом
node_t *create_node(char val);
node_t *push_tree(node_t *root, node_t *new_node);
node_t *lookfor(node_t *root, char value);
void print_tree_post(node_t *root);
void print_tree(node_t *node, int level);
node_t *str_to_tree(char *str);

// балансировка (методом вставки)
node_t *balance_tree(node_t *root);

#endif