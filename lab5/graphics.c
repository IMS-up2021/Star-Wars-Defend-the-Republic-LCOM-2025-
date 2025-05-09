#include <lcom/lcf.h>
#include "graphics.h"

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

// vg_init() is given
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

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (unsigned int i = 0; i < height; i++) {
        if (vg_draw_hline(x, y + 1, width, color) != 0){
            vg_exit();
            return 1;
        }
    }
    return 0;
}

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

    xpm_image_t img;
  
    uint16_t *colors = (uint16_t*)xpm_load(xpm, XPM_5_6_5, &img);
  
    for (int h = 0 ; h < img.height ; h++) {
      for (int w = 0 ; w < img.width ; w++) {
        // printf("%u",*colors); -> to check errors in colors
        if(*colors == 0) {
          colors++;
          continue;
        }
        if (vg_draw_pixel(x + w, y + h, *colors) != 0) return 1;
        colors++; 
      }
    }
    return 0;
  }

int (normalize_color)(uint32_t color, uint32_t *new_color){
    if (mode_info.BitsPerPixel == 32) *new_color = color;
    else *new_color = color & (BIT(mode_info.BitsPerPixel) - 1);
    return 0;
}


uint32_t (direct_mode)(uint32_t R, uint32_t G, uint32_t B) {
    return (R << mode_info.RedFieldPosition) | (G << mode_info.GreenFieldPosition) | (B << mode_info.BlueFieldPosition);
}

uint32_t (indexed_mode)(uint16_t col, uint16_t row, uint8_t step, uint32_t first, uint8_t n){
    return (first + (row * n + col) * step) % (1 << mode_info.BitsPerPixel); 
}

uint32_t (Red)(unsigned j, uint8_t step, uint32_t first) {
    return(R(first) + j * step) % (1 << mode_info.BitsPerPixel);
}

uint32_t (Green)(unsigned j, uint8_t step, uint32_t first) {
    return(G(first) + j * step) % (1 << mode_info.BitsPerPixel);
}

uint32_t (Blue)(unsigned j, unsigned i, uint8_t step, uint32_t first) {
    return(B(first) + j * step) % (1 << mode_info.BitsPerPixel);
} 

uint32_t (R)(uint32_t first) {
    return ((1 << mode_info.RedMaskSize) - 1) & (first >> mode_info.RedFieldPosition);
}

uint32_t (G)(uint32_t first){
    return ((1 << mode_info.GreenMaskSize) - 1) & (first >> mode_info.GreenFieldPosition);
}



uint32_t (B)(uint32_t first) {
    return ((1 << mode_info.BlueMaskSize) - 1) & (first >> mode_info.BlueFieldPosition);
}
