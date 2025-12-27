#include "Player.h"


void PlayerUpdate(Player* player, int level[][26])
{
	if (player)
	{
		Print(0, 0, "HELLO WORLD", 0);
		int x = player->x - 64;
		int y = player->y - 64;
		if (player->movingLeft || player->movingRight || player->movingDown || player->movingUp)
		{
			player->frame = ++player->frame % 2;
		}
		if (player->movingLeft)
		{
			player->dir = DIRECTION_LEFT;
			if (level[y / 32][(x - 1) / SCALE32] == 0 && level[y / SCALE32 + 1][(x - 1) / SCALE32] == 0 ||
				level[y / 32][(x - 1) / SCALE32] == 10 && level[y / SCALE32 + 1][(x - 1) / SCALE32] == 10)

			{
				player->x -= SPEED_PLAYER;
			}
		}
		else if (player->movingRight)
		{
			player->dir = DIRECTION_RIGHT;
			if (level[y / SCALE32][(x + 1) / SCALE32 + 2] == 0 && level[y / SCALE32 + 1][(x + 1) / SCALE32 + 2] == 0 ||
				level[y / SCALE32][(x + 1) / SCALE32 + 2] == 10 && level[y / SCALE32 + 1][(x + 1) / SCALE32 + 2] == 10)
			{
				player->x += SPEED_PLAYER;
			}
		}
		else if (player->movingDown)
		{
			player->dir = DIRECTION_DOWN;
			if (level[(y + 1) / SCALE32 + 1][x / SCALE32] == 0 && level[(y + 1) / SCALE32 + 1][x / SCALE32 + 1] == 0 ||
				level[(y + 1) / SCALE32 + 1][x / SCALE32] == 10 && level[(y + 1) / SCALE32 + 1][x / SCALE32 + 1] == 10)
			{
				player->y += SPEED_PLAYER;
			}
		}
		else if (player->movingUp)
		{
			player->dir = DIRECTION_UP;
			if (level[(y - 1) / SCALE32][x / SCALE32] == 0 && level[(y - 1) / SCALE32][x / SCALE32 + 1] == 0 ||
				level[(y - 1) / SCALE32][x / SCALE32] == 10 && level[(y - 1) / SCALE32][x / SCALE32 + 1] == 10)
			{
				player->y -= SPEED_PLAYER;
			}
		}
		SDL_FRect r = { player->x / SCALE32 * SCALE32, player->y / SCALE32 * SCALE32, 64, 64 };
		SDL_RenderRect(pRenderer, &r);
	}
}

void PlayerDraw(Player* player)
{
	if (player)
	{
		SDL_FRect r1 = { player->frame * 16 + player->dir * SCALE32, 0, 16, 16 };
		SDL_FRect r2 = { player->x, player->y, 64, 64 };
		SDL_RenderTexture(pRenderer, pTiles, &r1, &r2);
	}
}