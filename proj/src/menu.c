
#include "xpms/menu_bg.xpm"
#include "xpms/play_button.xpm"
#include "xpms/instructions_button.xpm"
#include "xpms/exit_button.xpm"


#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "menu.h"
#include "gameState.h"
#include "controllers/video/graphics.h"

/*
// Declare assets
xpm_image_t menu_bg, play_button, instructions_button, exit_button;
uint8_t *bg_menu, *b_play, *b_instructions, *b_exit;

// Load the menu assets
void load_menu_assets() {
    bg_menu = xpm_load(menu_bg_xpm, XPM_5_6_5, &menu_bg);
    uint8_t *b_play = xpm_load(play_button_xpm, XPM_8_8_8_8, &play_button);
    uint8_t *b_instructions = xpm_load(instructions_button_xpm, XPM_8_8_8_8, &instructions_button);
    uint8_t *b_exit = xpm_load(exit_button_xpm, XPM_8_8_8_8, &exit_button);
}

// Draw the menu
void draw_menu() {
    // Draw the background
    vg_draw_pixmap(bg_menu, 0, 0, menu_bg.width, menu_bg.height);

    // Draw the buttons
    vg_draw_pixmap(b_play, 300, 200, play_button.width, play_button.height); // Play button
    vg_draw_pixmap(b_instructions, 300, 300, instructions_button.width, instructions_button.height); // Instructions button
    vg_draw_pixmap(b_exit, 300, 400, exit_button.width, exit_button.height); // Exit button
}


*/


// Draw the menu
void draw_menu() {
    // Load the menu assets
    xpm_image_t menu_bg; //, play_button, instructions_button, exit_button;

    // Load the XPM images
    uint8_t *bg_menu = xpm_load(menu_bg_xpm, XPM_5_6_5, &menu_bg);
    // uint8_t *b_play = xpm_load(play_button_xpm, XPM_5_6_5, &play_button);
    // uint8_t *b_instructions = xpm_load(instructions_button_xpm, XPM_5_6_5, &instructions_button);
    // uint8_t *b_exit = xpm_load(exit_button_xpm, XPM_5_6_5, &exit_button);


    // Draw the background
    vg_draw_pixmap(bg_menu, 0, 0, menu_bg.width, menu_bg.height);

    // Draw the buttons
    // vg_draw_pixmap(b_play, 300, 200, play_button.width, play_button.height); // Play button
    // vg_draw_pixmap(b_instructions, 300, 300, instructions_button.width, instructions_button.height); // Instructions button
    // vg_draw_pixmap(b_exit, 300, 400, exit_button.width, exit_button.height); // Exit button

   
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
