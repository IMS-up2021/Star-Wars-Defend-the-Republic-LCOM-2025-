#include "health.h"

xpm_image_t enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7, enemy8, enemy9, enemy10, enemy11;
xpm_image_t player1, player2, player3, player4, player5, player6, player7, player8, player9, player10, player11;

uint8_t *enemy_1, *enemy_2, *enemy_3, *enemy_4, *enemy_5, *enemy_6, *enemy_7, *enemy_8, *enemy_9, *enemy_10, *enemy_11;
uint8_t *player_1, *player_2, *player_3, *player_4, *player_5, *player_6, *player_7, *player_8, *player_9, *player_10, *player_11;

Player *player_health;
Player *enemy_health;

bool init_healthbar(void) {
    enemy_1 = xpm_load(enemy1_xpm, XPM_5_6_5, &enemy1);
    enemy_2 = xpm_load(enemy2_xpm, XPM_5_6_5, &enemy2);
    enemy_3 = xpm_load(enemy3_xpm, XPM_5_6_5, &enemy3);
    enemy_4 = xpm_load(enemy4_xpm, XPM_5_6_5, &enemy4);
    enemy_5 = xpm_load(enemy5_xpm, XPM_5_6_5, &enemy5);
    enemy_6 = xpm_load(enemy6_xpm, XPM_5_6_5, &enemy6);
    enemy_7 = xpm_load(enemy7_xpm, XPM_5_6_5, &enemy7);
    enemy_8 = xpm_load(enemy8_xpm, XPM_5_6_5, &enemy8);
    enemy_9 = xpm_load(enemy9_xpm, XPM_5_6_5, &enemy9);
    enemy_10 = xpm_load(enemy10_xpm, XPM_5_6_5, &enemy10);
    enemy_11 = xpm_load(enemy11_xpm, XPM_5_6_5, &enemy11);

    player_1 = xpm_load(player1_xpm, XPM_5_6_5, &player1);
    player_2 = xpm_load(player2_xpm, XPM_5_6_5, &player2);
    player_3 = xpm_load(player3_xpm, XPM_5_6_5, &player3);
    player_4 = xpm_load(player4_xpm, XPM_5_6_5, &player4);
    player_5 = xpm_load(player5_xpm, XPM_5_6_5, &player5);
    player_6 = xpm_load(player6_xpm, XPM_5_6_5, &player6);
    player_7 = xpm_load(player7_xpm, XPM_5_6_5, &player7);
    player_8 = xpm_load(player8_xpm, XPM_5_6_5, &player8);
    player_9 = xpm_load(player9_xpm, XPM_5_6_5, &player9);
    player_10 = xpm_load(player10_xpm, XPM_5_6_5, &player10);
    player_11 = xpm_load(player11_xpm, XPM_5_6_5, &player11);

    if (!enemy_1 || !player_1) {
        fprintf(stderr, "Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_2 || !player_2) {
        fprintf(stderr, "2Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_3 || !player_3) {
        fprintf(stderr, "3Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_4 || !player_4) {
        fprintf(stderr, "4Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_5 || !player_5) {
        fprintf(stderr, "5Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_6 || !player_6) {
        fprintf(stderr, "6Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_7 || !player_7) {
        fprintf(stderr, "7Error loading healthbar sprites\n");
        return false;
    }
    if (!enemy_8 || !player_8) {
        fprintf(stderr, "Error loading healthbar sprites\n");
        return false;
    }



    player_health = create_healthbar(50, 50, true);
    enemy_health = create_healthbar(830, 50, false);

    return true;
}

Player *create_healthbar(unsigned int x, unsigned int y, bool is_player) {
    Player *healthbar = (Player *)malloc(sizeof(Player));
    if (!healthbar) {
        perror("Failed to allocate memory for healthbar");
        return NULL;
    }
    if (is_player) {
        healthbar->x = x;
        healthbar->y = y;
        healthbar->sprite = player_1;
        healthbar->width = player1.width;
        healthbar->height = player1.height;
        healthbar->health = MAX_HEALTH;
    } else {
        healthbar->x = x;
        healthbar->y = y;
        healthbar->sprite = enemy_1;
        healthbar->width = enemy1.width;
        healthbar->height = enemy1.height;
        healthbar->health = MAX_HEALTH;
    }

    return healthbar;
}

void draw_healthbar(Player *healthbar, bool is_player) {
    if (!healthbar || !healthbar->sprite) return;

    uint16_t *pixels = (uint16_t *)healthbar->sprite;

    for (uint16_t y = 0; y < healthbar->height; y++) {
        for (uint16_t x = 0; x < healthbar->width; x++) {
            uint16_t color = pixels[y * healthbar->width + x];
            if (color == TRANSPARENT_COLOR) continue;
            vg_draw_pixel(healthbar->x + x, healthbar->y + y, color);
        }
    }
}

void update_healthbar(Player *healthbar, bool is_player) {
    if (!healthbar) return;

    if (is_player){
        if (healthbar->sprite == player_1 && healthbar->health == 90) {
           healthbar->sprite = player_2;
           healthbar->width = player2.width;
           healthbar->height = player2.height;
        } else if (healthbar->sprite == player_2 && healthbar->health == 80) {
            healthbar->sprite = player_3;
            healthbar->width = player3.width;
            healthbar->height = player3.height;
        } else if (healthbar->sprite == player_3 && healthbar->health == 70) {
            healthbar->sprite = player_4;
            healthbar->width = player4.width;
            healthbar->height = player4.height;
        } else if (healthbar->sprite == player_4 && healthbar->health == 60) {
            healthbar->sprite = player_5;
            healthbar->width = player5.width;
            healthbar->height = player5.height;
        } else if (healthbar->sprite == player_5 && healthbar->health == 50) {
            healthbar->sprite = player_6;
            healthbar->width = player6.width;
            healthbar->height = player6.height;
        } else if (healthbar->sprite == player_6 && healthbar->health == 40) {
            healthbar->sprite = player_7;
            healthbar->width = player7.width;
            healthbar->height = player7.height;
        } else if (healthbar->sprite == player_7 && healthbar->health == 30) {
            healthbar->sprite = player_8;
            healthbar->width = player8.width;
            healthbar->height = player8.height;
        } else if (healthbar->sprite == player_8 && healthbar->health == 20) {
            healthbar->sprite = player_9;
            healthbar->width = player9.width;
            healthbar->height = player9.height;
        } else if (healthbar->sprite == player_9 && healthbar->health == 10) {
            healthbar->sprite = player_10;
            healthbar->width = player10.width;
            healthbar->height = player10.height;
        } else if (healthbar->sprite == player_10 && healthbar->health == 0) {
            healthbar->sprite = player_11;
            healthbar->width = player11.width;
            healthbar->height = player11.height;
        }
    } else {
        if (healthbar->sprite == enemy_1 && healthbar->health == 90) {
           healthbar->sprite = enemy_2;
           healthbar->width = enemy2.width;
           healthbar->height = enemy2.height;
        } else if (healthbar->sprite == enemy_2 && healthbar->health == 80) {
            healthbar->sprite = enemy_3;
            healthbar->width = enemy3.width;
            healthbar->height = enemy3.height;
        } else if (healthbar->sprite == enemy_3 && healthbar->health == 70) {
            healthbar->sprite = enemy_4;
            healthbar->width = enemy4.width;
            healthbar->height = enemy4.height;
        } else if (healthbar->sprite == enemy_4 && healthbar->health == 60) {
            healthbar->sprite = enemy_5;
            healthbar->width = enemy5.width;
            healthbar->height = enemy5.height;
        } else if (healthbar->sprite == enemy_5 && healthbar->health == 50) {
            healthbar->sprite = enemy_6;
            healthbar->width = enemy6.width;
            healthbar->height = enemy6.height;
        } else if (healthbar->sprite == enemy_6 && healthbar->health == 40) {
            healthbar->sprite = enemy_7;
            healthbar->width = enemy7.width;
            healthbar->height = enemy7.height;
        } else if (healthbar->sprite == enemy_7 && healthbar->health == 30) {
            healthbar->sprite = enemy_8;
            healthbar->width = enemy8.width;
            healthbar->height = enemy8.height;
        } else if (healthbar->sprite == enemy_8 && healthbar->health == 20) {
            healthbar->sprite = enemy_9;
            healthbar->width = enemy9.width;
            healthbar->height = enemy9.height;
        } else if (healthbar->sprite == enemy_9 && healthbar->health == 10) {
            healthbar->sprite = enemy_10;
            healthbar->width = enemy10.width;
            healthbar->height = enemy10.height;
        } else if (healthbar->sprite == enemy_10 && healthbar->health == 0) {
            healthbar->sprite = enemy_11;
            healthbar->width = enemy11.width;
            healthbar->height = enemy11.height;
        }
    }
    
}

