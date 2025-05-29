#include "enemy.h"
#include "gameState.h"

#include "xpms/bg1_pose1.xpm"
#include "xpms/bg2_pose1.xpm"
#include "xpms/bg3_pose1.xpm"

uint8_t *e1, *e2, *e3;
xpm_image_t enemy1, enemy2, enemy3;


CharacterPos positions[5] = {
    {1200, 285},
    {1200, 415},
    {1200, 544},
    {1200, 665},
    {1200, 794}
};


Character *createEnemy(CharacterPos pos, int enemy_type) {
    Character *enemy = (Character *)malloc(sizeof(Character));
    switch (enemy_type) {
        case 0:

            enemy->x_pos = pos.x;
            enemy->y_pos = pos.y;
            enemy->width = enemy1.width;
            enemy->height = enemy1.height;
            enemy->damage = 10;
            enemy->health = 100;
            enemy->speed = 2;
            enemy->attack_range = 50;
            enemy->sprite = e1;
            enemy->enemy = true;

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2, enemy->x_pos, enemy->y_pos, enemy->width * 1.5, enemy->height * 1.5);
            break;
        case 1:
                
            enemy->x_pos = pos.x;
            enemy->y_pos = pos.y;
            enemy->width = enemy2.width;
            enemy->height = enemy2.height;
            enemy->damage = 10;
            enemy->health = 100;
            enemy->speed = 2;
            enemy->attack_range = 50;
            enemy->sprite = e2;
            enemy->enemy = true;

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2, enemy->x_pos, enemy->y_pos, enemy->width * 1.5, enemy->height * 1.5);
            break;
        case 2:

            enemy->x_pos = pos.x;
            enemy->y_pos = pos.y;
            enemy->width = enemy3.width;
            enemy->height = enemy3.height;
            enemy->damage = 10;
            enemy->health = 100;
            enemy->speed = 2;
            enemy->attack_range = 50;
            enemy->sprite = e3;
            enemy->enemy = true;

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2, enemy->x_pos, enemy->y_pos, enemy->width * 1.5, enemy->height * 1.5);
            break;
        default:
            printf("Invalid enemy type\n");
            break;
    }
    if (enemy->sprite == NULL) {
        printf("Error loading enemy sprite\n");
        free(enemy);
        return NULL;
    }
    printf("Enemy created at position (%u, %u) with type %d\n", enemy->x_pos, enemy->y_pos, enemy_type);
    return enemy;
}

void spawnEnemies(void) {
    int enemies = rand() % 3; // Number of different enemy types
    int idx = rand() % 5;
    createEnemy(positions[idx], enemies);
}

bool init_enemies(void) {
    e1 = xpm_load(en1, XPM_5_6_5, &enemy1);
    e2 = xpm_load(en2, XPM_5_6_5, &enemy2);
    e3 = xpm_load(en3, XPM_5_6_5, &enemy3);

    return (e1 != NULL && e2 != NULL && e3 != NULL);
}
