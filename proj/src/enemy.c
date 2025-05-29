#include "enemy.h"
#include "gameState.h"

#include "xpms/bg1_pose1.xpm"
#include "xpms/bg2_pose1.xpm"
#include "xpms/bg3_pose1.xpm"

uint8_t *e1, *e2, *e3;
xpm_image_t enemy1, enemy2, enemy3;

Character *e;

CharacterPos positions[5] = {
    {1238, 285},
    {1238, 415},
    {1238, 544},
    {1238, 665},
    {1238, 794}
};


Character *createEnemy(CharacterPos pos, int enemy_type) {
    Character *enemy = (Character *)malloc(sizeof(Character));
    switch (enemy_type) {
        case 1:
            e1 = xpm_load(en1, XPM_5_6_5, &enemy1);

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

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2, enemy->x_pos, enemy->x_pos, enemy->width, enemy->height);
            break;
        case 2:
            e2 = xpm_load(en2, XPM_5_6_5, &enemy2);
                
            enemy->x_pos = pos.x;
            enemy->y_pos = pos.y;
            enemy->width = enemy1.width;
            enemy->height = enemy1.height;
            enemy->damage = 10;
            enemy->health = 100;
            enemy->speed = 2;
            enemy->attack_range = 50;
            enemy->sprite = e2;
            enemy->enemy = true;

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2, enemy->x_pos, enemy->x_pos, enemy->width, enemy->height);
            break;
        case 3:
            e3 = xpm_load(en3, XPM_5_6_5, &enemy3);

            enemy->x_pos = pos.x;
            enemy->y_pos = pos.y;
            enemy->width = enemy1.width;
            enemy->height = enemy1.height;
            enemy->damage = 10;
            enemy->health = 100;
            enemy->speed = 2;
            enemy->attack_range = 50;
            enemy->sprite = e3;
            enemy->enemy = true;

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2, enemy->x_pos, enemy->x_pos, enemy->width, enemy->height);
            break;
        default:
            printf("Invalid enemy type\n");
            break;
    }
    return enemy;
}

void spawnEnemies() {
    int enemies = rand() % 3; // Number of different enemy types
    int idx = rand() % 5;
    e = createEnemy(positions[idx], enemies);
}
