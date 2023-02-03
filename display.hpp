#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED
#include <list>
#include "consonants.hpp"
#include "entitys.hpp"
void openWindow();
void updateDiplay(tile grid[grid_size][grid_size], std::list<bullet>& bullets, std::list<mob>& mobs, int x, int y);
void exitWindow();
#include "display.cpp"
#endif // DISPLAY_HPP_INCLUDED
