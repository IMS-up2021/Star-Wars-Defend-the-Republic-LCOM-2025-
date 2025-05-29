#include "timer_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "kbd_handler.h"
#include "characters.h"


void timer_event_handler(gameState game_state) {
    switch (state) {
        case MAIN_MENU:
            draw_menu();
            break;
        case PLAYING:
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
            break;
        case INSTRUCTIONS:
            draw_instructions();
            break;
        case EXIT:
            break;
    }
}
