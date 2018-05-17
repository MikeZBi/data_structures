// linkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//Used inside Class queue for the linked list based queue implementation
struct node {
	int data;
	node* next;
	node* previous;
};

class queue {
public: 
	queue();
	void pushBack(int data);
	int pop(); //Last in first out
	int FIFO(); //First in first out
	int getSize();
	bool isEmpty();
	void printQueue();
private:
	node* head;
	node* currentNode;
	int size;
};


//Functions to write, create a list from an array, insert into, findItem, delete item, print item
node* createListFromArray(int* array1, int size);
void printList(node* head);
void insertIntoList(node* head, int item);
void deleteFromList(node* head, int item);

int main()
{
	//Creates a pointer of class type queue called myQueue. Points to an unnamed memory location
	queue* myQueue = new queue;
	//Pushes the numbers 5,10,15 to the queue. 
	myQueue->pushBack(5);
	myQueue->pushBack(10);
	myQueue->pushBack(15);

	//FIFO is member function that implements first in first out queue. Change the function to pop(), for the Last in first out queue
	cout << myQueue->FIFO() << endl;
	myQueue->printQueue();
	cout << myQueue->FIFO() << endl;
	cout << myQueue->FIFO() << endl;

	//Verify's the isEmpty() function works correctly
	if (myQueue->isEmpty())
	{
		cout << "queue is empty" << endl;
	}
	system("pause");
    return 0;
}

//Initialize values, set size =0 at first, we set everything of the head to NULL
queue::queue() {
	size = 0;
	head = new node;
	head->next = NULL;
	head->data = NULL;
	head->previous = NULL;
}

//Because we set all things in head to NULL, if head->next is null, then we know there are no items in the queue
//and thus our if statement makes it so that the head is a special pointer for the list and points to the first item
//in the list, but head is not the actual first item.
void queue::pushBack(int data) {
	node* createdNode = new node;
	createdNode->data = data;

	if (head->next == NULL) {
		head->next = createdNode;
		currentNode = createdNode;
		currentNode->previous = head;
		currentNode->next = NULL;
		size++;
	}
	else {
		currentNode->next = createdNode;
		createdNode->next = NULL;
		createdNode->previous = currentNode;
		currentNode = createdNode;		
		size++;
	}
}
//Pop the last item LIFO, from the queue
int queue::pop() {
	node* currentNodeCopy = currentNode;
	int popValue = currentNodeCopy->data;

	//point currentNode to the previous node
	currentNode = currentNodeCopy->previous;
	//use the copy to set those pointers to null and delete the pointer to the node
	currentNodeCopy->previous->next = NULL;
	currentNodeCopy->previous = NULL;
	delete currentNodeCopy;
	size--;
	return popValue;
}

//make the head node next equal to the second node, make the second node's previous value to the head node
//set all values in first node to NULL, delete the pointer to the node. Else if there is only one node.
int queue::FIFO() {
	node* headCopy = head; 
	node* firstNodeCopy = head->next;
	int data = headCopy->next->data;
	
	if (headCopy->next->next != NULL) {
		headCopy->next = firstNodeCopy->next;
		firstNodeCopy->next->previous = headCopy;
		firstNodeCopy->next = NULL;
		firstNodeCopy->previous = NULL;
		delete firstNodeCopy;
		size--;
	}
	else {
		headCopy->next = NULL;
		firstNodeCopy->previous = NULL;
		delete firstNodeCopy;
		size--;
	}	
	return data;
}

int queue::getSize() {
	return size;
}

bool queue::isEmpty() {
	if (size == 0) {
		return true;
	}
	else
		return false;
}
//Since head is a special node, we go to head->next, which gives us the memory address of the first item in the list
//Once we get to the last item, that last item->next is set to null, so the while loop terminates
void queue::printQueue() {
	node* headCopy = head;
	headCopy = headCopy->next;
	while (headCopy != NULL) {
		cout << headCopy->data << endl;
		headCopy = headCopy->next;
	}
}














//Linked list insert, delete, print list, create list from an input(array)
void insertIntoList(node* head, int item) {
	node* headCopy = head;
	headCopy = headCopy->next;

	while (head != NULL) {
		if (headCopy->data >= item) {
			node* createdNode = new node;
			createdNode->data = item;
			headCopy->previous->next = createdNode;
			createdNode->previous = headCopy->previous;
			createdNode->next = headCopy;
			headCopy->previous = createdNode;
			return;
		}
		headCopy = headCopy->next;
	}
}


void deleteFromList(node* head, int item) {
	node* headCopy = head;
	headCopy = headCopy->next;
	
	while (headCopy != NULL) {
		if (headCopy->data == item) {
			headCopy->previous->next = headCopy->next;
			headCopy->next->previous = headCopy->previous;

			headCopy->next = NULL;
			headCopy->previous = NULL;
			delete headCopy;
			return;
		}
		headCopy = headCopy->next;
	}
}

void printList(node* head) {
	node* headCopy = head;
	headCopy = headCopy->next;
	while (headCopy != NULL) {
		cout << "node : " << headCopy->data << endl;
		headCopy = headCopy->next;
	}
}


node* createListFromArray(int* array1, int size) {
	node* head, *currentNode, *createdNode;
	head = NULL;
	currentNode = NULL;
	int i = 0;

	while (i < size) {
		createdNode = new node;
		if (head == NULL) {
			createdNode->next = NULL;
			createdNode->previous = NULL;
			head = createdNode;
			currentNode = createdNode;
		}
		else {
			createdNode->data = array1[i];
			createdNode->next = NULL;
			createdNode->previous = currentNode;
			currentNode->next = createdNode;
			currentNode = createdNode;
			i++;
		}
	}
	return head; 
}



