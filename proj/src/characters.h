#ifndef __CHARACTERS_H
#define __CHARACTERS_H

#include <lcom/lcf.h>
#include <lcom/xpm.h>

#include "enemy.h" 

#define MAX_PLAYER_CHARACTERS 15

#define PLAYER_CHAR_TYPE_1 0
#define PLAYER_CHAR_TYPE_2 1
#define PLAYER_CHAR_TYPE_3 2

extern Character *active_player_chars[MAX_PLAYER_CHARACTERS];
extern int num_active_player_chars;

bool init_player_units(void);
Character *create_player_unit(CharacterPos pos, int unit_type);
void add_player_unit_to_game(CharacterPos pos, int unit_type);

void handle_player_unit_spawn_input(uint8_t scancode); 
void update_and_spawn_player_units(void); // For movement, AI, etc.
void draw_player_units(void);
void set_timer_frequency_for_heroes(unsigned int hz);


#endif
