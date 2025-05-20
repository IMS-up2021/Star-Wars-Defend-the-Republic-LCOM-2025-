#include "kbd_handler.h"
#include "manager.h"
#include <stdbool.h>


bool changed;
bool two_byte;
gameState state;

void kbd_event_handler(uint8_t scan_code[2]) {
    switch (state) {

        case MAIN_MENU:
            if (scan_code[0] == ESC_BREAK) {
            state = EXIT;
            }

            break;
        case PLAYING:

            if (scan_code[0] == TWO_BYTE_CODE) two_byte = true;
            else two_byte = false;
            
            uint8_t key_code = two_byte ? scan_code[1] : scan_code[0];

            if (two_byte) {
                switch (key_code) {
                    case ONE_T:
                        // character = '1';
                        break;
                    case TWO_T:
                        // character = '2';
                        break;
                    case THREE_T:
                        // character = '3';
                        break;
                    default: break;
                }
            } else if (scan_code[0] == ESC_BREAK) {
                state = EXIT; // isto pode ser uma especie de pausa (se não quisermos implementar o botão de pause)
            }
            break;

        case INSTRUCTIONS:
            switch (scan_code[0]) {
                case ESC_BREAK:
                    state = MAIN_MENU;
                    changed = true;
                    break;
                default:
                    break;
            }
            break;
            
        case EXIT:
            break;
    }
}


