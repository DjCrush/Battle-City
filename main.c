#include <SDL3/SDL.h>
#undef main
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "defs.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"
#include "LinkedList.h"


SDL_Renderer* pRenderer = NULL;
SDL_Texture* pTiles = NULL;
SDL_Texture* pFont = NULL;

#define SCALE32 32

static SDL_Texture* CreteTexture(const char* file)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(file);
	if (!loadedSurface)
	{
		fprintf(stderr, "Failed to load %s: %s\n", file, SDL_GetError());
		SDL_DestroyRenderer(pRenderer);
		SDL_Quit();
		return NULL;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
	SDL_SetTextureScaleMode(pTexture, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(loadedSurface);
	return pTexture;
}

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
	int x = 0, y = 0;
	SDL_FRect r1 = { 321, 192, 8, 8 };
	for (int i = 0; i < countEnemies; ++i)
	{
		SDL_FRect r2 = { x * SCALE32 + 928, y * SCALE32 + 96, SCALE32, SCALE32 };
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
		if (++x == 2) { x = 0;  ++y; }
	}
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	SDL_Window* pWindow = NULL;
	SDL_CreateWindowAndRenderer("Battle City", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_TRANSPARENT, &pWindow, &pRenderer);

	//SDL_Texture* pTiles = CreteTexture("tiles.bmp"); if (!pTiles) return 1; 
	//SDL_Texture* pFont = CreteTexture("font_white.bmp"); if (!pFont) return 1; 

	SDL_Surface* loadedSurface = SDL_LoadBMP("tiles.bmp");
	if (!loadedSurface)
	{
		//fprintf(stderr, "Failed to load %s: %s\n", file, SDL_GetError());
		SDL_DestroyRenderer(pRenderer);
		SDL_Quit();
		return 1;
	}
	SDL_Texture* pTiles = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
	SDL_SetTextureScaleMode(pTiles, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(loadedSurface);


	int level1[][26] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 9, 9, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 9, 9, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {4, 4, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 4, 4},
						 {9, 9, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 9, 9},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

	int level2[][26] = { {0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 4, 4, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 4, 4, 9, 9, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 4, 4, 9, 9, 4, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0},
						 {10, 10, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 4, 4, 10, 10, 4, 4, 9, 9},
						 {10, 10, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 4, 4, 10, 10, 4, 4, 9, 9},
						 {10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 9, 9, 0, 0, 10, 10, 0, 0, 0, 0},
						 {10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 9, 9, 0, 0, 10, 10, 0, 0, 0, 0},
						 {0, 0, 4, 4, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 10, 10, 4, 4, 0, 0},
						 {0, 0, 4, 4, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 9, 9, 0, 0, 0, 0, 10, 10, 4, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 9, 9, 10, 10, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 0, 0, 0, 0, 9, 9, 10, 10, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {9, 9, 4, 4, 0, 0, 9, 9, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0},
						 {9, 9, 4, 4, 0, 0, 9, 9, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 9, 9, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 9, 9, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0} };

	int level3[][26] = { {0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 10, 10, 10, 10, 10, 10, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {0, 0, 10, 10, 10, 10, 10, 10, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9},
						 {4, 4, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {4, 4, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						 {10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0},
						 {10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0},
						 {10, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 0, 0, 0, 4, 0, 0},
						 {10, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 4, 0, 0},
						 {10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0},
						 {10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0},
						 {0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 10, 10, 0, 0},
						 {0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 10, 10, 0, 0},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10},
						 {0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10},
						 {4, 4, 4, 0, 0, 4, 4, 4, 4, 0, 0, 4, 4, 4, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10},
						 {4, 4, 4, 0, 0, 4, 4, 4, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10},
						 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 10, 10},
						 {4, 4, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 10, 10, 10, 10, 10, 10, 0, 0},
						 {4, 4, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0},
						 {4, 4, 4, 4, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0},
						 {4, 4, 4, 4, 0, 0, 9, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0},
						 {9, 9, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0},
						 {9, 9, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0} };

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
	LinkedList* enemies = CreateLinkedList();
	LinkedList* bullets = CreateLinkedList();
	LinkedList* explosions = CreateLinkedList();
	int countEnemies = 20;
	SDL_Event event;
	bool bIsRun = true;
	while (bIsRun)
	{
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_EVENT_KEY_DOWN)
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
		//PlayerUpdate(player, level);
		//EnemyUpdate(enemies);
		//BulletsUpdate(bullets, explosions, level);
		//checkCollision(enemies, bullets, explosions);
		//ExplosionsUpdate(explosions);
		//DrawLevel(level, countEnemies);

		if (countEnemies && rand() % 10000 > 10000)
		{
			AddEnemy(enemies, countEnemies + 1);
			--countEnemies;
		}
		//PlayerDraw(player);
		//DrawEnemies(enemies);
		//DrawBullets(bullets);
		//DrawExplosions(explosions);

		SDL_RenderPresent(pRenderer);
		//SDL_Delay(5);

		Node* curNode = enemies->head;
		while (curNode)
		{
			if (rand() % 100 > 98)
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
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	return 0;
}
