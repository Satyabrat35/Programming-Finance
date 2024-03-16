//
// Created by Satyabrat Bhol on 10/12/23.
//

#include "DoublyLinkedList_SatyabratBhol.h"
#include<string>
using namespace std;

DoublyLinkedList::DoublyLinkedList()
{
    nodeNum = 0;
    // create empty head and empty tail
    head = new Node("", 0);
    tail = new Node("", 0);
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* currentPtr = head;
    while (currentPtr) {
        Node* tempPtr = currentPtr;
        currentPtr = currentPtr->next;
        delete tempPtr;
        tempPtr = NULL;
    }
}

Node * DoublyLinkedList::getHead() const
{
    return head;
}

Node * DoublyLinkedList::getTail() const
{
    return tail;
}

int DoublyLinkedList::getSize() const
{
    return nodeNum;
}

void DoublyLinkedList::insertNode(Node * node)
{
    //insert it before the tail and add the number of nodes
    node->next = tail;
    node->prev = tail->prev;
    tail->prev->next = node;
    tail->prev = node;
    nodeNum++;
}

void DoublyLinkedList::deleteNode(string stockName)
{
    Node * node = findNode(stockName);
    if (node == nullptr) { // if do not find the stock
        cout << "Error: Stock not found." << endl;
    }
    else { // delete it
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete(node);
        nodeNum--;
    }
}

Node * DoublyLinkedList::findNode(string stockName)
{
    Node * currentPtr = head->next;
    while (currentPtr != tail) { // go throungh the doublyList to find if there is a stock having this name
        if (currentPtr->stockName == stockName) {
            return currentPtr;
        }
        currentPtr = currentPtr->next;
    }
    return nullptr;
}

Node * DoublyLinkedList::findNodeByPosition(int position) const
{
    if (position > getSize()) { // position is larger than the size of doublyList
        cout << "Error: invalid position." << endl;
        return nullptr;
    }
    else {
        int cnt = 1; // count the position now
        Node* tempPtr = head->next;
        while ((cnt++) != position) {
            tempPtr = tempPtr->next;
        }
        return tempPtr;
    }
}

void DoublyLinkedList::swapNode(int pos1, int pos2) 
{
    Node* n1 = findNodeByPosition(pos1); //find node1 and node2
    Node* n2 = findNodeByPosition(pos2);
    if (n1 == nullptr || n2 == nullptr) {
        cout << "Error: invalid swap." << endl; //both of the node must exist
        return;
    }
    if (n1->next == n2 ) {
        // Nodes are adjacent
        swapAdjacentNodes(n1, n2);
    } else {
        // Nodes are not adjacent
        swapNonAdjacentNodes(n1, n2);
    }

}

void DoublyLinkedList::swapAdjacentNodes(Node* n1, Node* n2) 
{
    n1->next = n2->next;
	n2->prev = n1->prev;
	n1->prev->next = n2;
	n1->prev = n2;
	n2->next->prev = n1;
	n2->next = n1;
}

void DoublyLinkedList::swapNonAdjacentNodes(Node* n1, Node* n2) 
{
    Node* tempPtr = new Node("", 0);
	tempPtr->next = n1->next;
	tempPtr->prev = n1->prev;
	n1->prev->next = n2;
	n1->next->prev = n2;
	n1->prev = n2->prev;
	n1->next = n2->next;
	n2->prev->next = n1;
	n2->next->prev = n1;
	n2->prev = tempPtr->prev;
	n2->next = tempPtr->next;
    
	delete(tempPtr);
}

void DoublyLinkedList::printList() //print for debugging
{
    Node* currentPtr = head->next;
    while (currentPtr != tail) {
        cout << currentPtr->stockName << " ," << currentPtr->stockNum << endl;
        currentPtr = currentPtr->next;
    }
}
