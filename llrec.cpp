#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    Node* curr = head;
    llpivot(head->next, smaller, larger, pivot);  // split the rest first

    if (curr->val <= pivot) {
        curr->next = smaller;
        smaller = curr;
    } else {
        curr->next = larger;
        larger = curr;
    }
    head = NULL;
}