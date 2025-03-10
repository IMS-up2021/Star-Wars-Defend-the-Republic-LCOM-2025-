#include "keyboard.h"
#include "KBC.h"

uint8_t scancode = 0;
int keyboard_hook_id = 1;

int (kbd_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;
  *bit_no = BIT(keyboard_hook_id);
  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&keyboard_hook_id);
}

void (kbc_ih)() {
  if (read_kbc_out(KBD_OUT_CMD, &scancode) != 0)
    printf("Error: Could not read scancode!\n");
}
