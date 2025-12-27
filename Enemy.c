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
		enemy->frame = 0;
		enemy->ID = ID;
		LinkedListAddNode(linkedlist, enemy);
	}
}

void EnemyUpdate(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while(curNode)
	{
		Enemy* enemy = (Enemy*)curNode->data;
		enemy->frame = (enemy->frame + 1) % 2;
		if (enemy->dir == DIRECTION_LEFT)
		{
			enemy->x -= STEP_ENEMY;
		}
		else if (enemy->dir == DIRECTION_RIGHT)
		{
			enemy->x += STEP_ENEMY;
		}
		else if (enemy->dir == DIRECTION_UP)
		{
			enemy->y -= STEP_ENEMY;
		}
		else if (enemy->dir == DIRECTION_DOWN)
		{
			enemy->y += STEP_ENEMY;
		}
		if (enemy->x < 0 || enemy->x > SCREEN_WIDTH - 64 ||
			enemy->y < 0 || enemy->y > SCREEN_HEIGHT - 64 || rand() % 100 > 97)
		{
			if (enemy->dir == DIRECTION_LEFT)
			{
				enemy->x += STEP_ENEMY;
			}
			else if (enemy->dir == DIRECTION_RIGHT)
			{
				enemy->x -= STEP_ENEMY;
			}
			else if (enemy->dir == DIRECTION_UP)
			{
				enemy->y += STEP_ENEMY;
			}
			else if (enemy->dir == DIRECTION_DOWN)
			{
				enemy->y -= STEP_ENEMY;
			}
			DIRECTION dir = enemy->dir;
			while (enemy->dir == dir)
			{
				enemy->dir = rand() % 4;
			}
		}
		curNode = curNode->next;
	}
}

void DrawEnemies(LinkedList* linkedlist)
{
	Node* curNode = linkedlist->head;
	while(curNode)
	{
		Enemy* enemy = (Enemy*)curNode->data;
		SDL_FRect r1 = { enemy->dir * 32 + enemy->frame * 16, 240, 16, 16 };
		SDL_FRect r2 = { enemy->x, enemy->y, 64, 64 };
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		curNode = curNode->next;
	}
}

void checkCollision(LinkedList* enemies, LinkedList* bullets, LinkedList* explosionslist)
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
				//AddExplosion(explosionslist, bullet->x - 16 - 8, bullet->y - 16 - 8);
				//DeleteNodeFromLinkedList(bullets, &curNodeBullet);
				//DeleteNodeFromLinkedList(enemies, &curNodeEnemy);
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
