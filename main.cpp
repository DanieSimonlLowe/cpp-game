#include <time.h>
#include <list>
#include <windows.h>
#include "consonants.hpp"
#include "display.hpp"
#include "grid.hpp"
#include "entitys.hpp"
#include "controller.hpp"


int main() {
    tile grid[grid_size][grid_size];
    setupGird(grid);

    grid[start_pos+7][start_pos+7] = permWall;
    grid[start_pos+7][start_pos+8] = wall;
    grid[start_pos+7][start_pos+6] = wall;
    grid[start_pos+7][start_pos+5] = wall;

    float x = start_pos, y = start_pos;
    int hp = start_hp;
    std::list<mob> mobs;
    std::list<bullet> bullets;

    openWindow();
    HANDLE thread = CreateThread(NULL, 0, inputThread, NULL, 0, NULL);
    struct timespec remaining, request = {0, tick_nano_amount};
    while (hp > 0) {
        tickEntitys(mobs,bullets,grid,x,y,&hp);
        updateDiplay(grid,bullets,mobs,x,y);
        playerTick(grid, x,y);

        nanosleep(&request, &remaining);

    }

}
