#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook_id = 0;

/**
 * @brief Set the frequency of a timer
 * @param timer Timer to configure
 * @param freq Frequency to set
 * @return 0 if successful, 1 otherwise
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  if (freq > TIMER_FREQ || freq < 19) return 1; // freq can't go bellow 19 because after a certain point the counter does an overflow

  uint8_t controlWord;
  if(timer_get_conf(timer, &controlWord) != 0) return 1;
  
  controlWord = (controlWord & 0x0F) | TIMER_LSB_MSB;

  uint32_t counter = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  util_get_LSB(counter, &lsb);
  util_get_MSB(counter, &msb);

  uint8_t selectedTimer;
  switch (timer) {
  case 0:
    controlWord |= TIMER_SEL0;
    selectedTimer = TIMER_0;
    break;
  case 1:
    controlWord |= TIMER_SEL1;
    selectedTimer = TIMER_1;
    break;
  case 2:
    controlWord |= TIMER_SEL2;
    selectedTimer = TIMER_2;
    break;
  default:
    return 1;
  }

  if(sys_outb(TIMER_CTRL, controlWord) != 0) return 1;

  if(sys_outb(counter, lsb) != 0) return 1;
  if(sys_outb(counter, msb) != 0) return 1;
  
  return 0;
}

/**
 * @brief Subscribes and enables Timer 0 interrupts (Default type of Interruption: Pooling, changes to Interrupt)
 * @param bit_no 
 * @return 0 if successful, 1 otherwise
 */
int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;
  *bit_no = BIT(hook_id);
  int sys_policy = sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
  if (sys_policy != 0) return 1;
  return 0;
}

/**
 * @brief Unsubscribes Timer 0 interrupts (Default type of Interruption: Pooling, returns to it)
 * @return 0 if successful, 1 otherwise
 */
int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != 0) return 1; 
  return 0;
}

/**
 * @brief Timer interrupt handler - increments the counter
 */
void (timer_int_handler)() {
  counter++;
}

/**
 * @brief Timer get Configuration - Reads the configuration of a timer, builds the READ BACK COMMAND and stores the configuration
 * @param timer Timer to get the configuration
 * @param st Address to store the configuration
 * @return 0 if successful, 1 otherwise
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st == NULL || timer < 0  || timer > 2) return 1; // interruption in case: the address memory is not defined, and the timer not int the correct interval
  uint8_t RBC = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer)); // construímos o READ BACK COMMAND (ver tabela)
  if(sys_outb(TIMER_CTRL, RBC) != 0) return 1; 
  if(util_sys_inb(TIMER_0 + timer, st)) return 1;
  return 0;
}

/**
 * @brief Timer display Configuration - Displays the configuration of a timer, by reading the READ BACK COMMAND
 * @param timer Timer to display the configuration
 * @param st Address that has stored the configuration
 * @param field Field to display (all, initial, mode, base)
 * @return 0 if successful, 1 otherwise
 */
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  switch(field) {

    case tsf_all:
      val.byte = st;
      break;
    case tsf_initial:
      st = (st >> 4) & 0x03; // Bitwise AND to isolate the last two bits (0x03 = 0011)
      if(st == 1) val.in_mode = LSB_only;
      else if (st == 2) val.in_mode = MSB_only;
      else if (st == 3) val.in_mode = MSB_after_LSB;
      else val.in_mode = INVAL_val;
      break;
    case tsf_mode:
      st = (st >> 1) & 0x07;
      if(st == 6) val.count_mode = 2; // Mode 2 - Rate Generator
      else if(st == 7) val.count_mode =3; // Mode 3 - Square Wave Generator
      else val.count_mode = st;
      break;
    case tsf_base:
      val.bcd = st & TIMER_BCD;
      break;
    default:
      return 1;
  }

  if(timer_print_config(timer, field, val) != 0) return 1;
  return 0;
}