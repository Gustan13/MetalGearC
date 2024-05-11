#ifndef _ENEMY
#define _ENEMY

#include "entity.h"

#define ENEMY_SPEED 1

void updateEnemy(EntityContainer *container, Entity *enemy, Entity *player, int *alert);
void calculateEnemyDestination(Entity *enemy);
int moveEnemyForward(Entity *entity);

void checkEnemySight(EntityContainer *container, Entity *enemy, Entity *player, int *alert);
int checkEnemyHorizontal(EntityContainer *container, Entity *enemy, Entity *player, side_t direction);
int checkEnemyVertical(EntityContainer *container, Entity *enemy, Entity *player, side_t direction);

#endif