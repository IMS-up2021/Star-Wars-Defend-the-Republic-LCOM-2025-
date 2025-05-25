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
            // if (!mouse_packet.lb) return;

            /*
            // coordenadas dos botões~: EXEMPLOS
            if (mouse_pos.x >= 0 && mouse_pos.x <= 200 && mouse_pos.y >= 0 && mouse_pos.y <= 100) {
                state = PLAYING;
            } else if (mouse_pos.x >= 0 && mouse_pos.x <= 200 && mouse_pos.y >= 100 && mouse_pos.y <= 200) {
                state = INSTRUCTIONS;
            } else if (mouse_pos.x >= 0 && mouse_pos.x <= 200 && mouse_pos.y >= 200 && mouse_pos.y <= 300) {
                state = EXIT;
            }*/

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

            // coordenadas dos botões
            break;

        case EXIT:
            break;
    }
}
