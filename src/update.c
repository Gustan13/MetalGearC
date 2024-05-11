#include "update.h"

void updateAll(EntityContainer *container, Entity *player, int *alert)
{
    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        switch (e->type)
        {
        case SOLDIER:
            updateEnemy(container, e, player, alert);
            break;

        default:
            break;
        }
    }
}