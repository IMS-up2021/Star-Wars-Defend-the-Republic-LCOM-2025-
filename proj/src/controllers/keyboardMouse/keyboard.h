#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/syslib.h>
#include <lcom/lcf.h>
#include "i8042.h"

/**
 * @brief Subscribes and enables Keyboard interrupts
 * @param bit_no Address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return 0 if successful, 1 otherwise
 */
int kbd_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes Keyboard interrupts
 * @return 0 if successful, 1 otherwise
 */
int kbd_unsubscribe_int();

void (kbc_ih)();

int(kbd_restore)();

extern uint8_t scancode;

#endif
