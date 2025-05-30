#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "characters.h"
#include "gameState.h"
#include "controllers/video/graphics.h"

#include "characters.h"
#include "gameState.h" 


#include "xpms/char1/pose_1.xpm" 
#include "xpms/char2/h2_pose1.xpm"
#include "xpms/char3/h3_pose1.xpm"

uint8_t *pc1_sprite_data = NULL, *pc2_sprite_data = NULL, *pc3_sprite_data = NULL;
xpm_image_t pc1_img, pc2_img, pc3_img;

// --- Active Player Characters Array ---
Character *active_player_chars[MAX_PLAYER_CHARACTERS];
int num_active_player_chars = 0;


 extern CharacterPos player_spawn_positions[5];

bool init_player_units(void) {
    pc1_sprite_data = xpm_load(char_1, XPM_5_6_5, &pc1_img);
    pc2_sprite_data = xpm_load(h2_pose1, XPM_5_6_5, &pc2_img);
    pc3_sprite_data = xpm_load(h3_pose1, XPM_5_6_5, &pc3_img);

    if (!pc1_sprite_data) printf("Failed to load Player Char 1 sprite\n");
    if (!pc2_sprite_data) printf("Failed to load Player Char 2 sprite\n");
    if (!pc3_sprite_data) printf("Failed to load Player Char 3 sprite\n");

    num_active_player_chars = 0;

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

    bool success = false;
    switch (unit_type) {
        case PLAYER_CHAR_TYPE_1:
            if (pc1_sprite_data) {
                unit->width = pc1_img.width;
                unit->height = pc1_img.height;
                unit->sprite = pc1_sprite_data;
                unit->damage = 15; // Example stats
                unit->health = 120;
                unit->speed = 3;
                unit->attack_range = 60;
                success = true;
            }
            break;
        case PLAYER_CHAR_TYPE_2:
            if (pc2_sprite_data) {
                unit->width = pc2_img.width;
                unit->height = pc2_img.height;
                unit->sprite = pc2_sprite_data;
                unit->damage = 10;
                unit->health = 80;
                unit->speed = 4;
                unit->attack_range = 100; // e.g., a ranged unit
                success = true;
            }
            break;
        case PLAYER_CHAR_TYPE_3:
            if (pc3_sprite_data) {
                unit->width = pc3_img.width;
                unit->height = pc3_img.height;
                unit->sprite = pc3_sprite_data;
                unit->damage = 25; // e.g., a tanky unit
                unit->health = 200;
                unit->speed = 1;
                unit->attack_range = 40;
                success = true;
            }
            break;
        default:
            printf("Invalid player unit type: %d\n", unit_type);
            break;
    }

    if (!success || unit->sprite == NULL) {
        printf("Error: Sprite data not loaded or invalid for player unit type %d.\n", unit_type);
        free(unit);
        return NULL;
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
        active_player_chars[num_active_player_chars] = new_unit;
        num_active_player_chars++;
        printf("Player unit type %d spawned at (%u, %u).\n", unit_type, pos.x, pos.y);
    } else {
        printf("Failed to create player unit of type %d.\n", unit_type);
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
    printf("All player units drawn.\n");
}
