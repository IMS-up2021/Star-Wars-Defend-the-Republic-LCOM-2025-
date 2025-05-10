#ifndef PROJ_ENTITY_H
#define PROJ_ENTITY_H

#include <stdbool.h>
#include <lcom/lcf.h>


typedef struct {      
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
    const unsigned int x_pos;  
    const unsigned int y_pos;   
    const unsigned int width;    
    const unsigned int height;  
    const bool top;              
} Wall;


bool update_character(Character *character);

Wall *create_wall(bool top);

Character *create_character(xpm_map_t xpm);

Player *create_player(unsigned int max_health);

#endif