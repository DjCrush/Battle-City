#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	struct Node* prev;
	void* data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	Node* tail;
} LinkedList;

LinkedList* CreateLinkedList();
void LinkedListAddNode(LinkedList* linkedlist, void* data);
void DeleteNodeFromLinkedList(LinkedList* linkedlist, Node** curNode);
void DeleteLinkedList(LinkedList* linkedlist);

#endif // LINKEDLIST_H

