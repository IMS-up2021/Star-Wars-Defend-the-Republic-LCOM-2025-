#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/syslib.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "KBC.h"

int kbd_subscribe_int(uint8_t *bit_no);

int kbd_unsubscribe_int();

#endif