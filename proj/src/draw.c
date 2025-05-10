#include <lcom/lcf.h>
#include <math.h>

#include "draw.h"
#include "controllers/video/graphics.h"

vbe_mode_info_t mode_info;

Button *play_button;
Cursor *cursor_menu;
Button *quit;
Button *instruction_button;
Wall *top_wall;
Wall *bottom_wall;

Player *player;
Player *player_enemy;

unsigned int player_health = 100;
unsigned int player_enemy_health = 100;

uint16_t x_max = 1024;
uint16_t y_max = 768;

uint8_t *background;
uint8_t *background_menu;
uint8_t *background_instructions;
uint8_t *background_game_over;

