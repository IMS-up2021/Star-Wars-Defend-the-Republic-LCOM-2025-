#include "xpms/menu_bg.xpm"
#include "xpms/mouse_cursor.xpm"
#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "menu.h"
#include "entity.h"
#include "gameState.h"
#include "controllers/video/graphics.h"

extern Cursor *cursor;


// Draw the menu
void draw_menu() {
    // Load the menu assets
    xpm_image_t menu_bg;

    // Load the XPM images
    uint8_t *bg_menu = xpm_load(menu_bg_xpm, XPM_5_6_5, &menu_bg);

    const uint8_t xpm_source_bpp = 2; //5:6:5

    vg_draw_scaled_pixmap(bg_menu, menu_bg.width, menu_bg.height, xpm_source_bpp, 0, 0, mode_info.XResolution, mode_info.YResolution);

    if (draw_cursor(cursor)) printf("%s: draw_cursor(cursor) error\n", __func__);
}


// Handle menu input 
/*void handle_menu_input() {
    if (mouse_left_button_pressed()) {
        // Check if the mouse is over the Play button
        if (mouse_pos.x >= 300 && mouse_pos.x <= 300 + play_button.width &&
            mouse_pos.y >= 200 && mouse_pos.y <= 200 + play_button.height) {
            setGameState(PLAYING); // Transition to the PLAYING state
        }
        // Check if the mouse is over the Instructions button
        else if (mouse_pos.x >= 300 && mouse_pos.x <= 300 + instructions_button.width &&
                 mouse_pos.y >= 300 && mouse_pos.y <= 300 + instructions_button.height) {
            setGameState(INSTRUCTIONS); // Transition to the INSTRUCTIONS state
        }
        // Check if the mouse is over the Exit button
        else if (mouse_pos.x >= 300 && mouse_pos.x <= 300 + exit_button.width &&
                 mouse_pos.y >= 400 && mouse_pos.y <= 400 + exit_button.height) {
            setGameState(EXIT); // Exit the game
        }
    }
}*/
