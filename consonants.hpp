#ifndef CONSONANTS_HPP_INCLUDED
#define CONSONANTS_HPP_INCLUDED
#define tick_nano_amount 16666666
#define grid_size 100
#define cell_display_size 30
#define max_window 685
#define grid_sqear_size (max_window/cell_display_size)
#define max_x (grid_sqear_size*cell_display_size)
#define max_y (grid_sqear_size*cell_display_size)
#define player_screen_pos (cell_display_size/2)
#define player_pos_x (player_screen_pos + x)
#define player_pos_y (player_screen_pos + y)
#define start_pos ((grid_size/2)-(cell_display_size/2))
#define float_zero 0.001
#
#define start_hp 3
#define defult_player_move_speed 0.5
#define explosion_size 2
#define slow_factor 0.2
#define fast_factor 3
#include <graphics.h>

enum tile{none,slow,slip,wall,permWall,fast};
const int color[] = {BLACK,BROWN,CYAN,LIGHTGRAY,WHITE,RED}; // tile to color
enum effectcause {trail,explosion};
const int bulletStyle[] = {SOLID_FILL,HATCH_FILL}; // effectcause to fill style
enum aitype {dumb};
const int aiStyle[] = {XHATCH_FILL}; // aitype to fill style

typedef struct point {
    float x;
    float y;
} point;
typedef point vec2d;

#endif // CONSONANTS_HPP_INCLUDED
