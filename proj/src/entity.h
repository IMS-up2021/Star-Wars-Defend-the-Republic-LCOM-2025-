#ifndef PROJ_ENTITY_H
#define PROJ_ENTITY_H

#include <stdbool.h>
#include <lcom/lcf.h>


typedef struct {      
    int gold;
    unsigned int max_health;  
} Player;


typedef struct {
    const unsigned int x_pos;  
    const unsigned int y_pos;   
    const unsigned int width;    
    const unsigned int height;
    const unsigned int damage;
    const unsigned int health;
    const unsigned int speed;
    const unsigned int attack_range;
    bool enemy; 
} Character;


typedef struct {
    unsigned int pos_x;
    unsigned int pos_y;
    unsigned int width;
    unsigned int height;
    uint8_t *sprite;
} Cursor;


Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm);

bool (init_cursor)(void);

int draw_cursor(Cursor *cursor);

#endif
