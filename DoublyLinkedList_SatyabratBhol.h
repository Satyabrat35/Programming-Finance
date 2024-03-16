//
// Created by Satyabrat Bhol on 10/12/23.
//

#ifndef PROJECT_DOUBLELINKEDLIST_H
#define PROJECT_DOUBLELINKEDLIST_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class StockAccount;
class DoublyLinkedList
{
    // friend class StockAccount;
    // friend class SortStratergy;
    friend class BubbleSort;
    friend class SelectionSort;
public:
    DoublyLinkedList(); // I will call it doublyList
    ~DoublyLinkedList();

    Node* getHead() const; //get the empty head of doublyList
    Node* getTail() const; //get the empty tail of doublyList

    int getSize() const; //get the size of doublyList (do not include the head and tail)

    void insertNode(Node *node); //insert a node before the tail
    void deleteNode(string stockName); //delete a node with a certain name
    Node* findNode(string stockName); //find a node with a certain name

    Node* findNodeByPosition(int position) const; //find the node at position(begin with 1, do not include the head and tail)
    void swapNode(int pos1, int pos2); // swap the node at pos1 and pos2
    void swapAdjacentNodes(Node *n1, Node *n2);
    void swapNonAdjacentNodes(Node *n1, Node *n2);

    void printList(); //print the content of the list for debugging

private:
    Node* head; // the empty head of doublyList
    Node* tail; // the empty tail of doublyList
    int nodeNum; // the number of nodes in doublyList  (do not include the head and tail)
};

#endif //PROJECT_DOUBLELINKEDLIST_H
