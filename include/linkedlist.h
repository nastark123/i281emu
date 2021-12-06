#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef union {
    int i;
    float f;
} LLNodeData;

typedef struct LLNode {
    struct LLNode *prev;
    struct LLNode *next;
    LLNodeData data;
} LLNode;

// returns the index of the first appearance of val, or -1 if it is not found
int ll_contains(LLNode *head, LLNodeData val);

// adds node_to_add to the end of the linkedlist
// returns the new head of the linkedlist
LLNode *ll_add(LLNode *head, LLNode *node_to_add);

// removes the node at the specified index
// returns the new head of the linkedlist
LLNode *ll_remove(LLNode *head, int n);

#endif