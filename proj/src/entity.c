/**
 * @file entity.c
 * @brief Implements functionality related to game entities, specifically the mouse cursor.
 */

#include "entity.h"
#include "gameState.h"
#include <math.h>
#include <lcom/lcf.h>
#include "controllers/video/graphics.h"
#include "xpms/mouse_cursor.xpm"
#include "xpms/button_cursor.xpm" 
#include "controllers/keyboardMouse/mouse.h"

Cursor *cursor;
Position mouse_pos = {260, 140};

uint16_t x_max = 1274;
uint16_t y_max = 988;

struct packet mouse_packet;

/**
 * @brief Creates a new cursor object.
 * Allocates memory for a Cursor struct, loads its XPM sprite, and initializes its position.
 * @param pos_x The initial x-coordinate for the cursor.
 * @param pos_y The initial y-coordinate for the cursor.
 * @param xpm The XPM map (sprite) for the cursor.
 * @return A pointer to the newly created Cursor, or NULL on failure (memory allocation or XPM loading).
 */
Cursor *create_cursor(unsigned int pos_x, unsigned int pos_y, xpm_map_t xpm) {
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    if (cursor == NULL) {
        printf("Error allocating memory for cursor\n");
        return NULL;
    }

    cursor->sprite = xpm_load(xpm, XPM_5_6_5, &cursor->img);
    if (cursor->sprite == NULL) {
        printf("Error loading xpm image\n");
        free(cursor);
        return NULL;
    }

    cursor->pos_x = pos_x;
    cursor->pos_y = pos_y;
    cursor->width = cursor->img.width;
    cursor->height = cursor->img.height;

    return cursor;
}

/**
 * @brief Initializes the mouse cursor.
 * Creates the cursor using `create_cursor` with predefined settings.
 * Sets the global `x_max` and `y_max` based on `mode_info`.
 * @return True if the cursor was successfully initialized, false otherwise.
 */
bool init_cursor(void) {
    cursor = create_cursor(mouse_pos.x, mouse_pos.y, (xpm_map_t)mouse_cursor_xpm);

    if (cursor == NULL) {
        printf("Error creating cursor\n");
        return false;
    }
    return true;
}

/**
 * @brief Draws the specified cursor on the screen.
 * @param c Pointer to the Cursor object to draw.
 * @return 0 on success, 1 if the cursor or its sprite is NULL.
 */
int draw_cursor(Cursor *c) {
    if (!c || !c->sprite) return 1;

    uint16_t *pixels = (uint16_t *)c->img.bytes;

    for (uint16_t y = 0; y < c->img.height; y++) {
        for (uint16_t x = 0; x < c->img.width; x++) {
            uint16_t color = pixels[y * c->img.width + x];
            if (color == TRANSPARENT_COLOR) continue;
            vg_draw_pixel(c->pos_x + x, c->pos_y + y, color);
        }
    }

    return 0;
}

/**
 * @brief Updates the mouse cursor's location based on delta movements.
 * Ensures the cursor stays within the screen boundaries defined by `x_max` and `y_max`.
 * @param delta_x The change in x-coordinate.
 * @param delta_y The change in y-coordinate (note: typically inverted from mouse hardware).
 */
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

}
