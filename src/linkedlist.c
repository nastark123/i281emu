#include "linkedlist.h"

bool ll_contains(LLNode *head, LLNodeData val) {
    // TODO make this better
    if(head->data.i == val.i || head->data.f == val.f) return true; // the current node is the value we're looking for
    if(head->next != NULL) return ll_contains(head->next, val); // check the next node
    return false; // the next node doesn't exist, so we are out of nodes to search
}

void ll_add(LLNode *head, LLNode *node_to_add) {
    LLNode *cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = node_to_add;
    node_to_add->prev = cur;
}