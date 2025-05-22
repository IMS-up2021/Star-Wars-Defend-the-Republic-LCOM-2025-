#include <lcom/lcf.h>
#include "./graphics.h"

#define BIT(n) (1 << (n))

vbe_mode_info_t mode_info; 
uint8_t *video_mem; 
uint8_t *frame_buffer;

// set minix to graphic mode
int (set_graphic_mode)(uint16_t submode){
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10;
    reg86.ah = 0x4F;
    reg86.al = 0x02;
    reg86.bx = submode | BIT(14);

    if (sys_int86(&reg86) != 0) {
        printf("Set graphic mode failed\n");
        return 1;
    }
    
    return 0;
}

// Set minix to text mode
int (set_text_mode)() {
    reg86_t reg86;

    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ah = 0x00;
    reg86.al = 0x03;
    reg86.bx = 0x0000;

    if (sys_int86(&reg86) != 0) {
        printf("Set text mode failed\n");
        return 1;
    }

    return 0;
}

int (set_frame_buffer)(uint16_t mode){

    memset(&mode_info, 0, sizeof(mode_info));
    if(vbe_get_mode_info(mode, &mode_info)) return 1;

    printf("BitsPerPixel: %d\n", mode_info.BitsPerPixel);
    printf("Red: Size %d, Pos %d\n", mode_info.RedMaskSize, mode_info.RedFieldPosition);
    printf("Green: Size %d, Pos %d\n", mode_info.GreenMaskSize, mode_info.GreenFieldPosition);
    printf("Blue: Size %d, Pos %d\n", mode_info.BlueMaskSize, mode_info.BlueFieldPosition);
  
    uint8_t bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;    unsigned int frame_size = mode_info.XResolution * mode_info.YResolution * bytes_per_pixel;
    
    struct minix_mem_range physic_addresses;
    physic_addresses.mr_base = mode_info.PhysBasePtr; 
    physic_addresses.mr_limit = physic_addresses.mr_base + frame_size; 
    
    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physic_addresses)) {
      printf("Physical memory allocation error\n");
      return 1;
    }
  
    frame_buffer = vm_map_phys(SELF, (void*) physic_addresses.mr_base, frame_size);
    if (frame_buffer == NULL) {
      printf("Virtual memory allocation error");
      return 1;
    }
  
    return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x >= mode_info.XResolution || y >= mode_info.YResolution) return 1;
    unsigned int BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;
    unsigned int index = (mode_info.XResolution * y + x) * BytesPerPixel;
    
    memcpy(&frame_buffer[index], &color, BytesPerPixel);

    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (unsigned int i = 0; i < len; i++) {
        if (vg_draw_pixel(x + 1, y, color) != 0) return 1;
    }
    return 0;
}

int (normalize_color)(uint32_t color, uint32_t *new_color){
    if (mode_info.BitsPerPixel == 32) *new_color = color;
    else *new_color = color & (BIT(mode_info.BitsPerPixel) - 1);
    return 0;
}

int vg_draw_pixmap(uint8_t *pixmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    // Calculate BytesPerPixel
    uint8_t bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    uint32_t screen_pitch = mode_info.XResolution * bytes_per_pixel; // Bytes per screen line

    for (uint16_t current_y = 0; current_y < height; ++current_y) {
        uint16_t screen_y_coord = y + current_y;

        // if current row is outside screen, skip it
        if (screen_y_coord >= mode_info.YResolution) {
            break; 
        }

        // Pointer to the start of the current row in the framebuffer
        uint8_t *dest_row_start = frame_buffer + screen_y_coord * screen_pitch;

        if (mode_info.BitsPerPixel == 16) {
            // 16bpp direct color (e.g., RGB565)
            uint16_t *src_row = (uint16_t *)(pixmap + current_y * width * 2); // 2 bytes per pixel
            uint16_t *dest_pixel_ptr_16 = (uint16_t *)(dest_row_start + x * 2);

            for (uint16_t current_x = 0; current_x < width; ++current_x) {
                uint16_t screen_x_coord = x + current_x;

                if (screen_x_coord >= mode_info.XResolution) {
                    break;
                }

                dest_pixel_ptr_16[current_x] = src_row[current_x];
            }
        } 
        else if (mode_info.BitsPerPixel == 32) {
            uint32_t *src_row = (uint32_t *)(pixmap + current_y * width * 4); // 4 bytes per pixel
            uint32_t *dest_pixel_ptr_32 = (uint32_t *)(dest_row_start + x * 4);

            for (uint16_t current_x = 0; current_x < width; ++current_x) {
                uint16_t screen_x_coord = x + current_x;

                if (screen_x_coord >= mode_info.XResolution) {
                    break;
                }

                uint32_t pixmap_color32 = src_row[current_x];

                uint8_t r_in = (pixmap_color32 >> 16) & 0xFF;
                uint8_t g_in = (pixmap_color32 >> 8) & 0xFF;
                uint8_t b_in = pixmap_color32 & 0xFF;

                uint32_t framebuffer_color32 = 0;

                framebuffer_color32 |= ((uint32_t)(r_in >> (8 - mode_info.RedMaskSize))) << mode_info.RedFieldPosition;
                framebuffer_color32 |= ((uint32_t)(g_in >> (8 - mode_info.GreenMaskSize))) << mode_info.GreenFieldPosition;
                framebuffer_color32 |= ((uint32_t)(b_in >> (8 - mode_info.BlueMaskSize))) << mode_info.BlueFieldPosition;
              

                dest_pixel_ptr_32[current_x] = framebuffer_color32;
            }
        } else {
            printf("Unsupported color depth for optimized pixmap drawing: %d\n", mode_info.BitsPerPixel);
            return 1; 
        }
    }
    return 0;
}


