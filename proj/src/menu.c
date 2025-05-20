
#include "xpms/menu_bg.xpm"
#include "xpms/play_button.xpm"
#include "xpms/instructions_button.xpm"
#include "xpms/exit_button.xpm"
#include "xpms/test.xpm"

#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "menu.h"
#include "gameState.h"
#include "controllers/video/graphics.h"

// Draw the menu
void draw_menu() {
    // Load the menu assets
    xpm_image_t img;
    uint8_t *colors = xpm_load(test_xpm, XPM_INDEXED, &img);
    if (!colors) {
        printf("Failed to load test_xpm!\n");
        return;
    }
    // Only draw if loaded successfully
    print_xpm(test_xpm, 0, 0);

   /* print_xpm(menu_bg_xpm, 0, 0);
    print_xpm(play_button_xpm, 300, 200);
    print_xpm(instructions_button_xpm, 300, 300);
    print_xpm(exit_button_xpm, 300, 400);*/
   
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
