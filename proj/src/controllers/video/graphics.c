#include <lcom/lcf.h>
#include "./graphics.h"

#define BIT(n) (1 << (n))

vbe_mode_info_t mode_info; 

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
    
    for(unsigned int i = 0; i < BytesPerPixel; i++){
        frame_buffer[index + i] = (color >> (8 * i)) & 0xFF;
    }

    return 0;
}

int (normalize_color)(uint32_t color, uint32_t *new_color){
    if (mode_info.BitsPerPixel == 32) *new_color = color;
    else *new_color = color & (BIT(mode_info.BitsPerPixel) - 1);
    return 0;
}

int vg_draw_pixmap(uint8_t *pixmap, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    if (mode_info.BitsPerPixel == 16) {
        // 16bpp direct color (5:6:5)
        uint16_t* pix = (uint16_t*)pixmap; 
        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
               uint16_t color16 = pix[i * width + j];
               vg_draw_pixel(x + j, y + i, (uint32_t)color16);

               if(vg_draw_pixel(x + j, y + i, (uint32_t)color16) != 0){
                printf("Error drawing pixel at (%u, %u) for pixmap. \n", x + y, y + i);
               }
            }
        }
    } else {
        printf("Unsupported color depth: %d\n", mode_info.BitsPerPixel);
        return 1;
    }
    return 0;
}


