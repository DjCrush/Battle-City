#include "Bullet.h"

void AddBullet(LinkedList* linkedlist, void* entity, int type)
{
	Node* curNode = linkedlist->head;
	while(curNode)
	{
		Bullet* bul = curNode->data;
		if (bul->ID == type)
		{
			return;
		}
		curNode = curNode->next;
	}
	
	int x = ((Player*)entity)->x;
	int y = ((Player*)entity)->y;
	DIRECTION dir = ((Player*)entity)->dir;
	if (type != 0)
	{
		x = ((Enemy*)entity)->x;
		y = ((Enemy*)entity)->y;
		dir = ((Enemy*)entity)->dir;
	}

	Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
	if (bullet)
	{
		bullet->ID = type;
		bullet->dir = dir;
		if (dir == DIRECTION_LEFT)
		{
			bullet->x = x - 4;
			bullet->y = y + 24;
		}
		if (dir == DIRECTION_RIGHT)
		{
			bullet->x = x + 60;
			bullet->y = y + 24;
		}
		if (dir == DIRECTION_UP)
		{
			bullet->x = x + 24;
			bullet->y = y - 5;
		}
		if (dir == DIRECTION_DOWN)
		{
			bullet->x = x + 24;
			bullet->y = y + 56;
		}
		LinkedListAddNode(linkedlist, bullet);
	}
}

void UpdateBullets(LinkedList* bulletslist, LinkedList* explosionslist, int level[][26])
{
	Node* curNode = bulletslist->head;
	while (curNode)
	{
		Bullet* bullet = (Bullet*)curNode->data;
		if (bullet->dir == DIRECTION_LEFT)
		{
			bullet->x -= SPEED_BULLET;
		}
		else if (bullet->dir == DIRECTION_RIGHT)
		{
			bullet->x += SPEED_BULLET;
		}
		else if (bullet->dir == DIRECTION_UP)
		{
			bullet->y -= SPEED_BULLET;
		}
		else if (bullet->dir == DIRECTION_DOWN)
		{
			bullet->y += SPEED_BULLET;
		}


		int x = (bullet->x - 64) / SCALE32;
		int y = (bullet->y - 64) / SCALE32;
		if (x > 0 && x < 26 && y > 0 && y < 26 && level[y][x] == 4)
		{
			level[y][x] = 0;
			AddExplosion(explosionslist, bullet->x - 16 - 8, bullet->y - 16 - 8);
			DeleteNodeFromLinkedList(bulletslist, &curNode);
		}
		else if (bullet->x > 880 || bullet->x < 64 || bullet->y > 880 || bullet->y < 64)
		{
			AddExplosion(explosionslist, bullet->x - 16 - 8, bullet->y - 16 - 8);
			DeleteNodeFromLinkedList(bulletslist, &curNode);
		}
		else
		{
			curNode = curNode->next;
		}
	}
}

void DrawBullets(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while (curNode)
	{
		Bullet* bullet = (Bullet*)curNode->data;
		SDL_FRect r1 = { 330, 102, 4, 3 };
		SDL_FRect r2 = { bullet->x, bullet->y, 16, 12 };
		if (bullet->dir == DIRECTION_RIGHT)
		{
			r1.x = 346;
		}
		else if (bullet->dir == DIRECTION_UP)
		{
			r1.x = 323;
			r1.w = 3;
			r1.h = 4;
			r2.w = 12;
			r2.h = 16;
		}
		else if (bullet->dir == DIRECTION_DOWN)
		{
			r1.x = 339;
			r1.w = 3;
			r1.h = 4;
			r2.w = 12;
			r2.h = 16;
		}
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		curNode = curNode->next;
	}
}
