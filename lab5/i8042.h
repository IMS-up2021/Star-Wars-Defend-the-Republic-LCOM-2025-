#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define IRQ_KEYBOARD        1
#define IRQ_MOUSE           12

#define ESC_BREAK           0x81
#define MAKE_CODE           BIT(7)
#define TWO_BYTE_CODE       0xE0
#define ENABLE_INT          BIT(0)

#define KBC_STAT_REG        0x64
#define KBC_IN_CMD          0x64
#define KBC_OUT_CMD         0x60
#define KBC_READ_CMD        0X20
#define KBC_WRITE_CMD       0x60

#define ERR_PARITY          BIT(7)
#define ERR_TIMEOUT         BIT(6)
#define FULL_OUT_BUF        BIT(0)
#define FULL_IN_BUF         BIT(1)

#define WAIT_KBC            20000
#define MAX_ATTEMPS         10

#define MOUSE_LB            BIT(0)
#define MOUSE_RB            BIT(1)
#define MOUSE_MB            BIT(2)
#define FIRST_BYTE          BIT(3)
#define MOUSE_X_SIGNAL      BIT(4)
#define MOUSE_Y_SIGNAL      BIT(5)
#define MOUSE_X_OVERFLOW    BIT(6)
#define MOUSE_Y_OVERFLOW    BIT(7)
#define DISABLE_DATA_REPORT 0xF5
#define ENABLE_DATA_REPORT  0xF4
#define ENABLE_STREAM_MODE  0xEA
#define MOUSE_READ_DATA     0xEB
#define WRITE_BYTE_MOUSE    0XD4

#define ACK                 OxFA
#define NACK                0xFE

#endif
