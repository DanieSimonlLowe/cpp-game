#ifndef ENTITYS_HPP_INCLUDED
#define ENTITYS_HPP_INCLUDED
#include "entitys.cpp"
#include <list>
void tickEntitys(std::list<mob>& mobs, std::list<bullet>& bullets, tile grid[grid_size][grid_size], int x, int y, int* hp);
mob makeMob(std::list<mob>& mobs, int x, int y, float speed, aitype aiType);
#endif // GRID_HPP_INCLUDED
