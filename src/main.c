#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "init.h"
#include "input.h"
#include "texture.h"
#include "entity.h"
#include "enemy.h"
#include "player.h"
#include "update.h"

#include <stdio.h>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 192;

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    Textures *textures = NULL;
    EntityContainer *container = NULL;
    Entity *player = NULL;

    int running = 1;
    int alert = 0;
    SDL_Keycode current_pressed = 0;

    if (init(&window, &renderer))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return 1;
    }

    textures = loadMedia(renderer);
    container = createContainer();

    player = createEntity(128, 96, PLAYER, NULL);
    addEntity(container, player);

    side_t path[] = {FORWARD, RIGHT, FORWARD, DOWN, FORWARD, LEFT, FORWARD, UP};
    addEntity(container, createEntity(200, 100, SOLDIER, createEnemy(path, 8)));

    addEntity(container, createEntity(80, 80, WALL, NULL));

    while (running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                running = 0;

            handle_input(&e, &current_pressed);
        }

        playerMove(container, player, &current_pressed);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);

        // SDL_RenderCopy(renderer, textures->hello, NULL, NULL);
        drawEntities(container, renderer);
        SDL_RenderPresent(renderer);

        // UPDATE STUFF

        updateAll(container, player, &alert);

        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    removeAll(container);
    free(container);

    IMG_Quit();
    SDL_Quit();

    return 0;
}