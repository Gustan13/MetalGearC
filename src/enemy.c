#include "enemy.h"

void updateEnemy(Entity *enemy)
{
    EnemyModule *enemyModule = ((EnemyModule *)(enemy->extraModule));
    int prevIndex = enemyModule->index;

    if (enemyModule->index < 0)
        enemyModule->index = enemyModule->pathSize - 1;

    if (enemyModule->path[enemyModule->index] == FORWARD)
    {
        if (enemyModule->timer < 1)
        {
            if (moveEnemyForward(enemy) == 1)
            {
                enemyModule->index--;
                printf("Arrived\n");
                enemyModule->timer = TIMER;
            }
        }
        else
            enemyModule->timer--;
    }
    else
    {
        enemyModule->timer--;
        if (enemyModule->timer < 1)
        {
            enemy->side = enemyModule->path[enemyModule->index];
            enemyModule->timer = TIMER;
            enemyModule->index--;
            printf("Turned\n");
            calculateEnemyDestination(enemy);
        }
    }
}

void calculateEnemyDestination(Entity *enemy)
{
    EnemyModule *enemyModule = ((EnemyModule *)(enemy->extraModule));

    enemyModule->dx = enemy->x;
    enemyModule->dy = enemy->y;

    switch (enemy->side)
    {
    case LEFT:
        enemyModule->dx = enemy->x - 16;
        break;
    case RIGHT:
        enemyModule->dx = enemy->x + 16;
        break;
    case UP:
        enemyModule->dy = enemy->y - 16;
        break;
    case DOWN:
        enemyModule->dy = enemy->y + 16;
        break;
    default:
        break;
    }
}

int moveEnemyForward(Entity *entity)
{
    if (entity->type != SOLDIER)
        return 0;

    if (
        ((EnemyModule *)entity->extraModule)->dx == entity->x &&
        ((EnemyModule *)entity->extraModule)->dy == entity->y)
        return 1;

    switch (entity->side)
    {
    case LEFT:
        entity->x -= ENEMY_SPEED;
        break;
    case RIGHT:
        entity->x += ENEMY_SPEED;
        break;
    case UP:
        entity->y -= ENEMY_SPEED;
        break;
    case DOWN:
        entity->y += ENEMY_SPEED;
        break;
    default:
        break;
    }

    return 2;
}