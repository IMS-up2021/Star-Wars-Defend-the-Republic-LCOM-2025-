#include "timer_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "enemy.h"


void timer_event_handler(gameState game_state) {
    switch (state) {
        case MAIN_MENU:
            draw_menu();
            break;
        case PLAYING:
            draw_game();
            spawnEnemies();
            break;
        case INSTRUCTIONS:
            draw_instructions();
            break;
        case EXIT:
            break;
    }
}
