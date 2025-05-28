#include "entity.h"
#include "gameState.h"
#include <math.h>
#include <lcom/lcf.h>
#include "controllers/video/graphics.h"
#include "xpms/mouse_cursor.xpm"
#include "controllers/keyboardMouse/mouse.h"

Cursor *cursor;
Position mouse_pos = {890, 800};

uint16_t x_max = 1274;
uint16_t y_max = 938;

struct packet mouse_packet;

Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm) {
    // Carregar a imagem primeiro
    xpm_image_t image;
    uint8_t *sprite = xpm_load(xpm, XPM_5_6_5, &image);
    if (sprite == NULL) {
        printf("Error loading xpm image\n");
        return NULL;
    }

    // Alocar memória para o cursor
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    if (cursor == NULL) {
        printf("Error allocating memory for cursor\n");
        free(sprite); 
        return NULL;
    }

    // Inicializar os campos
    cursor->pos_x = pos_x;
    cursor->pos_y = pos_y;
    cursor->width = image.width;
    cursor->height = image.height;
    cursor->sprite = sprite;

    return cursor;
}


bool init_cursor(void) {
    cursor = create_cursor(mouse_pos.x, mouse_pos.y, (xpm_map_t)mouse_cursor_xpm);
    if (cursor == NULL) {
        printf("Error creating cursor\n");
        return false;
    }
    return true;
}

int draw_cursor(Cursor *c) {
    if (!c || !c->sprite) {
        printf("%s: NULL cursor or NULL sprite\n", __func__);
        return 1;
    }

    uint8_t src_bpp_for_cursor = 2;

    float scale_factor = 1.5f; // Para 50% maior

    uint16_t target_width = (uint16_t)(c->width * scale_factor);
    uint16_t target_height = (uint16_t)(c->height * scale_factor);

    vg_draw_scaled_pixmap(c->sprite, c->width, c->height, src_bpp_for_cursor, cursor->pos_x, cursor->pos_y, target_width, target_height);

    return 0;
}

void (update_mouse_location)(int16_t delta_x, int16_t delta_y){
    printf("Updating mouse location: delta_x = %d, delta_y = %d\n", delta_x, delta_y);
    int32_t temp_x = cursor->pos_x;
    int32_t temp_y = cursor->pos_y;
    float mouse_sensitivity = 1.0f; // Experimente valores como 1.5, 2.0, 2.5, etc.

    // ... dentro de update_mouse_location, antes de adicionar aos temp_x, temp_y
    delta_x = (int16_t)(delta_x * mouse_sensitivity);
    delta_y = (int16_t)(delta_y * mouse_sensitivity); // Cuidado com a inversão aqui se já a faz mais tarde

    temp_x += delta_x;
    temp_y -= delta_y;

    if (temp_x < 0) temp_x = 0;
    if (temp_x > x_max) temp_x = x_max; // Assumindo x_max é compatível com int32_t

    if (temp_y < 0) temp_y = 0;
    if (temp_y > y_max) temp_y = y_max; // Assumindo y_max é compatível com int32_t

    cursor->pos_x = (unsigned int)temp_x;
    cursor->pos_y = (unsigned int)temp_y;
}
