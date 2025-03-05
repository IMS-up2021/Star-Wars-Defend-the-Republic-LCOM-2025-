#include <lcom/lcf.h>
#include <lcom/lab2.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

extern int counter;

/**
 * @brief Main function of the program
 * @param argc Number of arguments
 * @param argv Arguments
 * @return 0 if successful, 1 otherwise
 */
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

/**
 * @brief Timer Test Read Configuration - Test the reading of the configuration of a timer
 * @param timer Timer to read the configuration
 * @param field Field to display (all, initial, mode, base)
 * @return 0 if successful, 1 otherwise
 */
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

/**
 * @brief Timer Test Time Base - Test the setting of the timer frequency
 * @param timer Timer to set the frequency
 * @param freq Frequency to set
 * @return 0 if successful, 1 otherwise
 */
int(timer_test_time_base)(uint8_t timer, uint32_t freq)   {
  if(timer > 2 || freq < 19) return 1;
  return timer_set_frequency(timer, freq);
}

/**
 * @brief Timer Test Interruption - Test the subscription to the interruption of the timer and then the unsubscription
 * @param time Time to wait
 * @return 0 if successful, 1 otherwise
 */
int(timer_test_int)(uint8_t time) {
  int ipc_status, r;
  uint8_t hook_id_timer;
  message msg;

  if(timer_subscribe_int(&hook_id_timer) != 0) return 1;

  while (time > 0) {
    if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if(is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:

        if(msg.m_notify.interrupts & hook_id_timer) {
          timer_int_handler();
          if(counter % 60 == 0) {
            timer_print_elapsed_time();
            time--;
          }
        }
       
        break;
      
      default:
        break;
      }
    }
  }

  if(timer_unsubscribe_int() != 0) return 1;

  return 0;
}
