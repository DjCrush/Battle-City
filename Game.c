#include "Game.h"
#include <SDL3/SDL.h>
#include "Levels.h"
#include "defs.h"
#include "Player.h"
#include "Enemy.h"
#include "structs.h"
#include "Explosion.h"
#include "LinkedList.h"



void DrawLevel(int level[][26], int countEnemies)
{
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			SDL_FRect r1 = { 0 };
			SDL_FRect r2 = { j * SCALE32 + 64, i * SCALE32 + 64, SCALE32, SCALE32 };
			switch (level[i][j])
			{
			case 0: r1 = (SDL_FRect){ 256, 88, 8, 8 }; break;
			case 4: r1 = (SDL_FRect){ 256, 64, 8, 8 }; break;
			case 9: r1 = (SDL_FRect){ 256, 72, 8, 8 }; break;
			case 10: r1 = (SDL_FRect){ 272, 32, 8, 8 }; break;
			}
			SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		}
	}
}


void Game()
{
	int level[26][26] = { 0 };
	memcpy(level, level1, sizeof(level));
	Player* player = (Player*)calloc(1, sizeof(Player));
	if (!player)
	{
		return 1;
	}
	player->x = 8 * SCALE32 + 64;
	player->y = 24 * SCALE32 + 64;
	player->dir = DIRECTION_UP;
	player->Time = 0.f;
	player->Star = true;
	LinkedList* enemies = CreateLinkedList();
	LinkedList* bullets = CreateLinkedList();
	LinkedList* explosions = CreateLinkedList();
	srand(time(NULL));
	int countEnemies = 20;
	SDL_Event event;
	bool bIsRun = true;
	while (bIsRun)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_KEY_DOWN)
			{
				switch (event.key.scancode)
				{
				case SDL_SCANCODE_RIGHT: player->movingRight = true; break;
				case SDL_SCANCODE_LEFT: player->movingLeft = true; break;
				case SDL_SCANCODE_UP: player->movingUp = true; break;
				case SDL_SCANCODE_DOWN: player->movingDown = true; break;
				case SDL_SCANCODE_SPACE: AddBullet(bullets, player, 0); break;
				}
			}
			else if (event.type == SDL_EVENT_KEY_UP)
			{
				switch (event.key.scancode)
				{
				case SDL_SCANCODE_RIGHT: player->movingRight = false; break;
				case SDL_SCANCODE_LEFT:  player->movingLeft = false; break;
				case SDL_SCANCODE_UP: player->movingUp = false; break;
				case SDL_SCANCODE_DOWN: player->movingDown = false; break;
				}
			}
			if (event.type == SDL_EVENT_QUIT)
			{
				bIsRun = false;
			}
		}
		SDL_SetRenderDrawColor(pRenderer, 116, 116, 116, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(pRenderer);
		PlayerUpdate(player, level);
		UpdateEnemies(enemies, level);
		UpdateBullets(bullets, explosions, level);
		CheckCollisions(enemies, bullets, explosions);
		UpdateExplosions(explosions);
		DrawLevel(level, countEnemies);

		if (countEnemies && rand() > RAND_MAX - 50)
		{
			AddEnemy(enemies, countEnemies + 1);
			--countEnemies;
		}
		PlayerDraw(player);
		DrawEnemies(enemies);
		DrawBullets(bullets);
		DrawExplosions(explosions);

		SDL_RenderPresent(pRenderer);
		SDL_Delay(5);

		Node* curNode = enemies->head;
		while (curNode)
		{
			if (rand() > RAND_MAX - 30)
			{
				Enemy* enemy = (Enemy*)curNode->data;
				AddBullet(bullets, enemy, enemy->ID);
			}
			curNode = curNode->next;
		}
	}
	DeleteLinkedList(bullets);
	DeleteLinkedList(enemies);
	free(player);
}