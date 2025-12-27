#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "LinkedList.h"
#include <SDL3/SDL.h>

extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;

typedef struct {
	int x;
	int y;
	int frame;
	int countframe;
	int count;
} Explosion;

void AddExplosion(LinkedList* linkedlist, int x, int y);
void ExplosionsUpdate(LinkedList* linkedlist);
void DrawExplosions(LinkedList* linkedlist);

#endif // !EXPLOSION_H

