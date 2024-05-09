#include "walls.h"

int collideWalls(EntityContainer *container, Entity *collider)
{
    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (collider == e || e->type != WALL)
            continue;
        if (
            collider->x < e->x + 16 &&
            collider->x + 16 > e->x &&
            collider->y < e->y + 16 &&
            collider->y + 16 > e->y)
            return 1;
    }

    return 0;
}