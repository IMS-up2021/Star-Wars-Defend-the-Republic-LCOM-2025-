##ifndef KBD_HANDLER_H
#define KBD_HANDLER_H
#include <lcom/lcf.h>

#include <stdio.h>
#include "controllers/keyboardMouse/keyboard.h"
#include "gameState.h"

void (kbd_event_handler)(uint8_t scan_code[2]);

#endif // KBD_HANDLER_H
