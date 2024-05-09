#ifndef _ENTITY
#define _ENTITY

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define TIMER 100

enum
{
    PLAYER,
    SOLDIER
};

typedef enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    FORWARD
} side_t;

typedef struct Entity
{
    int type, x, y;
    side_t side;
    SDL_Texture *myTexture;
    SDL_Rect *rect;
    struct Entity *nextEntity;
    void *extraModule;
} Entity;

typedef struct DoorModule
{
    int dX, dY, card;
    char *destLvl;
} DoorModule;

typedef struct EnemyModule
{
    side_t *path;
    int timer, dx, dy, index, pathSize;
} EnemyModule;

typedef struct ItemModule
{
    int type;
} ItemModule;

typedef struct EntityContainer
{
    struct Entity *first, *last;
} EntityContainer;

DoorModule *createDoor(int dX, int dY, int card, char *destLvl);
EnemyModule *createEnemy(side_t *path, int pathSize);
ItemModule *createItem(int type);
Entity *createEntity(int x, int y, int type, void *extraModule);
EntityContainer *createContainer();

void addEntity(EntityContainer *container, Entity *newEntity);
void removeEntity(EntityContainer *container, Entity *doomedEntity);
void removeAll(EntityContainer *container);
void drawEntities(EntityContainer *container, SDL_Renderer *renderer);

#endif