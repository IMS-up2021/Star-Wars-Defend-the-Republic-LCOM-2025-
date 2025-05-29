#include "timer_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "enemy.h"

//unsigned int enemy_spawn_timer = 0;


void timer_event_handler(gameState game_state) {
    switch (state) {
        case MAIN_MENU:
            draw_menu();
            break;
        case PLAYING:
            update_and_spawn_enemies();
            draw_game();
            draw_enemies();
            break;
        case INSTRUCTIONS:
            draw_instructions();
            break;
        case EXIT:
            break;
    }
}
