#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

void tree_to_sort_array(node_t *root, char sorted_arr[], int *idx);
node_t *sorted_array_to_balanced_tree(char sorted_arr[], int start, int finish);

// создание нового узла
node_t *create_node(char val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node)
    {
        new_node->value = val;
        new_node->color = BLANK;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

// вставка нового элемента в дерево
node_t *push_tree(node_t *root, node_t *new_node)
{
    if (root == NULL)
        return new_node;

    if (root->value > new_node->value)
        root->left = push_tree(root->left, new_node);
    else if (root->value < new_node->value)
        root->right = push_tree(root->right, new_node);
    else
    {
        root->color = COLOR;
        free(new_node);
    }
    return root;
}

// строка в дерево
node_t *str_to_tree(char *str)
{
    node_t *root = NULL;
    node_t *node = NULL;
    int size = strlen(str);
    for (int i = 0; i < size; i++)
    {
        node = create_node(str[i]);
        if (node == NULL)
            return NULL;

        root = push_tree(root, node);
    }
    return root;
}

// поиск в дереве по значению
node_t *lookfor(node_t *root, char value)
{
    if (root == NULL || root->value == value)
        return root;

    if (value > root->value)
        return lookfor(root->right, value);

    return lookfor(root->left, value);
}

// вывод постфиксным обходом
void print_tree_post(node_t *root)
{
    if (root != NULL)
    {
        print_tree_post(root->left);
        print_tree_post(root->right);

        if (root->color)
            printf("\033[1;34m");
        printf("%c\n", root->value);

        printf("\033[0m");
    }
}

// вывод как дерево
void print_tree(node_t *node, int level)
{
    if (node != NULL)
    {
        print_tree(node->right, level + 1);
        for (int i = 0; i < level; i++)
            printf("......");

        if (node->color)
            printf("\033[1;34m");
        printf("%c\n", node->value);

        if (node->color)
            printf("\033[0m");

        print_tree(node->left, level + 1);
    }
}

// преобразуем дерево в сортрованный массив
void tree_to_sort_array(node_t *root, char sorted_arr[], int *idx)
{
    if (root != NULL)
    {
        tree_to_sort_array(root->left, sorted_arr, idx);
        sorted_arr[*idx] = root->value;
        (*idx)++;
        tree_to_sort_array(root->right, sorted_arr, idx);
    }
}

// сбалансированное дерево из отсортированного массива
node_t *sorted_array_to_balanced_tree(char sorted_arr[], int start, int finish)
{
    if (start > finish)
        return NULL;

    int mid = (start + finish) / 2;

    node_t *new_root = create_node(sorted_arr[mid]);

    new_root->left = sorted_array_to_balanced_tree(sorted_arr, start, mid - 1);
    new_root->right = sorted_array_to_balanced_tree(sorted_arr, mid + 1, finish);

    return new_root;
}

// функция для балансировки дерева
node_t *balance_tree(node_t *root)
{
    char sorted_arr[60]; // массив значений, по-идее максимум 52 тк буквы латинского алфавита
    int idx = 0;

    tree_to_sort_array(root, sorted_arr, &idx);

    return sorted_array_to_balanced_tree(sorted_arr, 0, idx - 1);
}
