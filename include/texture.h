#ifndef _TEXTURE
#define _TEXTURE

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include <stdlib.h>

typedef struct Textures
{
    SDL_Texture *hello;
} Textures;

SDL_Texture *
loadTexture(const char *path, SDL_Renderer *renderer);
Textures *loadMedia(SDL_Renderer *renderer);

#endif