#include "entity.h"

DoorModule *createDoor(int dX, int dY, int card, char *destLvl)
{
    DoorModule *door = malloc(sizeof(DoorModule));

    door->dX = dX;
    door->dY = dY;
    door->card = card;
    strcpy(door->destLvl, destLvl);

    return door;
}

EnemyModule *createEnemy(side_t *path, int pathSize)
{
    EnemyModule *enemy = malloc(sizeof(EnemyModule));

    enemy->path = path;
    enemy->timer = TIMER;
    enemy->dx = 0;
    enemy->dy = 0;
    enemy->pathSize = pathSize;
    enemy->index = pathSize - 1;

    return enemy;
}

ItemModule *createItem(int type)
{
    ItemModule *item = malloc(sizeof(ItemModule));

    item->type = type;

    return item;
}

Entity *createEntity(int x, int y, int type, void *extraModule)
{
    Entity *newEntity = malloc(sizeof(Entity));
    newEntity->x = x;
    newEntity->y = y;
    newEntity->type = type;

    newEntity->nextEntity = NULL;
    newEntity->extraModule = extraModule;
    newEntity->side = UP;

    return newEntity;
}

EntityContainer *createContainer()
{
    EntityContainer *newContainer = malloc(sizeof(EntityContainer));

    newContainer->first = NULL;
    newContainer->last = NULL;

    return newContainer;
}

void addEntity(EntityContainer *container, Entity *newEntity)
{
    if (container->first == NULL)
    {
        container->first = newEntity;
        container->last = newEntity;
        return;
    }

    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (newEntity == e)
            break;

        if (e->nextEntity == NULL)
        {
            e->nextEntity = newEntity;
            container->last = newEntity;

            break;
        }
    }
}

void removeEntity(EntityContainer *container, Entity *doomedEntity)
{
    Entity *prev = NULL, *next = NULL;

    if (container->first == NULL)
        return;

    if (container->first == container->last)
    {
        container->first = NULL;
        container->last = NULL;
        free(doomedEntity);
        return;
    }

    if (container->first == doomedEntity)
    {
        next = doomedEntity->nextEntity;
        container->first = next;
        free(doomedEntity);
        return;
    }

    prev = container->first;
    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        next = e->nextEntity;

        if (e == doomedEntity)
        {
            prev->nextEntity = next;
            free(e);

            if (prev->nextEntity == NULL)
                container->last = prev;
            break;
        }

        prev = e;
    }
}

void removeAll(EntityContainer *container)
{
    Entity *aux = NULL;
    for (Entity *e = container->first; e != NULL; e = aux)
    {
        aux = e->nextEntity;
        free(e);
    }

    container->first = NULL;
    container->last = NULL;
}

void drawEntities(EntityContainer *container, SDL_Renderer *renderer)
{
    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (e->type == PLAYER)
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        else if (e->type == SOLDIER)
            SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
        else
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
        SDL_Rect fillRect = {e->x, e->y, 16, 16};
        SDL_RenderFillRect(renderer, &fillRect);
    }
}

// ENEMY MOVEMENT