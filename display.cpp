#include <graphics.h>
#include "grid.hpp"
//#define has_grid_lines
#include "consonants.hpp"
#include "entitys.hpp"
#include "grid.hpp"

void openWindow()
{
    initwindow(max_x,max_y);
    #ifdef has_grid_lines
    setcolor(15);
    for (int i = 1; i < grid_size; i ++) {
        line(i*(*grid_x),0 ,i*(*gridx), max_y);
        line(0,i*(*grid_y) ,maxx, i*(*grid_y));
    }
    #endif
    return ;
}

void drawPlayer () {
    setfillstyle(1,MAGENTA);
    bar(grid_sqear_size*player_screen_pos+3,grid_sqear_size*player_screen_pos+3,grid_sqear_size*(player_screen_pos+1)-3,grid_sqear_size*(player_screen_pos+1)-3);
}

void updateTileDisplay(tile state , int i, int j)
{
    setfillstyle(1,color[state]);

    bar(grid_sqear_size*i,grid_sqear_size*j,grid_sqear_size*(i+1),grid_sqear_size*(j+1));

}


void updateGridDisplay(tile grid[grid_size][grid_size],  int x, int y)
{
    for (int i = 0; i < cell_display_size; i++) {
        for (int j = 0; j < cell_display_size; j++) {
            updateTileDisplay(getGridCell(grid,i+x,j+y), i, j);
        }
    }
}

void updateBulletDisplay(bullet bull, int i, int j) {
    setfillstyle(bulletStyle[bull.effectCause],color[bull.effectType]);
    fillellipse(grid_sqear_size*i+1,grid_sqear_size*j+1,grid_sqear_size-1,grid_sqear_size-1);
}

void updateMobDisplay(mob m, int i, int j)
{
    setfillstyle(aiStyle[m.aiType],RED);
    bar(grid_sqear_size*i+1,grid_sqear_size*j+1,grid_sqear_size*(i+1)-1,grid_sqear_size*(j+1)-1);
}

void updateEnititysDisplay(std::list<bullet>& bullets, std::list<mob>& mobs, int x, int y)
{
    for (auto it = bullets.begin() ; it != bullets.end(); ++it) {
        int i = ((*it).position.x) - x;
        int j = ((*it).position.y) - y;
        if (i >= 0 && i < cell_display_size) {
            if (j >= 0 && j < cell_display_size) {
                updateBulletDisplay(*it,i,j);
            }
        }
    }
    for (auto it = mobs.begin() ; it != mobs.end(); ++it) {
        int i = ((*it).position.x) - x;
        int j = ((*it).position.y) - y;
        if (i >= 0 && i < cell_display_size) {
            if (j >= 0 && j < cell_display_size) {
                updateMobDisplay(*it,i,j);
            }
        }
    }
}


void updateDiplay(tile grid[grid_size][grid_size], std::list<bullet>& bullets, std::list<mob>& mobs, int x, int y)
{
    updateGridDisplay(grid, x, y);
    updateEnititysDisplay(bullets, mobs, x, y);
    drawPlayer();
    if (getactivepage() == 0) {
        setactivepage(1);
        setvisualpage(0);
    } else {
        setactivepage(0);
        setvisualpage(1);
    }
}

void exitWindow()
{
    closegraph();
}
