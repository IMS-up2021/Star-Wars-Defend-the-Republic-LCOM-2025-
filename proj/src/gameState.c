#include "gameState.h"
#include "menu.h"
#include "gameplay.h"
#include "instructions.h"

// Initialize the current game state
gameState state = MAIN_MENU;

// Function to change the game state
void setGameState(gameState newState) {
    state = newState;
}

// Main game loop
void gameLoop() {
    bool running = true;

    while (running) {
        switch (state) {
            case MAIN_MENU:
                draw_menu(); // Render the main menu
                // handleMenuInput(); // Handle input for the menu
                break;

            case PLAYING:
                draw_game();
                // handleGameplayInput(); // Handle input for gameplay
                break;

            case INSTRUCTIONS:
                draw_instructions(); // Render the instructions screen
                // handleInstructionsInput(); // Handle input for instructions
                break;

            case EXIT:
                running = false; // Exit the game loop
                break;

            default:
                break;
        }
    }
}
