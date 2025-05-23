#include "entity.h"
#include <math.h>
#include <lcom/lcf.h>
#include "controllers/video/graphics.h"



Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm) {
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));

    xpm_image_t image;
    uint8_t *sprite = xpm_load(xpm, XPM_5_6_5, &image);

    *cursor = (Cursor){pos_x, pos_y, image.width, image.height, sprite};

    return cursor;
}
