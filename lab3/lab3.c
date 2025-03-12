#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "KBC.h"

extern uint32_t counter_kbd;
extern uint32_t counter;
extern uint8_t scancode;
extern int r;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status;
  uint8_t irq_set;

  message msg;

  if(kbd_subscribe_int(&irq_set) != 0) return 1;
  
  while (scancode != ESC_BREAK) {
    if( driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("error");
      continue;
    }
    if(is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:
        if(msg.m_notify.interrupts & irq_set) {
          kbc_ih(); // adiciona ao contador interno
          kbd_print_scancode(!(scancode & MAKE_CODE), scancode == TWO_BYTE_CODE ? 2 : 1, &scancode);
          }
        }
     
    } 
  }

  if (kbd_unsubscribe_int() != 0) return 1;
  if (kbd_print_no_sysinb(counter_kbd) != 0) return 1;

  return 0;
}

int(kbd_test_poll)() {
  while(scancode != ESC_BREAK){
    if(read_kbc_out(KBD_OUT_CMD, &scancode) == 0){
      kbd_print_scancode(!(scancode & MAKE_CODE), scancode == TWO_BYTE_CODE ? 2 : 1, &scancode);
    }
  }
  return kbc_restore();
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  uint8_t irq_set_kbd, irq_set_timer;
  int seconds = 0;
  message msg;

  if(timer_subscribe_int(&irq_set_timer) != 0) return 1;
  if(kbd_subscribe_int(&irq_set_kbd) != 0) return 1;
  
  while (scancode != ESC_BREAK && seconds < n) {
    if( driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("error");
      continue;
    }
    if(is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:
        if(msg.m_notify.interrupts & irq_set_kbd) {
          kbc_ih(); 
          kbd_print_scancode(!(scancode & MAKE_CODE), scancode == TWO_BYTE_CODE ? 2 : 1, &scancode);
          seconds = 0;
          counter = 0;
          }

        if (msg.m_notify.interrupts & irq_set_timer) {
          timer_int_handler();
          if (counter % 60 == 0) seconds++;
        }
        break;
      }
    } 
  }

  if (timer_unsubscribe_int() != 0) return 1;
  if (kbd_unsubscribe_int() != 0) return 1;
  if (kbd_print_no_sysinb(counter_kbd) != 0) return 1;

  return 0;
}
