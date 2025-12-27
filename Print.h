#ifndef PRINT_H
#define PRINT_H
#include <SDL3/SDL.h>

extern SDL_Renderer* pRenderer;
extern SDL_Texture* pTiles;
extern SDL_Texture* pFont;

void Print(int coordX, int coordY, const char* text, int inverse);
#endif // !PRINT_H

