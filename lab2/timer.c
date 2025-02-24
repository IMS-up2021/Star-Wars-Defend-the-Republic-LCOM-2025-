#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook_id = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  if (freq > TIMER_FREQ || freq < 19) return 1; // freq can't go bellow 19 because after a certain point the counter does an overflow

  uint8_t controlWord;
  if(timer_get_conf(timer, &controlWord) != 0) return 1;
  
  controlWord = (controlWord & 0x0F) | TIMER_LSB_MSB;

  // TODO


  switch (timer) {
  case 0:
    controlWord |= TIMER_SEL0;
    break;
  case 1:
    controlWord |= TIMER_SEL1;
    break;
  case 2:
    controlWord |= TIMER_SEL2;
    break;
  default:
    return 1;
  }


  return 0;
}

// subscrição das interrupções
int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  int sys_policy = sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
  if (sys_policy != 0) return 1;
  return 0;
}

// desliga as interrupções
int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != 0) return 1; 
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st == NULL || timer < 0  || timer > 2) return 1; // interruption in case: the address memory is not defined, and the timer not int the correct interval
  uint8_t RBC = (TIMER_RB_CMD | TIMER_RB_SEL(timer));
  sys_outb(TIMER_CTRL, RBC);

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

/*
" make clean && make
  lcom_run lab2 "config -t 0"
"
*/