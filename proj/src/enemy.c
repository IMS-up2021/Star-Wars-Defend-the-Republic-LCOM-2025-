#include "enemy.h"
#include "gameState.h"
#include <lcom/lcf.h>

#include "xpms/bg1_pose1.xpm"
#include "xpms/bg2_pose1.xpm"
#include "xpms/bg3_pose1.xpm"

uint8_t *e1_sprite_data, *e2_sprite_data, *e3_sprite_data;
xpm_image_t enemy1_img, enemy2_img, enemy3_img;

Character *active_enemies[MAX_ENEMIES];
int num_active_enemies = 0;
unsigned int enemy_spawn_tick_counter = 0;

unsigned int timer_frequency_hz = 60; // Default timer frequency

CharacterPos positions[5] = {
    {1200, 190},
    {1200, 320},
    {1200, 449},
    {1200, 570},
    {1200, 699}
};

Character *createEnemy(CharacterPos pos, int enemy_type) {
    Character *enemy = (Character *)malloc(sizeof(Character));
    if (!enemy) {
        perror("Failed to allocate memory for enemy");
        return NULL;
    }

    enemy->x_pos = pos.x;
    enemy->y_pos = pos.y;
    enemy->damage = 10;
    enemy->health = 100;
    enemy->pixels_per_sec = 120;
    enemy->attack_range = 50;
    enemy->enemy = true;

    bool success = false;
    switch (enemy_type) {
        case 0:
            if (e1_sprite_data) {
                enemy->width = enemy1_img.width;
                enemy->height = enemy1_img.height;
                enemy->sprite = e1_sprite_data;
                success = true;
            }
            break;
        case 1:
            if (e2_sprite_data) {
                enemy->width = enemy2_img.width;
                enemy->height = enemy2_img.height;
                enemy->sprite = e2_sprite_data;
                success = true;
            }
            break;
        case 2:
            if (e3_sprite_data) {
                enemy->width = enemy3_img.width;
                enemy->height = enemy3_img.height;
                enemy->sprite = e3_sprite_data;
                success = true;
            }
            break;
        default:
            printf("Invalid enemy type: %d\n", enemy_type);
            break;
    }

    if (!success || enemy->sprite == NULL) {
        printf("Error: Sprite data not loaded or invalid for enemy type %d.\n", enemy_type);
        free(enemy);
        return NULL;
    }

    return enemy;
}

void add_enemy_to_game(CharacterPos pos, int enemy_type) {
    if (num_active_enemies >= MAX_ENEMIES) return;

    Character *new_enemy = createEnemy(pos, enemy_type);
    if (new_enemy) {
        active_enemies[num_active_enemies] = new_enemy;
        num_active_enemies++;
    } else {
        printf("Failed to create enemy of type %d.\n", enemy_type);
    }
}

void update_and_spawn_enemies(void) {
    if (timer_frequency_hz == 0) return;

    enemy_spawn_tick_counter++;
    if (enemy_spawn_tick_counter >= ENEMY_SPAWN_DELAY) {
        enemy_spawn_tick_counter = 0;

        int enemy_type_to_spawn = rand() % 3;
        int position_index = rand() % 5;

        add_enemy_to_game(positions[position_index], enemy_type_to_spawn);
    }

    for (int i = 0; i < num_active_enemies;) {
        Character *enemy = active_enemies[i];
        if (!enemy) {
            i++;
            continue;
        }

        unsigned int pixels_to_move = enemy->pixels_per_sec / timer_frequency_hz;
        enemy->x_pos -= pixels_to_move;

        if ((int)(enemy->x_pos + enemy->width) < 0) {
            free(enemy);
            for (int j = i; j < num_active_enemies - 1; j++) {
                active_enemies[j] = active_enemies[j + 1];
            }
            active_enemies[num_active_enemies - 1] = NULL;
            num_active_enemies--;
        } else {
            i++;
        }
    }
}

void draw_enemies(void) {
    for (int i = 0; i < num_active_enemies; i++) {
        Character *enemy = active_enemies[i];
        if (enemy && enemy->sprite) {
            uint16_t *pixels = (uint16_t *)enemy->sprite;

            for (uint16_t y = 0; y < enemy->height; y++) {
                for (uint16_t x = 0; x < enemy->width; x++) {
                    uint16_t color = pixels[y * enemy->width + x];
                    if (color == TRANSPARENT_COLOR) continue;
                    vg_draw_pixel(enemy->x_pos + x, enemy->y_pos + y, color);
                }
            }
        }
    }
}

bool init_enemies(void) {
    e1_sprite_data = xpm_load(bg1_pose1_xpm, XPM_5_6_5, &enemy1_img);
    e2_sprite_data = xpm_load(bg2_pose1_xpm, XPM_5_6_5, &enemy2_img);
    e3_sprite_data = xpm_load(bg3_pose1_xpm, XPM_5_6_5, &enemy3_img);

    if (e1_sprite_data == NULL) printf("Failed to load e1 sprite\n");
    if (e2_sprite_data == NULL) printf("Failed to load e2 sprite\n");
    if (e3_sprite_data == NULL) printf("Failed to load e3 sprite\n");

    num_active_enemies = 0;
    enemy_spawn_tick_counter = 0;

    return (e1_sprite_data != NULL && e2_sprite_data != NULL && e3_sprite_data != NULL);
}

void set_timer_frequency_for_enemies(unsigned int hz) {
    timer_frequency_hz = hz;
}
