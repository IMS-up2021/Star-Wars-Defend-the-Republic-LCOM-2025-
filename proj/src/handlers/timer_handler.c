#include "timer_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "enemy.h"

#include "kbd_handler.h"
#include "characters.h"

#include "game.h"

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

            switch (play_state) {
                case PLAY_PAUSED:
					timer_set_frequency(0, 1);
          			break;
                case PLAY_NORMAL:
					timer_set_frequency(0, 60); // Normal game speed
                    break;
                case PLAY_FAST:
					timer_set_frequency(0, 120); // Fast game speed
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
