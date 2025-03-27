#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/syslib.h>
#include "i8042.h"
#include <lcom/lcf.h>

/**
 * @brief Reads the status of the KBC
 * @param status Address of the variable to store the status
 * @return 0 if successful, 1 otherwise
 */
int (read_KBC_status)(uint8_t* status);

/**
 * @brief Writes a command to the KBC
 * @param port Port to write the command
 * @param cmdByte Command to write
 * @return 0 if successful, 1 otherwise
 */
int (write_kbc_cmd)(uint8_t port, uint8_t cmdByte);

/**
 * @brief Reads the output of the KBC
 * @param port Port to read the output
 * @param cmdByteOut Address of the variable to store the output
 * @return 0 if successful, 1 otherwise
 */
int (read_kbc_out)(uint8_t port, uint8_t *cmdByteOut, uint8_t mouse);

/**
 * @brief Writes a command to the KBC
 * @param port Port to write the command
 * @param cmdByte Command to write
 * @return 0 if successful, 1 otherwise
 */
// int (kbc_restore)();



#endif
