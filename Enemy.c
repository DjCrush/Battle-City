#include "Enemy.h"

void AddEnemy(LinkedList* linkedlist, int ID)
{
	Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
	if (enemy)
	{
		int s = rand() % 100;
		if (s > 67)
		{
			enemy->x = 64;
		}
		else if (s > 33)
		{
			enemy->x = 12 * 32 + 64;
		}
		else
		{
			enemy->x = 24 * 32 + 64;
		}
		enemy->y = 64;
		enemy->dir = DIRECTION_DOWN;
		enemy->Star = true;
		enemy->ID = ID;
		enemy->Time = 0.f;
		LinkedListAddNode(linkedlist, enemy);
	}
}

void UpdateEnemies(LinkedList* linkedlist, int level[][26])
{
	Node* curNode = linkedlist->head;
	while (curNode)
	{
		Enemy* enemy = (Enemy*)curNode->data;
		if (enemy->Star)
		{
			enemy->Time += 0.125;
			int frames[] = { 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3 };
			enemy->frame = frames[(int)enemy->Time];
			if ((int)enemy->Time == 15)
			{
				enemy->Time = 0;
				enemy->Star = false;
			}
		}
		else
		{
			enemy->frame = (enemy->frame + 1) % 2;
			if (enemy->dir == DIRECTION_LEFT)
			{
				if (enemy->y % SCALE32 < 15)
				{
					enemy->y = enemy->y / SCALE32 * SCALE32;
				}
				if (enemy->y % SCALE32 > SCALE32 - 15)
				{
					enemy->y = (enemy->y / SCALE32 + 1) * SCALE32;
				}
				enemy->dir = DIRECTION_LEFT;
				enemy->x -= SPEED_ENEMY;
				int x = enemy->x / SCALE32 - 2;
				int y = enemy->y / SCALE32 - 2;
				int y1 = (enemy->y + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x] != 0 || level[y + 1][x] != 0 || level[y1][x] != 0)
				{
					enemy->x += SPEED_ENEMY;
				}
			}
			else if (enemy->dir == DIRECTION_RIGHT)
			{
				if (enemy->y % SCALE32 < 15)
				{
					enemy->y = enemy->y / SCALE32 * SCALE32;
				}
				if (enemy->y % SCALE32 > SCALE32 - 15)
				{
					enemy->y = (enemy->y / SCALE32 + 1) * SCALE32;
				}
				enemy->dir = DIRECTION_RIGHT;
				enemy->x += SPEED_ENEMY;
				int y = enemy->y / SCALE32 - 2;
				int x1 = (enemy->x + SCALE64 - 1) / SCALE32 - 2;
				int y1 = (enemy->y + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x1] != 0 || level[y + 1][x1] != 0 || level[y1][x1] != 0)
				{
					enemy->x -= SPEED_ENEMY;
				}
			}
			else if (enemy->dir == DIRECTION_UP)
			{
				if (enemy->x % SCALE32 < 15)
				{
					enemy->x = enemy->x / SCALE32 * SCALE32;
				}
				if (enemy->x % SCALE32 > SCALE32 - 15)
				{
					enemy->x = (enemy->x / SCALE32 + 1) * SCALE32;
				}
				enemy->dir = DIRECTION_UP;
				enemy->y -= SPEED_ENEMY;
				int x = enemy->x / SCALE32 - 2;
				int y = enemy->y / SCALE32 - 2;
				int x1 = (enemy->x + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x] != 0 || level[y][x + 1] != 0 || level[y][x1] != 0)
				{
					enemy->y += SPEED_ENEMY;
				}
			}
			else if (enemy->dir == DIRECTION_DOWN)
			{
				if (enemy->x % SCALE32 < 15)
				{
					enemy->x = enemy->x / SCALE32 * SCALE32;
				}
				if (enemy->x % SCALE32 > SCALE32 - 15)
				{
					enemy->x = (enemy->x / SCALE32 + 1) * SCALE32;
				}
				enemy->dir = DIRECTION_DOWN;
				enemy->y += SPEED_ENEMY;
				int x = enemy->x / SCALE32 - 2;
				int x1 = (enemy->x + SCALE64 - 1) / SCALE32 - 2;
				int y = (enemy->y + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x] != 0 || level[y][x + 1] != 0 || level[y][x1] != 0)
				{
					enemy->y -= SPEED_ENEMY;
				}
			}
			if (rand() > RAND_MAX - 10)
			{
				DIRECTION dir = enemy->dir;
				while (enemy->dir == dir)
				{
					enemy->dir = rand() % 4;
				}
			}
		}
		curNode = curNode->next;
	}
}

void DrawEnemies(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while (curNode)
	{
		Enemy* enemy = (Enemy*)curNode->data;
		if (enemy->Star)
		{
			SDL_FRect r1 = { enemy->frame * 16 + 256, 96, 16, 16 };
			SDL_FRect r2 = { enemy->x, enemy->y, 64, 64 };
			SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		}
		else
		{
			SDL_FRect r1 = { enemy->dir * 32 + enemy->frame * 16 + 128, 0, 16, 16 };
			SDL_FRect r2 = { enemy->x, enemy->y, 64, 64 };
			SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		}
		curNode = curNode->next;
	}
}

void CheckCollisions(LinkedList* enemies, LinkedList* bullets, LinkedList* explosionslist)
{
	Node* curNodeEnemy = enemies->head;
	bool flag = true;
	while(curNodeEnemy && flag)
	{
		Enemy* enemy = (Enemy*)curNodeEnemy->data;
		Node* curNodeBullet = bullets->head;
		while(curNodeBullet && flag)
		{
			Bullet* bullet = (Bullet*)curNodeBullet->data;
			if (bullet->x > enemy->x && bullet->x < enemy->x + 64 && bullet->y > enemy->y && bullet->y < enemy->y + 64)
			{
				AddExplosion(explosionslist, bullet->x - 16 - 8, bullet->y - 16 - 8);
				DeleteNodeFromLinkedList(bullets, &curNodeBullet);
				DeleteNodeFromLinkedList(enemies, &curNodeEnemy);
				flag = false;
			}
			else
			{
				curNodeBullet = curNodeBullet->next;
			}
		}
		if (flag)
		{
			curNodeEnemy = curNodeEnemy->next;
		}
	}
}
