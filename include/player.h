#ifndef _PLAYER
#define _PLAYER

#include "entity.h"

typedef enum dir
{
    VERTICAL,
    HORIZONTAL
} dir_t;

void playerMove(EntityContainer *container, Entity *player, SDL_Keycode *currentPressed);
void playerCollideWall(EntityContainer *container, Entity *player, dir_t direction);
void correctPlayerPosition(Entity *player, Entity *wall, dir_t direction);

#endif