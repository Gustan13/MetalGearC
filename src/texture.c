#include "texture.h"

#define TEXTURE_AMOUNT 256

SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path);

    if (loadedSurface != NULL)
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

Textures *loadMedia(SDL_Renderer *renderer)
{
    Textures *texture_container = malloc(sizeof(Textures));

    texture_container->hello = loadTexture("hello.png", renderer);

    return texture_container;
}