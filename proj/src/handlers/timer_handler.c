#include "timer_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "enemy.h"

#include "kbd_handler.h"
#include "characters.h"


void timer_event_handler(gameState game_state) {
    switch (state) {
        case MAIN_MENU:
            draw_menu();
            break;
        case PLAYING:
            update_and_spawn_enemies();
            switch(kbd_state){
                case 2:
                    draw_characters2();
                    break;
                case 3:
                    draw_characters3();
                    break;
                case 1:
                    draw_game();
                    break;
                default:
                    break;
            }
            draw_enemies();
            break;
        case INSTRUCTIONS:
            draw_instructions();
            break;
        case EXIT:
            break;
    }
}
