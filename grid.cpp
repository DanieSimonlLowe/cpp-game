#include "consonants.hpp"

void changeGridCell(tile grid[grid_size][grid_size], tile newTile, int x, int y) {
    if (x >= 0 && x < grid_size && y >= 0 && y < grid_size && grid[x][y] != permWall) {
        grid[x][y] = newTile;
    }
}

tile getGridCell(tile grid[grid_size][grid_size],int x, int y) {
    if (x < 0 || x >= grid_size || y < 0 || y >= grid_size) {
        return permWall;
    } else {
        return grid[x][y];
    }
}

void setupGird(tile grid[grid_size][grid_size]) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            grid[i][j] = none;
        }
    }
}

bool cellIsWall(tile grid[grid_size][grid_size],int x, int y) {
    tile cell = getGridCell(grid,x,y);
    return (cell == wall || cell == permWall);
}
