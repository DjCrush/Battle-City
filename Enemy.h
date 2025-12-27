#ifndef ENEMY_H
#define ENEMY_H
#include <SDL3/SDL.h>
#include "defs.h"
#include "structs.h"
#include "LinkedList.h"
#include "Bullet.h"
#include "Explosion.h"

#define STEP_ENEMY 1

extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;

typedef struct {
	int x;
	int y;
	int ID;
	DIRECTION dir;
	int frame;
} Enemy;

void AddEnemy(LinkedList* linkedlist, int ID);
void EnemyUpdate(LinkedList* linkedlist);
void DrawEnemies(LinkedList* linkedlist);
void checkCollision(LinkedList* enemies, LinkedList* bullets, LinkedList* explosionslist);

#endif // !ENEMY_H

