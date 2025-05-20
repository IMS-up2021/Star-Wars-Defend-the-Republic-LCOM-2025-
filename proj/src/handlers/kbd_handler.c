#include "kbd_handler.h"
// #include "draw.h"
#include "manager.h"

bool changed;
Player *player1;

void kbd_event_handler(uint8_t scan_code[2]) {
    switch (state) {

        case MAIN_MENU:
            if (scan_code[0] == ESC_BREAK) {
            state = EXIT;
            }

            break;
        case PLAYING:

            bool two_byte = (scan_code[0] == TWO_BYTE_SC);
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


