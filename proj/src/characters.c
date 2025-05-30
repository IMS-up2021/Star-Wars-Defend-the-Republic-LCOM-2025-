#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <stdlib.h>
#include <stdio.h>

#include "characters.h"
#include "gameState.h"
#include "health.h"
#include "controllers/video/graphics.h"

// Define constantes que faltavam
#define PLAYER_SPAWN_DELAY 180  // Exemplo: spawn a cada 3 segundos, com timer a 60 Hz
#define SCREEN_WIDTH 1275     // Define conforme a resolução do teu jogo


// Inclui os XPMs (assumindo os nomes corretos conforme os erros)
#include "xpms/char1/pose_1.xpm"
#include "xpms/char2/h2_pose1.xpm"
#include "xpms/char3/h3_pose1.xpm"

uint8_t *pc1_sprite_data = NULL, *pc2_sprite_data = NULL, *pc3_sprite_data = NULL;
xpm_image_t pc1_img, pc2_img, pc3_img;

// --- Active Player Characters Array ---
Character *active_player_chars[MAX_PLAYER_CHARACTERS];
int num_active_player_chars = 0;
unsigned int player_spawn_tick_counter = 0;

unsigned int timer_frequency_hz_hero = 60; // Default timer frequency


// Suponho que tens isto declarado no teu código ou header
extern CharacterPos player_spawn_positions[5];

bool init_player_units(void) {
    pc1_sprite_data = xpm_load(h1_pose_1, XPM_5_6_5, &pc1_img);
    pc2_sprite_data = xpm_load(h2_pose1, XPM_5_6_5, &pc2_img);
    pc3_sprite_data = xpm_load(h3_pose1, XPM_5_6_5, &pc3_img);

    if (!pc1_sprite_data) printf("Failed to load Player Char 1 sprite\n");
    if (!pc2_sprite_data) printf("Failed to load Player Char 2 sprite\n");
    if (!pc3_sprite_data) printf("Failed to load Player Char 3 sprite\n");

    num_active_player_chars = 0;
    player_spawn_tick_counter = 0;

    return (pc1_sprite_data && pc2_sprite_data && pc3_sprite_data);
}

Character *create_player_unit(CharacterPos pos, int unit_type) {
    Character *unit = (Character *)malloc(sizeof(Character));
    if (!unit) {
        perror("Failed to allocate memory for player unit");
        return NULL;
    }

    unit->x_pos = pos.x;
    unit->y_pos = pos.y;
    unit->enemy = false;

    switch (unit_type) {
        case 0: // PLAYER_CHAR_TYPE_1
            if (pc1_sprite_data) {
                unit->width = pc1_img.width;
                unit->height = pc1_img.height;
                unit->sprite = pc1_sprite_data;
                unit->damage = 15;
                unit->health = 120;
                unit-> pixels_per_sec = 120;
                unit->attack_range = 60;
            }
            break;
        case 1: // PLAYER_CHAR_TYPE_2
            if (pc2_sprite_data) {
                unit->width = pc2_img.width;
                unit->height = pc2_img.height;
                unit->sprite = pc2_sprite_data;
                unit->damage = 10;
                unit->health = 80;
                unit-> pixels_per_sec = 120;
                unit->attack_range = 100;
            }
            break;
        case 2: // PLAYER_CHAR_TYPE_3
            if (pc3_sprite_data) {
                unit->width = pc3_img.width;
                unit->height = pc3_img.height;
                unit->sprite = pc3_sprite_data;
                unit->damage = 25;
                unit->health = 200;
                unit-> pixels_per_sec = 120;
                unit->attack_range = 40;
            }
            break;
        default:
            printf("Invalid player unit type: %d\n", unit_type);
            break;
    }

    return unit;
}

void add_player_unit_to_game(CharacterPos pos, int unit_type) {
    if (num_active_player_chars >= MAX_PLAYER_CHARACTERS) {
        printf("Max player characters reached.\n");
        return;
    }

    Character *new_unit = create_player_unit(pos, unit_type);
    if (new_unit) {
        active_player_chars[num_active_player_chars++] = new_unit;
        printf("Player unit type %d spawned at (%u, %u).\n", unit_type, pos.x, pos.y);
    } else {
        printf("Failed to create player unit of type %d.\n", unit_type);
    }
}

void update_and_spawn_player_units(void) {
  if (timer_frequency_hz_hero == 0) return;

    for (int i = 0; i < num_active_player_chars;) {
        Character *unit = active_player_chars[i];
        if (!unit) {
            i++;
            continue;
        }

        unsigned int pixels_to_move = unit->pixels_per_sec / timer_frequency_hz_hero; // Ajusta se quiseres por timer_frequency
        unit->x_pos += pixels_to_move; // Exemplo: player anda para a direita (contrário do inimigo)

        if ((int)unit->x_pos > SCREEN_WIDTH) { // Saiu do ecrã, remove
            free(unit);
            for (int j = i; j < num_active_player_chars - 1; j++) {
                active_player_chars[j] = active_player_chars[j + 1];
            }
            active_player_chars[num_active_player_chars - 1] = NULL;
            num_active_player_chars--;
        } else {
            i++;
        }
    }
}

void draw_player_units(void) {
    for (int i = 0; i < num_active_player_chars; i++) {
        Character *unit = active_player_chars[i];
        if (unit && unit->sprite) {
            uint16_t *pixels = (uint16_t *)unit->sprite;
            for (uint16_t y = 0; y < unit->height; y++) {
                for (uint16_t x = 0; x < unit->width; x++) {
                    uint16_t color = pixels[y * unit->width + x];
                    if (color == TRANSPARENT_COLOR) continue;
                    vg_draw_pixel(unit->x_pos + x, unit->y_pos + y, color);
                }
            }
        }
    }
}

void set_timer_frequency_for_heroes(unsigned int hz) {
    timer_frequency_hz_hero = hz;
}
