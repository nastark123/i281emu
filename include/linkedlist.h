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

// returns true if the linkedlist beginning at head contains the specified value, false otherwise
bool ll_contains(LLNode *head, LLNodeData val);

// adds node_to_add to the end of the linkedlist
// returns the new head of the linkedlist
LLNode *ll_add(LLNode *head, LLNode *node_to_add);

#endif