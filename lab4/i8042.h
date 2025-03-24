#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KBD_IRQ             1

#define ESC_BREAK           0x81
#define MAKE_CODE           BIT(7)
#define TWO_BYTE_CODE       0xE0

#define KBD_STAT_REG        0x64
#define KBD_CMD_REG         0x64
#define KBD_IN_BUF          0x64
#define KBD_OUT_CMD         0x60

#define ERR_PARITY          BIT(7)
#define ERR_TIMEOUT         BIT(6)

#define WAIT_KBC            20000
#define MAX_ATTEMPS         10

#endif
