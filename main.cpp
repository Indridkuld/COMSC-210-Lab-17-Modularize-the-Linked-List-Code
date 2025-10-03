#include <iostream>
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
    int count = 0;
    int entry;
    // create a linked list of size SIZE with random numbers 0-99 (add to front)
    for (int i = 0; i < SIZE; i++) {
        int tmp_val = rand() % 100;
        addFront(head, tmp_val);
    }
    output(head);

    // adding a node to the tail of the list
    float choice;
    cout << "Enter a value to add to the tail of the list: ";
    cin >> choice;
    addTail(head, choice);
    output(head);

    // deleting a node
    cout << "Which node to delete? " << endl;
    output(head);
    cout << "Choice --> ";
    cin >> entry;
    deleteNode(head, entry); 
    output(head);

    // insert a node
    Node *current = head;
    cout << "After which node to insert 10000? " << endl;
    count = 1;
    while (current) {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << "Choice --> ";
    cin >> entry;
    insertNode(head, entry, 10000);
    output(head);

    // deleting the linked list
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
        addFront(head, val);
        return;
    }
    Node *current = head;
    while (current->next)  // traverse to the end of the list
        current = current->next;
    current->next = n;  // link the new node at the end
}
// insertNode function to insert val after the given 1-based position. Returns true on success.
bool insertNode(Node *&head, int entry, float val) {
    Node *current = head;
    Node *prev = head;
    for (int i = 0; i < (entry); i++)
        if (i == 0)
            current = current->next;
        else {
            current = current->next;
            prev = prev->next;
        }
    //at this point, insert a node between prev and current
    Node * newnode = new Node;
    newnode->value = val;
    newnode->next = current;
    prev->next = newnode;
    return true;    
}
// deleteNode function to delete node at 1-based position. Returns true if deleted.
bool deleteNode(Node *&head, int entry) {
    Node *current = head;
    Node *prev = head;
    for (int i = 0; i < (entry-1); i++)
        if (i == 0)
            current = current->next;
        else {
            current = current->next;
            prev = prev->next;
        }
    // at this point, delete current and reroute pointers
    if (current) {  // checks for current to be valid before deleting the node
        prev->next = current->next;
        delete current;
        current = nullptr;
    }
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
    output(head);
}