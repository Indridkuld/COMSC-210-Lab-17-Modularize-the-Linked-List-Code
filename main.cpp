// COMSC-210 | Lab 17: Modularize the Linked List Code | Aidan Woodcock | 2025-10-02
// IDE used: Visual Studio Code

#include <iostream>
using namespace std;

const int SIZE = 7;  

struct Node {
    float value;
    Node *next;
};

// Function prototypes (required by course coding conventions)
void output(Node *);
void addFront(Node *&head, float val);
void addTail(Node *&head, float val);
bool deleteNode(Node *&head, int position); // position is 1-based
bool insertAfter(Node *&head, int position, float val); // insert after given 1-based position
void deleteList(Node *&head);

int main() {
    Node *head = nullptr;
    int count = 0;

    // create a linked list of size SIZE with random numbers 0-99 (add to front)
    for (int i = 0; i < SIZE; i++) {
        int tmp_val = rand() % 100;
        addFront(head, tmp_val);
    }
    output(head);

    // deleting a node
    cout << "Which node to delete? " << endl;
    output(head);
    int entry;
    cout << "Choice --> ";
    cin >> entry;
    if (!deleteNode(head, entry))
        cout << "Failed to delete node at position " << entry << " (out of range).\n";
    output(head);

    // insert a node with value 10000 after a chosen node
    cout << "After which node to insert 10000? " << endl;
    output(head);
    cout << "Choice --> ";
    cin >> entry;
    if (!insertAfter(head, entry, 10000))
        cout << "Failed to insert after position " << entry << " (out of range).\n";
    output(head);

    // deleting the linked list
    deleteList(head);
    output(head);

    return 0;
}

void output(Node * hd) {
    if (!hd) {
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    Node * current = hd;
    while (current) {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << endl;
}

// Add a new node to the front of the list
void addFront(Node *&head, float val) {
    Node *n = new Node;
    n->value = val;
    n->next = head;
    head = n;
}

// Add a new node to the tail of the list
void addTail(Node *&head, float val) {
    Node *n = new Node;
    n->value = val;
    n->next = nullptr;
    if (!head) {
        head = n;
        return;
    }
    Node *cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = n;
}

// Delete node at 1-based position. Returns true if deleted.
bool deleteNode(Node *&head, int position) {
    if (!head || position < 1) return false;
    if (position == 1) {
        Node *tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }
    Node *cur = head;
    Node *prev = nullptr;
    int i = 1;
    while (cur && i < position) {
        prev = cur;
        cur = cur->next;
        ++i;
    }
    if (!cur) return false; // out of range
    prev->next = cur->next;
    delete cur;
    return true;
}

// Insert val after the given 1-based position. Returns true on success.
bool insertAfter(Node *&head, int position, float val) {
    if (position < 0) return false;
    if (position == 0) { // insert at front (after position 0)
        addFront(head, val);
        return true;
    }
    Node *cur = head;
    int i = 1;
    while (cur && i < position) {
        cur = cur->next;
        ++i;
    }
    if (!cur) return false; // out of range
    Node *n = new Node;
    n->value = val;
    n->next = cur->next;
    cur->next = n;
    return true;
}

// Delete the entire linked list and set head to nullptr
void deleteList(Node *&head) {
    Node *cur = head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    head = nullptr;
}