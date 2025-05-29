#include <math.h>
#include "mouse_handler.h"
#include "menu.h"
#include "gameState.h"
#include "entity.h"
#include "game.h"


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

        // Verifica se clicou no botão PAUSE
        if (cursor->pos_x >= PAUSE_BTN_X1 && cursor->pos_x <= PAUSE_BTN_X2 &&
            cursor->pos_y >= PAUSE_BTN_Y1 && cursor->pos_y <= PAUSE_BTN_Y2) {
            printf("Pause button clicked!\n");
            //state = PAUSED;
            return;
            }

        // Verifica se clicou no botão RESUME
        if (cursor->pos_x >= RESUME_BTN_X1 && cursor->pos_x <= RESUME_BTN_X2 &&
            cursor->pos_y >= RESUME_BTN_Y1 && cursor->pos_y <= RESUME_BTN_Y2) {
            printf("Resume button clicked!\n");
            // Provavelmente queres manter o estado em PLAYING
            // Mas pode ser útil em caso de retomar de PAUSED
            //state = PLAYING;
            return;
            }

        // Verifica se clicou no botão FAST
        if (cursor->pos_x >= FAST_BTN_X1 && cursor->pos_x <= FAST_BTN_X2 &&
            cursor->pos_y >= FAST_BTN_Y1 && cursor->pos_y <= FAST_BTN_Y2) {
            printf("Fast button clicked! Spawning fast character...\n");
            // Aqui podes chamar a função que faz o spawn de um personagem rápido
            return;
            }

        // Aqui podes continuar com outras lógicas do estado PLAYING
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


