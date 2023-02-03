#ifndef CONTROLLER_HPP_INCLUDED
#define CONTROLLER_HPP_INCLUDED
#include "controller.cpp"
#include <windows.h>
DWORD WINAPI inputThread(void *i);
void playerTick(tile grid[grid_size][grid_size],   int& x, int& y);
#endif // CONTROLLER_HPP_INCLUDED
