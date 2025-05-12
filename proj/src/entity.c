#include "entity.h"
#include <math.h>


bool update_character(Character *character) {
    if (character == NULL) return false;

    // Exemplo de movimento horizontal (pode adaptar conforme lógica do jogo)
    if (character->enemy) {
        character->x_pos -= character->speed;
    } else {
        character->x_pos += character->speed;
    }

    // Evita que o personagem saia da tela (ajuste conforme seu limite de tela)
    if (character->x_pos > x_max - character->width)
        character->x_pos = x_max - character->width;
    if (character->x_pos < 0)
        character->x_pos = 0;

    return true;
}


// isto vai ser os limites inferior e superior (no topo tem as barrinhas de vida/em baixo tem os personagens jogaveis e os botões)
Wall *create_wall(bool top) {
    Wall *wall = (Wall *)malloc(sizeof(Wall));
    if (!wall) return NULL;

    *wall = (Wall){
        .x_pos = 0,
        .y_pos = top ? 0 : y_max - 10,
        .width = x_max,
        .height = 10, // depois isto pode ser ajustado (em principio não teriam o mesmo tamanho)
        .top = top
    };

    return wall;
}


Character *create_character(bool enemy) {
    Character *character = (Character *)malloc(sizeof(Character));
    if (!character) return NULL;

    *character = (Character){
        .x_pos = enemy ? x_max - 60 : 60, // isto depois é ajustado
        .y_pos = y_max / 2, // isto depois é ajustado
        .width = 40,
        .height = 60,
        .damage = 10,
        .health = 100,
        .speed = 5,
        .attack_range = 30,
        .enemy = enemy
    };

    return character;
}

Player *create_player(unsigned int max_health) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (!player) return NULL;

    *player = (Player){
        .max_health = 100 // isto depois é ajustado
    };

    return player;
}

Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm){
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    xpm_image_t image;
    uint8_t *sprite = xpm_load(xpm, XPM_INDEXED, &image);
    *cursor = (Cursor){pos_x, pos_y, image.width, image.height, sprite};
    return cursor;
}