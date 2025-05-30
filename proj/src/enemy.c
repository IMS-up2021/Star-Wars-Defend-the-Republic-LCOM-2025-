#include "enemy.h"
#include "gameState.h"

#include "xpms/enemy1/bg1_pose1.xpm"
#include "xpms/bg2_pose1.xpm"
#include "xpms/bg3_pose1.xpm"

uint8_t *e1_sprite_data, *e2_sprite_data, *e3_sprite_data;
xpm_image_t enemy1_img, enemy2_img, enemy3_img;

Character *active_enemies[MAX_ENEMIES];
int num_active_enemies = 0;
unsigned int enemy_spawn_tick_counter = 0;

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
    enemy->speed = 2;       // Velocidade padrão
    enemy->attack_range = 50; // Raio de ataque padrão
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

// Adiciona um inimigo à lista de inimigos ativos
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

// Lógica para decidir quando spawnar inimigos
void update_and_spawn_enemies(void) {
    enemy_spawn_tick_counter++;
    if (enemy_spawn_tick_counter >= ENEMY_SPAWN_DELAY) {
        enemy_spawn_tick_counter = 0; // Reset counter

        int enemy_type_to_spawn = rand() % 3; // Número de diferentes tipos de inimigos
        int position_index = rand() % 5;
        
        add_enemy_to_game(positions[position_index], enemy_type_to_spawn);
    }

    // TODO: Adicionar lógica de movimento dos inimigos aqui, se necessário
    // Por exemplo:
    // for (int i = 0; i < num_active_enemies; ++i) {
    //     active_enemies[i]->x_pos -= active_enemies[i]->speed;
    //     // Lógica para remover inimigos que saem do ecrã ou morrem
    // }
}

// Desenha todos os inimigos ativos
void draw_enemies(void) {
    for (int i = 0; i < num_active_enemies; i++) {
        Character *enemy = active_enemies[i];
        if (enemy && enemy->sprite) {
            unsigned scaled_width = (unsigned int)(enemy->width * 1.5f);
            unsigned scaled_height = (unsigned int)(enemy->height * 1.5f);

            vg_draw_scaled_pixmap(enemy->sprite, enemy->width, enemy->height, 2,
                                  enemy->x_pos, enemy->y_pos, 
                                  scaled_width, scaled_height);
        }
    }
}

bool init_enemies(void) {

    e1_sprite_data = xpm_load(bg1_run1_xpm, XPM_5_6_5, &enemy1_img);
    e2_sprite_data = xpm_load(en2_xpm, XPM_5_6_5, &enemy2_img);
    e3_sprite_data = xpm_load(en3_xpm, XPM_5_6_5, &enemy3_img);

    if (e1_sprite_data == NULL) printf("Failed to load e1 sprite\n");
    if (e2_sprite_data == NULL) printf("Failed to load e2 sprite\n");
    if (e3_sprite_data == NULL) printf("Failed to load e3 sprite\n");
    
    num_active_enemies = 0;
    enemy_spawn_tick_counter = 0;

    return (e1_sprite_data != NULL && e2_sprite_data != NULL && e3_sprite_data != NULL);
}

