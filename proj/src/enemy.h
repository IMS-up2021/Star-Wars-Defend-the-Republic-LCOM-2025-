#ifndef ENEMY_H
#define ENEMY_H

#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "controllers/video/graphics.h"


typedef struct {      
    int gold;
    unsigned int max_health;  
} Player;


typedef struct {
    unsigned int x_pos;  
    unsigned int y_pos;   
    unsigned int width;    
    unsigned int height;
    unsigned int damage;
    unsigned int health;
    unsigned int speed;
    unsigned int attack_range;
    uint8_t *sprite;
    bool enemy; 
} Character;

typedef struct {
    unsigned int x;
    unsigned int y;
} CharacterPos;


Character *createEnemy(CharacterPos pos, int enemy_type);

void spawnEnemies();

#endif // ENEMY_H
