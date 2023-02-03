#include "consonants.hpp"
#include "grid.hpp"
#include <windows.h>
#define move_back 1
enum direction {up,down,left,right,stay};

direction dir = stay;
direction curr = stay;
bool updateDir = false;

void inputKey(char key)
{
    switch (key) {
    case 72:
        curr = up;
        break;
    case 80:
        curr = down;
        break;
    case 75:
        curr = left;
        break;
    case 77:
        curr = right;
    default:
        break;
    }
}

DWORD WINAPI inputThread(void *i)
{
    char c;
    while (true) {
        c = getch();
        switch(c) {
        case '8':
        case 'w':
            curr = up;
            break;
        case '4':
        case 'a':
            curr = left;
            break;
        case '2':
        case 's':
            curr = down;
        break;
        case '6':
        case 'd':
            curr = right;
            break;
        case 0:
            inputKey(getch());
        default:
            break;
        }
    }
}

float getMoveFactor(tile grid[grid_size][grid_size], int x, int y) {
    float factor = defult_player_move_speed;
    if (getGridCell(grid,player_pos_x,player_pos_y) == slow) {
        factor *= slow_factor;
    } else if (getGridCell(grid,player_pos_x,player_pos_y) == fast) {
        factor *= fast_factor;
    }
    return factor;
}

float getMoveAmount(tile grid[grid_size][grid_size] ,float moveFactor, float x, float y) {
    if (dir == up) {
        for (int i = 1; i < moveFactor; i++) {
            if (cellIsWall(grid,player_pos_x,player_pos_y-i)) {
                updateDir = true;
                return i-move_back;
            }
        }
        if (cellIsWall(grid,player_pos_x,player_pos_y-moveFactor)) {
            updateDir = true;
            return moveFactor-move_back;
        }
    } else if (dir == down) {
        for (int i = 1; i < moveFactor; i++) {
            if (cellIsWall(grid,player_pos_x,player_pos_y+i)) {
                updateDir = true;
                return i-move_back;
            }

        }
        if (cellIsWall(grid,player_pos_x,player_pos_y+moveFactor)) {
            updateDir = true;
            return moveFactor-move_back;
        }
    } else if (dir == left) {
        for (int i = 1; i < moveFactor; i++) {
            if (cellIsWall(grid,player_pos_x-i,player_pos_y)) {
                updateDir = true;
                printf("i:%d and %f\n",i , i-move_back);
                return (float)(i-move_back);
            }

        }
        if (cellIsWall(grid,player_pos_x-moveFactor,player_pos_y)) {
            updateDir = true;
            return moveFactor-move_back;
        }
    } else if (dir == right) {
        for (int i = 1; i < moveFactor; i++) {
            if (cellIsWall(grid,player_pos_x+i,player_pos_y)) {
                updateDir = true;
                return i-move_back;
            }

        }
        if (cellIsWall(grid,player_pos_x+moveFactor,player_pos_y)) {
            updateDir = true;
            return moveFactor-move_back;
        }
    }
    //printf("(%d,%d)\n",x,y)
    return moveFactor;
}

void playerTick(tile grid[grid_size][grid_size], float& x, float& y) {
    if (getGridCell(grid,player_pos_x,player_pos_y) != slip) {
        dir = curr;
    } else if (dir == stay) {
        dir = curr;
    }
    float moveAmount = getMoveAmount(grid,getMoveFactor(grid,x,y),x,y);

    if (moveAmount <= float_zero) {
        // if zero don't move
    } else if (dir == up) {
        y -= moveAmount;
    } else if (dir == down) {
        y += moveAmount;
    } else if (dir == left) {
        printf("MA: %d\n",moveAmount);
        x -= moveAmount;
    } else if (dir == right) {
        x += moveAmount;
    }

    curr = stay;
    if (updateDir) {
        dir = stay;
    }
}
