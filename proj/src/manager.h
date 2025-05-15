#ifndef MANAGER_H
#define MANAGER_H

#include <lcom/lcf.h>
#include "controllers/timer/timer.h"
#include "controllers/keyboardMouse/keyboard.h"
#include "controllers/keyboardMouse/mouse.h"
#include "controllers/video/graphics.h"

extern uint32_t timer_irq_set;
extern uint32_t kbd_irq_set;
extern uint32_t mouse_irq_set;
extern uint8_t *frame_buffer;
extern uint8_t *second_buffer;
extern uint16_t center_x;
extern uint16_t center_y;
extern uint64_t delta_time;

int (initialize_graphics)();

int (load_menu_assets)();

int (game_loop)();

int (exit_game)();
// void (load_xpms)();
void (handle_timer_event)();
void (handle_kbd_event)(uint8_t scancode[]);
void (handle_mouse_event)(struct packet pp);

#endif // MANAGER_H
