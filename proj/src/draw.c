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
int player_gold = 100;
unsigned int player_enemy_health = 100;

uint16_t x_max = 1024;
uint16_t y_max = 768;

// uint8_t *background;
uint8_t *background_menu;
uint8_t *background_instructions;
uint8_t *background_game_over;

// não sei se funciona
bool init_walls(void) {
    if (!(top_wall = draw_wall(*wall, top_wall_xpm)) || !(bottom_wall = draw_wall(*wall, bottom_wall_xpm))) {
        return false; // a criação da parede falhou
    }
    return true;
}
// não sei se funciona
int draw_wall(Wall *wall, xpm_image_t *wall_xpm) {
    if (!wall || !wall_xpm) {
        printf("%s: wall or wall_xpm is NULL\n", __func__);
        return 1;
    }

    // Desenha a parede usando a imagem XPM
    if (print_xpm(wall_xpm, wall->x_pos, wall->y_pos)) {
        printf("%s: print_xpm(wall_xpm, wall->x_pos: %d, wall->y_pos: %d) error\n", __func__, wall->x_pos, wall->y_pos);
        return 1;
    }

    return 0;
}

