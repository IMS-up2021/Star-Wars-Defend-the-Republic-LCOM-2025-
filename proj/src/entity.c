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
        free(sprite); // liberar a imagem se não puder alocar o cursor
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
