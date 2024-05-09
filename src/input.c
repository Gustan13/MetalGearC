#include "input.h"

void handle_input(SDL_Event *e, SDL_Keycode *current_pressed)
{
    if (e->type == SDL_KEYDOWN)
        *current_pressed = e->key.keysym.sym;

    if (e->type == SDL_KEYUP)
        if (e->key.keysym.sym == *current_pressed)
            *current_pressed = 0;
}