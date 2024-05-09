#include "update.h"

void updateAll(EntityContainer *container)
{
    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        switch (e->type)
        {
        case SOLDIER:
            updateEnemy(e);
            break;

        default:
            break;
        }
    }
}