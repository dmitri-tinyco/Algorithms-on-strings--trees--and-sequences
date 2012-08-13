#include "linked_list.h"
#include <stdio.h> 
#include <stdlib.h> 

Node *ll_create(void *data) {
    Node *n;
    if (!(n = malloc(sizeof(Node)))) return NULL;
    n->data = data;
    n->next = NULL;
    return n;
}

void ll_release(Node *start) {
    Node *current = start;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Node *insert_after(Node *n, void *data) {
    Node *new_node = ll_create(data);
    new_node->next = n->next;
    n->next = new_node;
    return new_node;
}

int ll_for_each(Node *n, int(*func)(void*)) {
    while(n) {
        if(func(n->data)!=0) return -1;
        n=n->next;
    }
    return 0;
}
