#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_SPAWN_DELAY 180
#define MAX_ENEMIES 20

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
    unsigned int pixels_per_sec;  // Movement in pixels per second
    unsigned int attack_range;
    uint8_t *sprite;
    bool enemy;
} Character;

typedef struct {
    unsigned int x;
    unsigned int y;
} CharacterPos;

extern Character *active_enemies[MAX_ENEMIES];
extern int num_active_enemies;
extern unsigned int enemy_spawn_tick_counter;
extern unsigned int timer_frequency_hz;

Character *createEnemy(CharacterPos pos, int enemy_type);
void add_enemy_to_game(CharacterPos pos, int enemy_type);
void update_and_spawn_enemies(void);
void draw_enemies(void);
bool init_enemies(void);
void set_timer_frequency_for_enemies(unsigned int hz);

#endif // ENEMY_H
