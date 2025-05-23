#include <sys/time.h>
#include <lcom/lcf.h>
#include "manager.h"
#include "xpms/mouse_cursor.xpm"

uint32_t timer_irq_set, kbd_irq_set, mouse_irq_set;

int kbd_i;
bool mouse_ready;
int timer_counter;

uint64_t delta_time;

int (initialize_graphics)() {
    uint8_t timer_bit_no, kbd_bit_no, mouse_bit_no;
    if (timer_subscribe_int(&timer_bit_no) != 0) {
        printf("Error subscribing timer interrupts\n");
        return 1;
    }
    if (kbd_subscribe_int(&kbd_bit_no) != 0) {
        printf("Error subscribing keyboard interrupts\n");
        timer_unsubscribe_int();
        return 1;
    }
    if (mouse_subscribe_int(&mouse_bit_no) != 0) {
        printf("Error subscribing mouse interrupts\n");
        kbd_unsubscribe_int();
        timer_unsubscribe_int();
        return 1;
    }

    if (mouse_enable_data_reporting() != 0) {
        printf("Error enabling mouse data reporting\n");
        mouse_unsubscribe_int();
        kbd_unsubscribe_int();
        timer_unsubscribe_int();
        return 1;
    }

    timer_irq_set = BIT(timer_bit_no);
    kbd_irq_set = BIT(kbd_bit_no);
    mouse_irq_set = BIT(mouse_bit_no);

    uint16_t mode_info = VBE_1024p_DC; 
    if (set_frame_buffer(mode_info) == 1) {
        printf("Error initializing graphics mode\n");
        mouse_unsubscribe_int();
        kbd_unsubscribe_int();
        timer_unsubscribe_int();
        return 1;
    }
    if (set_graphic_mode(mode_info) == 1) {
        printf("Error setting graphics mode\n");
        mouse_unsubscribe_int();
        kbd_unsubscribe_int();
        timer_unsubscribe_int();
        return 1;
    } 

    return 0;
}


int (exit_game)() {
    if (mouse_unsubscribe_int() != 0) {
        printf("Error unsubscribing mouse interrupts\n");
        fflush(stdout);
        return 1;
    }
    if (kbd_unsubscribe_int() != 0) {
        printf("Error unsubscribing keyboard interrupts\n");
        fflush(stdout);
        return 1;
    }
    if (timer_unsubscribe_int() != 0) {
        printf("Error unsubscribing timer interrupts\n");
        fflush(stdout);
        return 1;
    }
    if (mouse_enable_data_reporting() != 0) {
        printf("Error disabling mouse data reporting\n");
        fflush(stdout);
        return 1;
    }
    if(vg_exit() == 1) {
        printf("Error exiting graphics mode\n");
        fflush(stdout);
        return 1;
    }
    

    return 0;
}
