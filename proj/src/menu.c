#include "xpms/menu_bg.xpm"
#include "xpms/mouse_cursor.xpm"
#include "xpms/background.xpm"
#include "xpms/Instructions.xpm"

#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "menu.h"
#include "entity.h"
#include "gameState.h"
#include "controllers/video/graphics.h"


extern Cursor *cursor;
const uint8_t xpm_source_bpp = 2; //5:6:5
uint8_t *bg_menu, *bg_game, *bg_instructions;
xpm_image_t menu_bg, game_bg, instructions_bg;

void load_menu_assets() {
    // Load the XPM images
    bg_menu = xpm_load(menu_bg_xpm, XPM_5_6_5, &menu_bg);
}

// Draw the menu
void draw_menu() {
    vg_draw_scaled_pixmap(bg_menu, menu_bg.width, menu_bg.height, xpm_source_bpp, 0, 0, mode_info.XResolution, mode_info.YResolution);
}


void load_instructions_assets() {
    bg_instructions = xpm_load(instructions_xpm, XPM_5_6_5, &instructions_bg);
    if (!bg_instructions) printf("Failed to load instructions XPM!\n");
}

void draw_instructions() {
    vg_draw_scaled_pixmap(bg_instructions, instructions_bg.width, instructions_bg.height, xpm_source_bpp, 0, 0, mode_info.XResolution, mode_info.YResolution);
}
