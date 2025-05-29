#ifndef PROJ_ENTITY_H
#define PROJ_ENTITY_H

#include <stdbool.h>
#include <lcom/lcf.h>



typedef struct {
    unsigned int pos_x;
    unsigned int pos_y;
    unsigned int width;
    unsigned int height;
    uint8_t *sprite;
} Cursor;


Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm);

bool (init_cursor)(void);

int draw_cursor(Cursor *cursor);

void update_mouse_location(int16_t delta_x, int16_t delta_y);

#endif
