#include "Player.h"
#include <SDL3/SDL.h>

extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;

void PlayerUpdate(Player* player, int level[][26])
{
	if (player)
	{
		if (player->Star)
		{
			player->Time += 0.1;
			int frames[] = { 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3 };
			player->frame = frames[(int)player->Time];
			if ((int)player->Time == 15)
			{
				player->Time = 0;
				player->Star = false;
			}
		}
		else
		{
			if (player->movingLeft || player->movingRight || player->movingDown || player->movingUp)
			{
				player->frame = ++player->frame % 2;
			}
			if (player->movingLeft)
			{
				if (player->y % SCALE32 < 15)
				{
					player->y = player->y / SCALE32 * SCALE32;
				}
				if (player->y % SCALE32 > SCALE32 - 15)
				{
					player->y = (player->y / SCALE32 + 1) * SCALE32;
				}
				player->dir = DIRECTION_LEFT;
				player->x -= SPEED_PLAYER;
				int x = player->x / SCALE32 - 2;
				int y = player->y / SCALE32 - 2;
				int y1 = (player->y + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x] != 0 || level[y + 1][x] != 0 || level[y1][x] != 0)
				{
					player->x += SPEED_PLAYER;
				}
			}
			else if (player->movingRight)
			{
				if (player->y % SCALE32 < 15)
				{
					player->y = player->y / SCALE32 * SCALE32;
				}
				if (player->y % SCALE32 > SCALE32 - 15)
				{
					player->y = (player->y / SCALE32 + 1) * SCALE32;
				}
				player->dir = DIRECTION_RIGHT;
				player->x += SPEED_PLAYER;
				int y = player->y / SCALE32 - 2;
				int x1 = (player->x + SCALE64 - 1) / SCALE32 - 2;
				int y1 = (player->y + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x1] != 0 || level[y + 1][x1] != 0 || level[y1][x1] != 0)
				{
					player->x -= SPEED_PLAYER;
				}
			}
			else if (player->movingDown)
			{
				if (player->x % SCALE32 < 15)
				{
					player->x = player->x / SCALE32 * SCALE32;
				}
				if (player->x % SCALE32 > SCALE32 - 15)
				{
					player->x = (player->x / SCALE32 + 1) * SCALE32;
				}
				player->dir = DIRECTION_DOWN;
				player->y += SPEED_PLAYER;
				int x = player->x / SCALE32 - 2;
				int x1 = (player->x + SCALE64 - 1) / SCALE32 - 2;
				int y = (player->y + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x] != 0 || level[y][x + 1] != 0 || level[y][x1] != 0)
				{
					player->y -= SPEED_PLAYER;
				}
			}
			else if (player->movingUp)
			{
				if (player->x % SCALE32 < 15)
				{
					player->x = player->x / SCALE32 * SCALE32;
				}
				if (player->x % SCALE32 > SCALE32 - 15)
				{
					player->x = (player->x / SCALE32 + 1) * SCALE32;
				}
				player->dir = DIRECTION_UP;
				player->y -= SPEED_PLAYER;
				int x = player->x / SCALE32 - 2;
				int y = player->y / SCALE32 - 2;
				int x1 = (player->x + SCALE64 - 1) / SCALE32 - 2;
				if (level[y][x] != 0 || level[y][x + 1] != 0 || level[y][x1] != 0)
				{
					player->y += SPEED_PLAYER;
				}
			}
		}
	}
}

void PlayerDraw(Player* player)
{
	if (player->Star)
	{
		SDL_FRect r1 = { player->frame * 16 + 256, 96, 16, 16 };
		SDL_FRect r2 = { player->x, player->y, 64, 64 };
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
	}
	else if (player)
	{
		SDL_FRect r1 = { player->frame * 16 + player->dir * SCALE32, 0, 16, 16 };
		SDL_FRect r2 = { player->x, player->y, 64, 64 };
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
	}
}