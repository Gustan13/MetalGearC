#include "enemy.h"
#include <math.h>

void updateEnemy(EntityContainer *container, Entity *enemy, Entity *player, int *alert)
{
    EnemyModule *enemyModule = ((EnemyModule *)(enemy->extraModule));

    if (*alert)
    {
        enemyAlertMovement(container, enemy, player);
        return;
    }

    checkEnemySight(container, enemy, player, alert);

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
            return;
        }
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

    if (
        ((EnemyModule *)entity->extraModule)->dx == entity->x &&
        ((EnemyModule *)entity->extraModule)->dy == entity->y)
        return 1;

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
        if (direction == LEFT && player->x < e->x && enemy->x > e->x)
            return 0;
        if (direction == RIGHT && player->x > e->x && enemy->x < e->x)
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
        if (direction == UP && player->y < e->y && enemy->y > e->y)
            return 0;
        if (direction == DOWN && player->y > e->y && enemy->y < e->y)
            return 0;
    }
    return 1;
}

void enemyAlertMovement(EntityContainer *container, Entity *enemy, Entity *player)
{
    int xDist = (player->x + 8) - (enemy->x + 8);
    int yDist = (player->y + 8) - (enemy->y + 8);

    if (moveEnemyForward(enemy) == 1)
    {
        printf("%d %d\n", xDist, yDist);
        if (abs(xDist) > abs(yDist))
            enemy->side = xDist > 0 ? (RIGHT) : (LEFT);
        else
            enemy->side = yDist > 0 ? (DOWN) : (UP);

        calculateEnemyDestination(enemy);

        if (checkForObstacle(container, enemy))
            return;

        for (int i = 0; i < 4; i++)
        {
            enemy->side = i;
            calculateEnemyDestination(enemy);
            if (checkForObstacle(container, enemy))
                return;
        }
    }
}

int checkForObstacle(EntityContainer *container, Entity *enemy)
{
    EnemyModule *enemyModule = ((EnemyModule *)(enemy->extraModule));
    int eX, eY;

    for (Entity *e = container->first; e != NULL; e = e->nextEntity)
    {
        if (e->type != WALL)
            continue;
        eX = (int)(e->x / 16);
        eY = (int)(e->y / 16);

        if (eX == enemyModule->dx / 16 && eY == enemyModule->dy / 16)
            return 0;
    }

    return 1;
}