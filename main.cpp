#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

const int SIZE = 7;  

struct Node {
    float value;
    Node *next;
};
// function prototypes 
void output(Node *);
void addFront(Node *&head, float val);
void addTail(Node *&head, float val);
bool deleteNode(Node *&head, int position); 
bool insertNode(Node *&head, int position, float val);
void deleteList(Node *&head);

int main() {
    Node *head = nullptr;
    int entry;
    // seed random number generator for varied runs
    srand(static_cast<unsigned>(time(nullptr)));
    // create a linked list of size SIZE with random numbers 0-99 (add to front)
    for (int i = 0; i < SIZE; i++) {
        int tmp_val = rand() % 100;
        addFront(head, tmp_val);
    }
    output(head);

    // adding a node to the tail of the list
    float choice;
    cout << "Enter a value to add to the tail of the list: "<< endl;
    cout << "Choice --> ";
    while (!(cin >> choice)) {
        cout << "Invalid input; please enter a number. Choice --> ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    addTail(head, choice);
    output(head);

    // deleting a node
    cout << "Which node to delete? " << endl;
    output(head);
    cout << "Choice --> ";
    while (!(cin >> entry)) {
        cout << "Invalid input; please enter an integer position. Choice --> ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (!deleteNode(head, entry))
        cout << "Delete failed: position out of range or list empty.\n";
    output(head);

    // insert a node
    cout << "After which node to insert 10000? " << endl;
    cout << "Choice --> ";
    while (!(cin >> entry)) {
        cout << "Invalid input; please enter an integer position. Choice --> ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (!insertNode(head, entry, 10000))
        cout << "Insert failed: position out of range.\n";
    output(head);

    // deleting the linked list
    cout << "Deleting the entire list...\n";
    deleteList(head);
    output(head);

    return 0;
}
// function definitions
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
    if (!head) {  // if the list is empty, add to front
        head = n;
        return;
    }
    Node *current = head;
    while (current->next)  // traverse to the end of the list
        current = current->next;
    current->next = n;  // link the new node at the end
}
// insertNode function to insert val after the given 1-based position. Returns true on success.
bool insertNode(Node *&head, int position, float val) {
    // Insert AFTER the given 1-based position. position==0 inserts at front.
    if (position < 0) return false;
    if (position == 0) {
        addFront(head, val);
        return true;
    }
    Node *cur = head;
    int i = 1;
    // advance to the node at 'position'
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
// deleteNode function to delete node at 1-based position. Returns true if deleted.
bool deleteNode(Node *&head, int position) {
    if (!head || position < 1) return false;
    // delete head
    if (position == 1) {
        Node *tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }
    Node *cur = head;
    int i = 1;
    // stop at node before the one to delete
    while (cur && i < position - 1) {
        cur = cur->next;
        ++i;
    }
    if (!cur || !cur->next) return false; // out of range
    Node *toDelete = cur->next;
    cur->next = toDelete->next;
    delete toDelete;
    return true;
}
// delete the entire linked list and set head to nullptr
void deleteList(Node *&head) {
    Node *current = head;
    while (current) {
        head = current->next;
        delete current;
        current = head;
    }
    head = nullptr;
}