#include <lcom/lcf.h>

#include "gameState.h"
#include "menu.h"
#include "entity.h"
#include "manager.h"

#include "controllers/keyboardMouse/mouse.h"
#include "controllers/keyboardMouse/keyboard.h"
#include "controllers/timer/timer.h"
#include "handlers/mouse_handler.h"


extern bool mouse_ready;
extern Cursor *cursor;
extern uint8_t *double_buffer;
extern int timer_global_counter;

struct packet mouse_packet; 


gameState state = MAIN_MENU;

void gameLoop(void) {
    int ipc_status, r;
    message msg;
    bool running = true;
    lcf_log_output("/home/lcom/labs/grupo_2leic18_2/proj/src/output.txt");

    init_cursor();

    while (running) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) continue;

        if (is_ipc_notify(ipc_status)) {
            if (_ENDPOINT_P(msg.m_source) == HARDWARE) {
                if (msg.m_notify.interrupts & timer_irq_set) {
                    timer_int_handler();
                    if (timer_global_counter % 2 == 0) {
                        unsigned int _frame_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
                        memset(double_buffer, 0, _frame_size);
                        switch (state) { 
                            case MAIN_MENU:
                                draw_menu();
                                break;
                            case PLAYING:
                                // draw_playing_screen(); // Função que desenha o ecrã de jogo, incluindo o cursor
                                break;
                            case INSTRUCTIONS:
                                // draw_instructions_screen(); // etc.
                                break;
                            default:
                                break;
                        }
                        draw_cursor(cursor);

                        vg_swap_buffers();
                    }
                    
                }
                if (msg.m_notify.interrupts & mouse_irq_set) {
                    mouse_ih();
                    if (mouse_ready) {
                        mouse_event_handler(mouse_packet);
                        // draw_cursor(cursor);
                        mouse_ready = false;
                    }
                }
                
            } else {
                printf("Loop: NAO ENTROU no if is_ipc_notify. msg.m_type foi 0x%X.\n", msg.m_type);
            }
        }
    }
}
