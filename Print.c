#include "Print.h"

void Print(int coordX, int coordY, const char* text, int inverse)
{
	for (int i = 0; text[i] != '\0'; ++i)
	{
		int charX = (text[i] - 32) % 32;
		int charY = (text[i] - 32) / 32 + inverse * 3;
		SDL_FRect r1 = { charX << 3, charY << 3, 8, 8 };
		SDL_FRect r2 = { i * 32 + coordX, coordY, 32, 32 };
		SDL_RenderTexture(pRenderer, pFont, &r1, &r2);
	}
}