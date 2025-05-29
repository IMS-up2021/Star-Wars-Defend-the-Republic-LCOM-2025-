#include <math.h>
#include "mouse_handler.h"
#include "menu.h"
#include "gameState.h"
#include "entity.h"


Cursor *cursor;
Position mouse_pos;


void mouse_event_handler(struct packet mouse_packet) {
    switch (state) {

        case MAIN_MENU:
            update_mouse_location(mouse_packet.delta_x, mouse_packet.delta_y);
            if (!mouse_packet.lb) return;

            if (cursor->pos_x >= PLAY_BTN_X1 && cursor->pos_x <= PLAY_BTN_X2 &&
            cursor->pos_y >= PLAY_BTN_Y1 && cursor->pos_y <= PLAY_BTN_Y2) {
            state = PLAYING;
            }
            if (cursor->pos_x >= INSTR_BTN_X1 && cursor->pos_x <= INSTR_BTN_X2 &&
            cursor->pos_y >= INSTR_BTN_Y1 && cursor->pos_y <= INSTR_BTN_Y2) {
            state = INSTRUCTIONS;
            }
            if (cursor->pos_x >= EXIT_BTN_X1 && cursor->pos_x <= EXIT_BTN_X2 &&
            cursor->pos_y >= EXIT_BTN_Y1 && cursor->pos_y <= EXIT_BTN_Y2) {
            printf("Exit button clicked!\n");
            state = EXIT;
            return;
        }
        break;

        case PLAYING:
            update_mouse_location(mouse_packet.delta_x, mouse_packet.delta_y);
            if (!mouse_packet.lb) return;

           // coordenadas dos botões
            
            
            // falta meter a lógica das setas verdes, para dar spawn do personagem

            break;

        case INSTRUCTIONS:
            update_mouse_location(mouse_packet.delta_x, mouse_packet.delta_y);
            if (!mouse_packet.lb) return;

            if (cursor->pos_x >= BACK_BTN_X1 && cursor->pos_x <= BACK_BTN_X2 &&
            cursor->pos_y >= BACK_BTN_Y1 && cursor->pos_y <= BACK_BTN_Y2) {
            state = MAIN_MENU;
            }

            break;

        case EXIT:
            break;
    }
}


