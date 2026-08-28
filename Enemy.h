#ifndef ENEMY_H
#define ENEMY_H
#include <SDL3/SDL.h>
#include "defs.h"
#include "structs.h"
#include "LinkedList.h"
#include "Bullet.h"
#include "Explosion.h"

#define SPEED_ENEMY 1

typedef struct {
	bool Star;
	float Time;
	int x;
	int y;
	int ID;
	DIRECTION dir;
	int frame;
} Enemy;

void AddEnemy(LinkedList* linkedlist, int ID);
void UpdateEnemies(LinkedList* linkedlist, int level[][26]);
void DrawEnemies(LinkedList* linkedlist);
void CheckCollisions(LinkedList* enemies, LinkedList* bullets, LinkedList* explosionslist);

#endif // !ENEMY_H

