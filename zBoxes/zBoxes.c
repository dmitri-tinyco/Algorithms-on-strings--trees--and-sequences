#include <stdio.h>
#include "linked_list.h"
#include "element.h"

Node *assign_z_value(Node *n, Node *head, int previous_left, int previous_right);
Node *get_nth_node(Node *head, int position);

int main() {
    char *text = "aabaabcaxaabaabcy";
//    char *text = "ababcabababxab";
//    char *text = "aabaabaabcaabaabaabcabaabxaab";
//    char *text = "aabaabaabcaabaabaabcabaabxaaba";
//    char *text = "aabcaabxaaz";
    char *p = "aba";
    printf("searching for \"%s\" in \"%s\"\n", p, text);

    Node *head;
    Node *tail;
    ELEMENT *el;

    head = ll_create(el_create(0, text[0], 0, 0, 0));
    tail = head;
    int i;
    for (i=1; text[i] != '\0'; i++)
        tail = insert_after(tail, el_create(i, text[i], 0, 0, 0));
    
//    ll_for_each(head, &print_element);

    Node *next = head->next;
    int previous_left = 0;
    int previous_right = 0;
    Node *assigned;
    while(next) {
        assigned = assign_z_value(next, head, previous_left, previous_right);
        previous_left = ((ELEMENT *) assigned->data)->left;
        previous_right = ((ELEMENT *) assigned->data)->right;
        next = next->next;
    }

    ll_for_each(head, &print_element);

    ll_for_each(head, &el_release);
    ll_release(head);

    return 0;
}

Node *assign_z_value(Node *n, Node *head, int previous_left, int previous_right) {
    Node *current = n;
    Node *prefix = head;
    ELEMENT *el = ((ELEMENT *)n->data);
    int zValue = 0;
    el->right = previous_right;
    el->left = previous_left;
    if(el->index >= previous_right) {
        while(current && ((ELEMENT *)current->data)->letter == ((ELEMENT *)prefix->data)->letter) {
            zValue = ++zValue;
            prefix = prefix->next;
            current = current->next;
        }
        if (zValue && el->index + zValue >= previous_right) {
            el->right = el->index + zValue - 1;
            el->left = el->index;
        }
        el->zValue = zValue;
    }
    else {
        int beta = previous_right - el->index;
//        printf ("index: %i, beta: %i\n", el->index, beta);
        Node *k_prime;
        k_prime = get_nth_node(head, el->index - previous_left);
        if ( ((ELEMENT *)k_prime->data)->zValue <= beta)
            el->zValue = ((ELEMENT *)k_prime->data)->zValue;
        else {
            zValue = beta;
            Node *r_Node = get_nth_node(current, beta);
            Node *r_prime = get_nth_node(head, beta);
            while (r_Node != NULL && ((ELEMENT *)r_Node->data)->letter == ((ELEMENT *)r_prime->data)->letter) {
                zValue = ++zValue;
                r_Node = r_Node->next;
                r_prime = r_prime->next;
            }
            el->right = ((ELEMENT *)r_Node->data)->index;
            el->left = el->index;
            el->zValue = zValue;
        }
    }
    return n;
}

Node *get_nth_node(Node *head, int position) {
    int i=0;
    Node *next = head;
    while(next->next && i<position){
        next = next->next;
        i++;
    }
//    printf ("k_prime i: %i\n", i);
//    printf ("k_prime position: %i\n", position);
    return next;
}
