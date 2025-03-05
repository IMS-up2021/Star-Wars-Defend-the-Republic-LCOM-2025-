#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t status;
  
  // Retrieve timer configuration
  int error = timer_get_conf(timer, &status);
  if (error) { return error; } // Return error if retrieval fails

  // Display the configuration based on the requested field
  error = timer_display_conf(timer, status, field);
  if(error) { return error; } // Return error if display fails

  return 0; //success
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq)   {
  return timer_set_frequency(timer, freq);
}

int(timer_test_int)(uint8_t time) {

  int error = timer_subscribe_int(time);
  if(error) return error;

  error = timer_unsubscribe_int();
  if(error) return error;

  return 0;
}
