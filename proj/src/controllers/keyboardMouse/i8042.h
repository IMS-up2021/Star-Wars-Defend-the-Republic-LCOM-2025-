#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/*  IRQ LINES  */

#define IRQ_KBC             1
#define IRQ_MOUSE           12

/* KBC COMMANDS */

#define MAKE_CODE           BIT(7)
#define TWO_BYTE_CODE       0xE0
#define ERR_PARITY          BIT(7)
#define ERR_TIMEOUT         BIT(6)
#define FULL_OUT_BUF        BIT(0)
#define FULL_IN_BUF         BIT(1)

#define KBC_STAT_REG        0x64
#define KBC_IN_CMD          0x64
#define KBC_OUT_CMD         0x60
#define KBC_READ_CMD        0X20
#define KBC_WRITE_CMD       0x60

// Keys
#define LEFT_ARROW          0x4b
#define RIGHT_ARROW         0x4d
#define DOWN_ARROW          0x50
#define UP_ARROW            0x48

#define ENTER               0x1c
#define SPACE               0x39
#define ONE_T               0x02
#define TWO_T               0x03
#define THREE_T             0x04
#define FOUR_T              0x05
#define FIVE_T              0x06

/* MOUSE COMMANDS */

#define ESC_BREAK           0x81

#define DIS2                BIT(5)        // bit set to 1 for disabling mouse in command byte
#define DIS1                BIT(4)        // bit set to 1 for disabling kbd in command byte
#define INT2                BIT(1)        // bit set to 1 to enable OBF interrupts from mouse
#define INT1                BIT(0)        // bit set to 1 to enable OBF interrupts from kbd


#define ENABLE_INT          BIT(0)
#define MOUSE_ACK           OxFA
#define MOUSE_NACK          0xFE

// CONTROL byte
#define MOUSE_LB            BIT(0)
#define MOUSE_RB            BIT(1)
#define MOUSE_MB            BIT(2)
#define FIRST_BYTE          BIT(3)
#define MOUSE_X_DELTA       BIT(4)
#define MOUSE_Y_DELTA       BIT(5)
#define MOUSE_X_OVERFLOW    BIT(6)
#define MOUSE_Y_OVERFLOW    BIT(7)

#define WAIT_KBC            20000
#define MAX_ATTEMPS         10

#define MOUSE_RESET         0xFF          // resets the mouse
#define MOUSE_RESEND        0xFE          // resend byte (used for communication errors)
#define MOUSE_DEFAULT       0xF6          // set default mouse settings
#define DIS_DATA_REP        0xF5          // disables mouse data reporting
#define ENBL_DATA_REP       0xF4          // enables mouse data reporting
#define SET_SAMPLE          0xF3          // set sample rate
#define SET_REMOTE          0xF0          // set mouse to remote mode
#define READ_DATA           0xEB          // request a packet from the mouse (remote mode only)
#define SET_STREAM          0xEA          // set mouse to stream mode
#define MOUSE_CFG           0xE9          // get mouse configuration

#endif
