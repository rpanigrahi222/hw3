#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------
struct isOdd {
  bool operator()(int v) {
    return v % 2 != 0;
  }
}

struct greaterThan {
  int t;
  greaterThan(int threshold) : t(threshold) {}
  bool operator()(int v) {
    return v > t;
  }
}

struct dontRemove {
  bool operator()(int) {
    return false;
  }
}

struct removeAll {
  bool operator()(int) {
    return true;
  }
}

void testLLPivot(const char* filename, int pivot) {
  Node* head = readList(filename);
  Node* smaller = (Node*)0xBAD;
  Node* larger = (Node*)0xBAD;

  llpivot(head, smaller, larger, pivot);

  cout << "llpivot (pivot = " << pivot << ")" << endl;
  cout << "  head (should not be empty): "; print(head);
  cout << "  smaller: "; print(smaller);
  cout << "  larger: "; print(larger);

  dealloc(smaller);
  dealloc(larger);
}

template <typename Comp>
void testFilter(const char* filename, Comp pred, const char* label)
{
    Node* head = readList(filename);
    head = llfilter(head, pred);
    cout << "llfilter (" << label << "): "; print(head);
    dealloc(head);
}



int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);
    dealloc(head);

    // Test out your linked list code
    cout << endl;
    testLLPivot(argv[1], 5);
    testLLPivot(argv[1], -10000000);
    testLLPivot(argv[1], 10000000);

    cout << endl;
    testFilter(argv[1], isOdd(), "remove odds");
    testFilter(argv[1], greaterThan(5), "remove all > 5");
    testFilter(argv[1], dontRemove(), "don't remove anything");
    testFilter(argv[1], removeAll(), "remove everything");
    



    
    return 0;

}
