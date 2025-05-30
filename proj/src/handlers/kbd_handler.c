#include "xpms/selected1.xpm"
#include "xpms/selected2.xpm"
#include "xpms/selected3.xpm"

#include <lcom/lcf.h>
#include <lcom/xpm.h>

#include "kbd_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "characters.h"
#include "controllers/video/graphics.h"

extern vbe_mode_info_t mode_info;
int kbd_state = 1;

void kbd_event_handler(uint8_t scan_code[2]) {
    uint16_t full_scancode;

    if (scan_code[0] == TWO_BYTE_CODE)
        full_scancode = (scan_code[0] << 8) | scan_code[1];
    else
        full_scancode = scan_code[0];

    bool is_break = (full_scancode & 0x80) != 0;
    printf("Scancode: 0x%X (%s code)\n", full_scancode, is_break ? "break" : "make");

    if (!is_break)
        return; // Só lidamos com break codes neste caso

    switch (state) {
        case MAIN_MENU:
            if (full_scancode == ESC_BREAK)
                state = EXIT;
        break;
        case INSTRUCTIONS:
            if (full_scancode == ESC_BREAK)
                state = MAIN_MENU;
            break;
        case PLAYING:
            if (full_scancode == ESC_BREAK){
                state = MAIN_MENU;
            }
            else if(full_scancode == ONE_T){
                kbd_state = 1;
            }
            else if(full_scancode == TWO_T){
                kbd_state = 2;
            }
            else if(full_scancode == THREE_T){
                kbd_state = 3;
            }
            break;
        default:
            break;
    }
}

