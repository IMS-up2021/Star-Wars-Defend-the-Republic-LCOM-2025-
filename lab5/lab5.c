// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "graphics.h"
#include "VBE.h"
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "pixmap.h"

extern vbe_mode_info_t mode_info;
extern uint8_t scancode[2];


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (set_graphic_mode(mode) != 0) return 1;
  sleep(delay);
  if (vg_exit() != 0) return 1;

  return 0;
}

// for rectangle
int(waiting_ESC_key)() {

  int ipc_status;
  message msg;
  uint8_t keyboard_mask;

  if (kbd_subscribe_int(&keyboard_mask) != 0) return 1;

  while (scancode[0] != ESC_BREAK){
    if (driver_receive(ANY, &msg, &ipc_status) != 0) { 
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & keyboard_mask) 
            kbc_ih();
            break;
        default:
          break; 
      }
    }
  }
  if (kbd_unsubscribe_int() != 0) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  if (set_frame_buffer(mode) != 0) return 1;
  if (set_graphic_mode(mode) != 0) return 1;

  uint32_t new_color;

  if (normalize_color(color, &new_color) != 0) return 1;
  if (vg_draw_rectangle(x, y, width, height, new_color) != 0) return 1;
  if (waiting_ESC_key() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  // Retrieve mode information using vbe_get_mode_info()
  if (vbe_get_mode_info(mode, &mode_info) != 0) {
    printf("Error: Failed to get VBE mode info\n");
    return 1;
  }

  // Set the frame buffer and graphics mode
  if (set_frame_buffer(mode) != 0) return 1;
  if (set_graphic_mode(mode) != 0) return 1;

  // Calculate rectangle dimensions
  uint16_t width = mode_info.XResolution / no_rectangles;
  uint16_t height = mode_info.YResolution / no_rectangles;

  // Draw the pattern of rectangles
  for (uint8_t row = 0; row < no_rectangles; row++) {
    for (uint8_t col = 0; col < no_rectangles; col++) {
      uint32_t color;

      if (mode_info.MemoryModel == DIRECT_COLOR) { // Direct color mode
        uint32_t red = (R(first) + col * step) % (1 << mode_info.RedMaskSize);
        uint32_t green = (G(first) + row * step) % (1 << mode_info.GreenMaskSize);
        uint32_t blue = (B(first) + (col + row) * step) % (1 << mode_info.BlueMaskSize);

        color = (red << mode_info.RedFieldPosition) |
                (green << mode_info.GreenFieldPosition) |
                (blue << mode_info.BlueFieldPosition);
      } else { // Indexed color mode
        color = (first + (row * no_rectangles + col) * step) % (1 << mode_info.BitsPerPixel);
      }

      if (vg_draw_rectangle(col * width, row * height, width, height, color) != 0) {
        return 1;
      }
    }
  }

  // Wait for ESC key and exit graphics mode
  if (waiting_ESC_key() != 0) return 1;
  if (vg_exit() != 0) return 1;

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if(set_frame_buffer(VBE_1024p_DC)) return 1;
  
  if(set_graphic_mode(VBE_1024p_DC)) return 1;

  if (print_xpm(ana, x, y) != 0) return 1;

  if (waiting_ESC_key()) return 1;

  if (vg_exit() != 0) return 1;

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
