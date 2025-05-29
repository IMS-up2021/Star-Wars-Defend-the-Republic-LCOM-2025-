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
                    load_characters2_assets();
                    draw_characters2();
                    break;
                case 3:
                    load_characters3_assets();
                    draw_characters3();
                    break;
                default:
                    load_game_assets();
                    draw_game();
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
