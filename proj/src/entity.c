#include "entity.h"
#include "gameState.h"
#include <math.h>
#include <lcom/lcf.h>
#include "controllers/video/graphics.h"
#include "xpms/mouse_cursor.xpm"

Cursor *cursor;
Position mouse_pos = {210, 330};

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

    vg_draw_scaled_pixmap(c->sprite, c->width, c->height, src_bpp_for_cursor, mouse_pos.x, mouse_pos.y, target_width, target_height)

    return 0;
}
