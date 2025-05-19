#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "menu.h"
#include "gameState.h"
#include "xpms/menu_bg.xpm" // Background image
#include "xpms/play_button.xpm" // Play button image
#include "xpms/instructions_button.xpm" // Instructions button image
#include "xpms/exit_button.xpm" // Exit button image
#include "controllers/video/graphics.h" // For vg_draw_pixmap()


// Declare assets
xpm_image_t bg_menu, play_button, instructions_button, exit_button;

// Load the menu assets
void load_menu_assets() {
    xpm_load(bg_menu_xpm, XPM_8_8_8_8, &bg_menu);
    xpm_load(play_button_xpm, XPM_8_8_8_8, &play_button);
    xpm_load(instructions_button_xpm, XPM_8_8_8_8, &instructions_button);
    xpm_load(exit_button_xpm, XPM_8_8_8_8, &exit_button);
}

// Draw the menu
void draw_menu() {
    // Draw the background
    vg_draw_pixmap(bg_menu.bytes, 0, 0, bg_menu.width, bg_menu.height);

    // Draw the buttons
    vg_draw_pixmap(play_button.bytes, 300, 200, play_button.width, play_button.height); // Play button
    vg_draw_pixmap(instructions_button.bytes, 300, 300, instructions_button.width, instructions_button.height); // Instructions button
    vg_draw_pixmap(exit_button.bytes, 300, 400, exit_button.width, exit_button.height); // Exit button
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
