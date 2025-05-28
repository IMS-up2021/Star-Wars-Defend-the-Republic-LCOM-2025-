#include "keyboard.h"
#include "KBC.h"

uint8_t scancode = 0;
int keyboard_hook_id = 1;

int (kbd_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;
  *bit_no = BIT(keyboard_hook_id);
  return sys_irqsetpolicy(IRQ_KBC, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&keyboard_hook_id);
}
/*
void (kbc_ih)() {
  if (kbc_read_byte(&scancode, 0) != 0)
    printf("Error: Could not read scancode!\n");
}

int(kbd_restore)() {
    uint8_t commandByte;

    if(kbc_write_byte(KBC_IN_CMD, KBC_READ_CMD) != 0) return 1;
    if(kbc_read_byte(KBC_OUT_CMD, 0) != 0) return 1;

    commandByte |= ENABLE_INT;

    if(kbc_write_byte(KBC_IN_CMD, KBC_WRITE_CMD) != 0) return 1;
    if(kbc_write_byte(KBC_WRITE_CMD, commandByte) != 0) return 1;

    return 0;
}*/
