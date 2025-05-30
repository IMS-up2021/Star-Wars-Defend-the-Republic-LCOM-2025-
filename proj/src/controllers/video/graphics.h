#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <lcom/lcf.h>
#include "VBE.h"

extern vbe_mode_info_t mode_info;
extern uint8_t* frame_buffer;

int (set_graphic_mode)(uint16_t submode);
int (set_text_mode)();
int (vg_swap_buffers)();
int (set_frame_buffer)(uint16_t mode);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_scaled_pixmap)(uint8_t *pixmap_data, uint16_t original_width, uint16_t original_height, uint8_t  src_bytes_per_pixel,
    uint16_t screen_target_x, uint16_t screen_target_y, uint16_t screen_target_width, uint16_t screen_target_height);

#endif /* __GRAPHICS_H */
