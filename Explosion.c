#include "Explosion.h"

extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;

void AddExplosion(LinkedList* linkedlist, int x, int y)
{
	Explosion* explosion = (Explosion*)malloc(sizeof(Explosion));
	if (explosion)
	{
		explosion->x = x;
		explosion->y = y;
		explosion->frame = 0;
		explosion->countframe = 3;
		explosion->count = 0;
		LinkedListAddNode(linkedlist, explosion);
	}
}

void UpdateExplosions(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while (curNode)
	{
		Explosion* explosion = (Explosion*)curNode->data;
		
		if (++explosion->count >= 8)
		{
			++explosion->frame;
			if (explosion->frame == explosion->countframe)
			{
				DeleteNodeFromLinkedList(linkedlist, &curNode);
				break;
			}
			explosion->count = 0;
		}
		curNode = curNode->next;
	}
}

void DrawExplosions(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while (curNode)
	{
		Explosion* explosion = (Explosion*)curNode->data;
		SDL_FRect r1 = { 256 + explosion->frame * 16, 128, 16, 16 };
		SDL_FRect r2 = { explosion->x, explosion->y, 64, 64 };
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		curNode = curNode->next;
	}
}