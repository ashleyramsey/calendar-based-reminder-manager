#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

// Node structure for linked list
typedef struct Node {
    char reminder[MAX_STR_LEN];
    struct Node* next;
} Node;

// Linked list functions
Node* create_node(const char* reminder);
void add_node(Node** head, const char* reminder);
void free_all_nodes(Node* head);
void print_list(Node* head);

#endif
