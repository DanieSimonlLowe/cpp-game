#include "consonants.hpp"
#include "vecMath.hpp"
#include "grid.hpp"

typedef struct bullet {
    point position;
    vec2d velocity;
    tile effectType;
    effectcause effectCause;
    int tickLeft;
} bullet;

typedef struct mob {
    point position;
    vec2d velocity;
    float speed;
    aitype aiType;
} mob;


bool tickBullet(bullet *bull, tile grid[grid_size][grid_size]) {
    int oldPosX = bull->position.x;
    int oldPosY = bull->position.y;
    bull->position.x += bull->velocity.x;
    bull->position.y += bull->velocity.y;
    int newPosX = bull->position.x;
    int newPosY = bull->position.y;

    if (cellIsWall(grid,newPosX,newPosY) || bull->tickLeft <= 0) {
        if (bull->effectCause == explosion) {
            for (int i = -explosion_size; i <= explosion_size; i++) {
                for (int j = -explosion_size; j <= explosion_size; j++) {
                    changeGridCell(grid,bull->effectType,newPosX + i, newPosY + j);
                }
            }
        }
        return true;
    }
    bull->tickLeft--;
    return false;
}

void dumbAi(mob *m, tile grid[grid_size][grid_size],int x, int y) {
    m->velocity.x = player_pos_x - m->position.x;
    m->velocity.y = player_pos_y - m->position.y;
    normalize(&m->velocity);
    malt(&m->velocity, m->speed);
}

bool tickMob(mob *m, tile grid[grid_size][grid_size],  int x, int y, int *hp) {
    static void (*ais[1])(mob* m,tile grid[grid_size][grid_size],int x,int y) = {dumbAi};
    int oldPosX = m->position.x;
    int oldPosY = m->position.y;
    if (getGridCell(grid,oldPosX,oldPosY) != slip || lensq(&m->velocity) < float_zero) {
        ais[m->aiType](m,grid,x,y);
    }
    if (getGridCell(grid,oldPosX,oldPosY) == slow) {
        malt(&m->velocity, slow_factor);
    } else if (getGridCell(grid,oldPosX,oldPosY) == fast) {
        malt(&m->velocity, fast_factor);
    }
    m->position.x += m->velocity.x;
    m->position.y += m->velocity.y;

    int newPosX = m->position.x;
    int newPosY = m->position.y;
    if (newPosX == player_pos_x && newPosY == player_pos_y) {
        (*hp)--;
        return true;
    }

    if (getGridCell(grid,newPosY,newPosY) == wall) {
        changeGridCell(grid, none, newPosX, newPosY);
        return true;
    } else if (getGridCell(grid,newPosX,newPosY) == permWall) {
        return true;
    }
    return false;
}

void tickEntitys(std::list<mob>& mobs, std::list<bullet>& bullets, tile grid[grid_size][grid_size],  int x, int y, int *hp) {
    for (auto it = bullets.begin() ; it != bullets.end();) {
        if (tickBullet(&(*it),grid)) {
            it = bullets.erase(it);
        } else {
            it++;
        }
    }
    for (auto it = mobs.begin() ; it != mobs.end(); ) {
        if (tickMob(&(*it),grid,x,y,hp)) {
            it = mobs.erase(it);
        } else {
            it++;
        }
    }
}

mob makeMob(std::list<mob>& mobs, int x, int y, float speed, aitype aiType) {
    mob newMob;
    newMob.velocity = {0,0};
    newMob.position = {((float)x)+0.5,((float)y)+0.5};
    newMob.speed = speed;
    newMob.aiType = aiType;
    mobs.push_front(newMob);
}
