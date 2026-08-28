#ifndef BULLET_H
#define BULLET_H
#include <SDL3/SDL.h>
#include "defs.h"
#include "Player.h"
#include "Enemy.h"
#include "structs.h"
#include "Explosion.h"
#include "LinkedList.h"



extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;

typedef struct {
	int x;
	int y;
	int ID;
	DIRECTION dir;
	bool isMove;
} Bullet;


void AddBullet(LinkedList* linkedlist, void* entity, int type);
void UpdateBullets(LinkedList* bulletslist, LinkedList* explosionslist, int level[][26]);
void DrawBullets(LinkedList* linkedlist);

#endif // 

