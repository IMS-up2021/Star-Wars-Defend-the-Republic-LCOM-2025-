
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
    xpm_image_t menu_bg; // play_button, instructions_button, exit_button;

    // Load the XPM images
    uint8_t *bg_menu = xpm_load(menu_bg_xpm, XPM_5_6_5, &menu_bg);
    const uint8_t xpm_source_bpp = 2; //5:6:5
    //uint8_t *b_play_pixmap = xpm_load(play_button_xpm, XPM_5_6_5, &play_button_info);
    //uint8_t *b_instructions_pixmap = xpm_load(instructions_button_xpm, XPM_5_6_5, &instructions_button_info);
    //uint8_t *b_exit_pixmap = xpm_load(exit_button_xpm, XPM_5_6_5, &exit_button_info);

    // Draw the background scaled to fit the entire screen
    vg_draw_scaled_pixmap(bg_menu, menu_bg.width, menu_bg.height, xpm_source_bpp, 0, 0, mode_info.XResolution, mode_info.YResolution);

    /*
    // Draw the buttons
    uint16_t button_target_width = 150;
    uint16_t button_spacing = 20; 

    // Calculate target heights preserving aspect ratio
    uint16_t play_button_target_height = (uint16_t)((float)button_target_width / play_button.width * play_button.height);
    uint16_t instr_button_target_height = (uint16_t)((float)button_target_width / instructions_button.width * instructions_button.height);
    uint16_t exit_button_target_height = (uint16_t)((float)button_target_width / exit_button.width * exit_button.height);

    // Calculate total width occupied by buttons and spacing
    uint16_t total_buttons_width = button_target_width * 3 + button_spacing * 2;

    // Calculate starting X to center the line of buttons horizontally
    uint16_t start_x_for_buttons = (mode_info.XResolution - total_buttons_width) / 2;
    if (start_x_for_buttons > mode_info.XResolution) start_x_for_buttons = 0; // prevent underflow if total_buttons_width is too large

    // Define a common Y position for the top of the buttons
    uint16_t max_button_height = play_button_target_height;
    if (instr_button_target_height > max_button_height) max_button_height = instr_button_target_height;
    if (exit_button_target_height > max_button_height) max_button_height = exit_button_target_height;
    
    uint16_t buttons_y_position = 300; 

    uint16_t current_x = start_x_for_buttons;

    //Play Button
    vg_draw_scaled_pixmap(b_play_pixmap, play_button.width, play_button.height, xpm_source_bpp, current_x, buttons_y_position, button_target_width, play_button_target_height);

    current_x += button_target_width + button_spacing;

    // Instructions Button
    vg_draw_scaled_pixmap(b_instructions_pixmap, instructions_button.width, instructions_button.height, xpm_source_bpp, current_x, buttons_y_position, button_target_width, instr_button_target_height);

    current_x += button_target_width + button_spacing;

    // Exit Button
    vg_draw_scaled_pixmap(b_exit_pixmap, exit_button.width, exit_button.height, xpm_source_bpp, current_x, buttons_y_position, button_target_width, exit_button_target_height);
*/
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
