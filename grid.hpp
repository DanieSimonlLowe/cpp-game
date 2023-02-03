#ifndef GRID_HPP_INCLUDED
#define GRID_HPP_INCLUDED
void changeGridCell(tile grid[grid_size][grid_size], tile newTile, int x, int y);
tile getGridCell(tile grid[grid_size][grid_size],int x, int y);
void setupGird(tile grid[grid_size][grid_size]);
bool cellIsWall(tile grid[grid_size][grid_size],int x, int y);
#include "grid.cpp"

#endif // GRID_HPP_INCLUDED
