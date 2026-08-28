#ifndef PLAYER_H
#define PLAYER_H
#include "defs.h"
#include "structs.h"
#include <stdio.h>
#include <stdbool.h>

#define SPEED_PLAYER 1

typedef struct {
	bool Star;
	bool Light;
	float Time;
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

