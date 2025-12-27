#include "LinkedList.h"

LinkedList* CreateLinkedList()
{
	LinkedList* linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
	if (linkedlist)
	{
		linkedlist->head = NULL;
		linkedlist->tail = NULL;
	}
	return linkedlist;
}

static Node* CreateNode(void* data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node)
	{
		node->data = data;
		node->next = NULL;
	}
	return node;
}

void LinkedListAddNode(LinkedList* linkedlist, void* data)
{
	Node* node = CreateNode(data);
	if (node)
	{
		if (linkedlist->tail)
		{
			node->prev = linkedlist->tail;
			linkedlist->tail->next = node;
			linkedlist->tail = node;
		}
		else
		{
			linkedlist->head = node;
			linkedlist->tail = node;
			node->prev = NULL;
		}
	}
}

void DeleteNodeFromLinkedList(LinkedList* linkedlist, Node** curNode)
{
	if (linkedlist->head == *curNode && linkedlist->head == linkedlist->tail)
	{
		linkedlist->head = NULL;
		linkedlist->tail = NULL;
	}
	else if (linkedlist->head == *curNode && linkedlist->head != linkedlist->tail)
	{
		linkedlist->head = (*curNode)->next;
	}
	else if (linkedlist->tail == *curNode)
	{
		linkedlist->tail = (*curNode)->prev;
		linkedlist->tail->next = NULL;
	}
	else
	{
		(*curNode)->prev->next = (*curNode)->next;
		(*curNode)->next->prev = (*curNode)->prev;
	}
	if ((*curNode)->data) free((*curNode)->data);
	free(*curNode);
	*curNode = NULL;
}

void DeleteLinkedList(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while (curNode)
	{
		free(curNode->data);
		Node* t = curNode;
		curNode = curNode->next;
		free(t);
	}
	free(linkedlist);
	linkedlist = NULL;
}
