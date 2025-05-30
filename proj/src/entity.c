#include "entity.h"
#include "gameState.h"
#include <math.h>
#include <lcom/lcf.h>
#include "controllers/video/graphics.h"
#include "xpms/mouse_cursor.xpm"
#include "controllers/keyboardMouse/mouse.h"



Cursor *cursor;
Position mouse_pos = {260, 140};

uint16_t x_max = 1274;
uint16_t y_max = 988;

struct packet mouse_packet;

Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm) {
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    if (cursor == NULL) {
        printf("Error allocating memory for cursor\n");
        return NULL;
    }

    if (cursor->sprite == NULL) {
        printf("Error loading xpm image\n");
        free(cursor);
        return NULL;
    }

    cursor->pos_x = pos_x;
    cursor->pos_y = pos_y;
    cursor->sprite = xpm_load(xpm, XPM_DIRECT, &cursor->img);


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
    if (!c || !c->sprite) return 1;

    uint32_t *pixels = (uint32_t *)c->img.bytes;

    for (uint16_t y = 0; y < c->img.height; y++) {
        for (uint16_t x = 0; x < c->img.width; x++) {
            uint32_t color = pixels[y * c->img.width + x];
            if (color == TRANSPARENT_COLOR) continue; // define o que consideras transparente
            vg_draw_pixel(c->pos_x + x, c->pos_y + y, color);
        }
    }

    return 0;
}



void (update_mouse_location)(int16_t delta_x, int16_t delta_y){
    int32_t temp_x = cursor->pos_x;
    int32_t temp_y = cursor->pos_y;

    temp_x += delta_x;
    temp_y -= delta_y;

    if (temp_x < 0) temp_x = 0;
    if (temp_x > x_max) temp_x = x_max;

    if (temp_y < 0) temp_y = 0;
    if (temp_y > y_max) temp_y = y_max;

    cursor->pos_x = (unsigned int)temp_x;
    cursor->pos_y = (unsigned int)temp_y;

    printf("Cursor position updated: x = %u, y = %u\n", cursor->pos_x, cursor->pos_y);

}
