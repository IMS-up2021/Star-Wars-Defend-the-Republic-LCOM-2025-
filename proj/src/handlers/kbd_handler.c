#include "kbd_handler.h"
#include "gameState.h"
#include "manager.h"
#include "menu.h"
#include "graphics.h"

void kbd_event_handler(uint8_t scan_code[2]) {
    uint16_t full_scancode;

    if (scancode[0] == TWO_BYTE_CODE)
        full_scancode = (scancode[0] << 8) | scancode[1];
    else
        full_scancode = scancode[0];

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
        case PLAYING:
        
            if (full_scancode == ESC_BREAK)
                state = MAIN_MENU;
        break;
        default:
            break;
    }
}

