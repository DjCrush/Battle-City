#include <SDL3/SDL.h>
#undef main
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "Title.h"
#include "Game.h"

SDL_Renderer* pRenderer = NULL;
SDL_Texture* pTiles = NULL;
SDL_Texture* pFont = NULL;

#define SCALE32 32
//#define SCALE64 64

void CreateTexture(SDL_Texture** pTexture, const char* file)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(file);
	if (!loadedSurface)
	{
		fprintf(stderr, "Failed to load %s: %s\n", file, SDL_GetError());
		SDL_DestroyRenderer(pRenderer);
		SDL_Quit();
		return NULL;
	}
	*pTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
	SDL_SetTextureScaleMode(*pTexture, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(loadedSurface);
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	SDL_Window* pWindow = NULL;
	SDL_CreateWindowAndRenderer("Battle City", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_TRANSPARENT, &pWindow, &pRenderer);

	CreateTexture(&pFont, "f.bmp"); if (!pFont) return 1; 
	CreateTexture(&pTiles, "tiles.bmp"); if (!pTiles) return 1;
	Title();
	Game();
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
	return 0;
}
