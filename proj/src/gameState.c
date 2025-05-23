#include "gameState.h"
#include "menu.h"
#include "controllers/keyboardMouse/keyboard.h"
#include "manager.h"
#include <lcom/lcf.h>
#include "controllers/keyboardMouse/mouse.h"


extern uint32_t kbd_irq_set; // Use the one from manager.c
extern uint32_t mouse_irq_set; // Use the one from manager.c
bool mouse_ready = true;

gameState state = MAIN_MENU;

void gameLoop(void) {
    int ipc_status, r;
    message msg;
    bool running = true;
    lcf_log_output("/home/lcom/labs/grupo_2leic18_2/proj/src/output.txt");

    draw_menu(); // Draw the menu
    init_cursor(); // Initialize the cursor

    while (running) {
        

        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            continue;
        }
        if (is_ipc_notify(msg.m_type)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & kbd_irq_set) {
                        kbc_ih();
                        if (scancode == ESC_BREAK) { // ESC break code
                            if (exit_game() == 0) { // Call exit_game() and check for success
                                running = false;
                                printf("Game exited successfully\n");
                                fflush(stdout);
                            } else {
                                printf("Error during game exit\n");
                                fflush(stdout);
                            }
                        }
                    }
                    if (msg.m_notify.interrupts & mouse_irq_set) {
                        mouse_ih();

                        if (mouse_ready) {
                            mouse_ready = false;
                            // handle_mouse_event(pp);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
