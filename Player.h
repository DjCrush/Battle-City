#ifndef PLAYER_H
#define PLAYER_H
#include "defs.h"
#include "structs.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include "Print.h"

#define SPEED_PLAYER 1

extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;
extern SDL_Texture* pFont;

typedef struct {
	int x;
	int y;
	DIRECTION dir;
	int frame;
	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
} Player;

void PlayerUpdate(Player* player, int level[][26]);
void PlayerDraw(Player* player);
#endif // !PLAYER_H

