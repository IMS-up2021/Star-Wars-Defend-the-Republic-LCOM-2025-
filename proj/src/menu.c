
#include "xpms/menu_bg.xpm"
#include "xpms/play_button.xpm"
#include "xpms/instructions_button.xpm"
#include "xpms/exit_button.xpm"
#include "xpms/test.h"

#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "menu.h"
#include "gameState.h"
#include "controllers/video/graphics.h"



// Draw the menu
void draw_menu() {
    xpm_image_t menu_bg;
    uint8_t *bg_menu = xpm_load(menu_bg_xpm, XPM_5_6_5, &menu_bg);
    if (bg_menu == NULL) {
        printf("Error loading background menu\n");
        return;
    }

    // Draw the background
    vg_draw_pixmap(bg_menu, 0, 0, menu_bg.width, menu_bg.height);

   
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
