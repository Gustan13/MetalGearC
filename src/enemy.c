#include "enemy.h"
#include <math.h>

void updateEnemy(EntityContainer *container, Entity *enemy, Entity *player, int *alert)
{
    EnemyModule *enemyModule = ((EnemyModule *)(enemy->extraModule));

    checkEnemySight(container, enemy, player, alert);

    if (*alert)
        return;

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

void checkEnemySight(EntityContainer *container, Entity *enemy, Entity *player, int *alert)
{
    switch (enemy->side)
    {
    case LEFT:
        *alert = checkEnemyHorizontal(container, enemy, player, LEFT);
        break;
    case RIGHT:
        *alert = checkEnemyHorizontal(container, enemy, player, RIGHT);
        break;
    case UP:
        *alert = checkEnemyVertical(container, enemy, player, UP);
        break;
    case DOWN:
        *alert = checkEnemyVertical(container, enemy, player, DOWN);
        break;

    default:
        break;
    }
}

int checkEnemyHorizontal(EntityContainer *container, Entity *enemy, Entity *player, side_t direction)
{
    if ((int)(player->y / 16) != (int)(enemy->y / 16))
        return 0;

    if (direction == LEFT && player->x > enemy->x)
        return 0;
    else if (direction == RIGHT && player->x < enemy->x)
        return 0;

    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (e->type != WALL)
            continue;
        if ((int)(e->y / 16) != (int)(enemy->y / 16))
            continue;
        if (direction == LEFT && player->x < e->x)
            return 0;
        if (direction == RIGHT && player->x > e->x)
            return 0;
    }
    return 1;
}

int checkEnemyVertical(EntityContainer *container, Entity *enemy, Entity *player, side_t direction)
{
    if ((int)(player->x / 16) != (int)(enemy->x / 16))
        return 0;

    if (direction == UP && player->y > enemy->y)
        return 0;
    else if (direction == DOWN && player->y < enemy->y)
        return 0;

    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (e->type != WALL)
            continue;
        if ((int)(e->x / 16) != (int)(enemy->x / 16))
            continue;
        if (direction == UP && player->y < e->y)
            return 0;
        if (direction == DOWN && player->y > e->y)
            return 0;
    }
    return 1;
}