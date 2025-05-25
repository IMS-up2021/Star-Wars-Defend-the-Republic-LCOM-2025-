#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/syslib.h>
#include "i8042.h"
#include <lcom/lcf.h>

int (read_KBC_status)(uint8_t* status);

int (kbc_write_byte)(uint8_t port, uint8_t cmdByte);


int (read_kbc_out)(uint8_t port, uint8_t *cmdByteOut, uint8_t mouse);


#endif
