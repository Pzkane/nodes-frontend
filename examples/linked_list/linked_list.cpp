//Source for LL: https://www.geeksforgeeks.org/program-to-implement-singly-linked-list-in-c-using-class/

// C++ program for the above approach
#include <iostream>
#include "nf.hpp"
using namespace std;

nf::NodeFrontEndWrapper NFWrap;
#define WRAPPER NFWrap

// Node class to represent
// a node of the linked list.
class Node : public nf::LinkedListNode<Node, int>  {
public:
	Node() : LinkedListNode<Node, int>(NFWrap.api()) {}
    std::string representation() override {
        return std::to_string(getData());
    }
};

// Linked list class to
// implement a linked list.
class LinkedList {
	Node* head;
    size_t ms = 500;

public:
	// Default constructor
	LinkedList() { head = NULL; }

	// Function to insert a
	// node at the end of the
	// linked list.
	void insertNode(int);

	// Function to print the
	// linked list.
	void printList();

	// Function to delete the
	// node at given position
	void deleteNode(int);
};

// Function to delete the
// node at given position
void LinkedList::deleteNode(int nodeOffset)
{
	Node *temp1 = head, *temp2 = NULL;
	int ListLen = 0;

	if (head == NULL) {
		cout << "List empty." << endl;
		return;
	}

	// Find length of the linked-list.
	while (temp1 != NULL) {
        temp1->highlight();
		temp1 = temp1->getNext();
		ListLen++;
        nf::Utils::delay(ms);
	}

	// Check if the position to be
	// deleted is greater than the length
	// of the linked list.
	if (ListLen < nodeOffset) {
		cout << "Index out of range" << endl;
		return;
	}

	// Declare temp1
	temp1 = head;
    temp1->highlight();
    nf::Utils::delay(ms);

	// Deleting the head.
	if (nodeOffset == 1) {

		// Update head
		head = head->getNext();
		delete temp1;
		return;
	}

	// Traverse the list to
	// find the node to be deleted.
	while (nodeOffset-- > 1) {

		// Update temp2
		temp2 = temp1;

		// Update temp1
		temp1 = temp1->getNext();
        temp1->highlight();
        nf::Utils::delay(ms);
	}

	// Change the next pointer
	// of the previous node.
	temp2->setNext(temp1->getNext());

    temp1->highlight();
    nf::Utils::delay(ms);
	// Delete the node
	delete temp1;
}

// Function to insert a new node.
void LinkedList::insertNode(int data)
{
    static bool pos_set = false;
	// Create the new Node.
	Node* newNode = new Node();
    if (!pos_set) {
        newNode->setPosition(250, 250);
        pos_set = true;
    }
    newNode->setData(data);
    nf::Utils::delay(ms);

	// Assign to head
	if (head == NULL) {
		head = newNode;
        head->highlight();
		return;
	}

	// Traverse till end of list
	Node* temp = head;
	while (temp->getNext() != NULL) {
        temp->highlight();
		// Update temp
		temp = temp->getNext();
        nf::Utils::delay(ms);
	}

	// Insert at the last.
	temp->setNext(newNode);
    temp->highlight();
    nf::Utils::delay(ms);
}

// Function to print the
// nodes of the linked list.
void LinkedList::printList()
{
	Node* temp = head;

	// Check for empty list.
	if (head == NULL) {
		cout << "List empty" << endl;
		return;
	}

	// Traverse the list.
	while (temp != NULL) {
		cout << temp->getData() << " ";
		temp = temp->getNext();
	}
}

// Driver Code
int main()
{
    NFWrap.init("Linked List");
	LinkedList list;

	// Inserting nodes
	list.insertNode(1);
	list.insertNode(2);
	list.insertNode(3);
	list.insertNode(4);

	cout << "Elements of the list are: ";

	// Print the list
	list.printList();
	cout << endl;

	// Delete node at position 2.
	list.deleteNode(2);

	cout << "Elements of the list are: ";
	list.printList();
	cout << endl;
    START_LOOP;
	return 0;
}
