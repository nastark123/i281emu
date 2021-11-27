#include "linkedlist.h"

int ll_contains(LLNode *head, LLNodeData val) {
    // safeguard against NULL heads
    if(head == NULL) return -1;

    LLNode *cur = head;
    int i = 0;
    while(cur != NULL) {
        if(cur->data.i == val.i || cur->data.f == val.f) return i; // the current node is the value we're looking for
        cur = cur->next;
        i++;
    }
    return -1; // the next node doesn't exist, so we are out of nodes to search
}

LLNode *ll_add(LLNode *head, LLNode *node_to_add) {
    if(head == NULL) {
        node_to_add->prev = NULL;
        node_to_add->next = NULL;
        return node_to_add;
    }
    LLNode *cur = head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = node_to_add;
    node_to_add->prev = cur;
}

LLNode *ll_remove(LLNode *head, int n) {
    if(head == NULL || n < 0) return head; // guard against NULL lists or invalid indices
    if(n == 0) {
        LLNode *ret = head->next;
        free(head);
        return ret;
    }


    LLNode *cur = head->next;
    int i = 0;
    while(cur != NULL) {
        if(i == n) {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            break;
        }
        cur = cur->next;
        i++;
    }

    return head;
}