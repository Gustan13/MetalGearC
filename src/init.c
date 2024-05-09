#include "init.h"

int init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    *window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        512, 480, SDL_WINDOW_SHOWN);
    if (*window == NULL)
        return 1;

    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
        return 1;

    int imgFlags = IMG_INIT_PNG;
    if ((!IMG_Init(imgFlags)) & imgFlags)
        return 1;

    return 0;
}