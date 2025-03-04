#include <lcom/lcf.h>

#include <stdint.h>

// Least significant bits
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if (lsb == NULL) return 1; 
  *lsb = val & 0xFF;
  return 0;
}

// Most significant bits
int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) return 1;
  *msb = (val >> 8);
  return 1;
}

// Transform 32 bit output in 8 bit output. Error prevention.
int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL) return 1;
  uint32_t temp_val;
  int ret = sys_inb(port, &temp_val);
  *value =  0xFF & temp_val;
  return ret;
}
