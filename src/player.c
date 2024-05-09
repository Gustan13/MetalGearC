#include "player.h"

void playerMove(EntityContainer *container, Entity *player, SDL_Keycode *currentPressed)
{
    switch (*currentPressed)
    {
    case SDLK_w:
        player->y -= 1;
        playerCollideWall(container, player, VERTICAL);
        break;
    case SDLK_s:
        player->y += 1;
        playerCollideWall(container, player, VERTICAL);
        break;
    case SDLK_a:
        player->x -= 1;
        playerCollideWall(container, player, HORIZONTAL);
        break;
    case SDLK_d:
        player->x += 1;
        playerCollideWall(container, player, HORIZONTAL);
        break;
    default:
        break;
    }
}

void playerCollideWall(EntityContainer *container, Entity *player, dir_t direction)
{
    if (player->type != PLAYER)
        return;

    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (e->type != WALL)
            continue;

        if (
            player->x < e->x + 16 &&
            player->x + 16 > e->x &&
            player->y < e->y + 16 &&
            player->y + 16 > e->y)
            correctPlayerPosition(player, e, direction);
    }
}

void correctPlayerPosition(Entity *player, Entity *wall, dir_t direction)
{
    if (direction == HORIZONTAL)
    {
        if (player->x < wall->x + 16 && player->x + 16 > wall->x + 16)
            player->x = wall->x + 16;
        else if (player->x + 16 > wall->x && player->x < wall->x)
            player->x = wall->x - 16;
    }
    else
    {
        if (player->y < wall->y + 16 && player->y + 16 > wall->y + 16)
            player->y = wall->y + 16;
        else if (player->y + 16 > wall->y && player->y < wall->y)
            player->y = wall->y - 16;
    }
}