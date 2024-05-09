#ifndef _ENEMY
#define _ENEMY

#include "entity.h"

#define ENEMY_SPEED 1

void updateEnemy(Entity *enemy);
void calculateEnemyDestination(Entity *enemy);
int moveEnemyForward(Entity *entity);

#endif