#include "gameState.h"
#include "menu.h"
#include "controllers/keyboardMouse/keyboard.h"
#include "manager.h"
#include <lcom/lcf.h>

extern uint32_t kbd_irq_set; // Use the one from manager.c

gameState state = MAIN_MENU;

void gameLoop(void) {
    int ipc_status, r;
    message msg;
    bool running = true;
    lcf_log_output("/home/lcom/labs/grupo_2leic18_2/proj/src/output.txt");


    while (running) {
        draw_menu(); // Draw the menu

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
                    break;
                default:
                    break;
            }
        }
    }
}
