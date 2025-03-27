// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab4.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "i8042.h"
#include "i8254.h"
#include "KBC.h"
#include "mouse.h"

extern struct packet mouse_packet;
extern uint8_t byte_index;
extern int counter;


// Definição dos estados da máquina de estados
typedef enum {
  START,
  UP,
  VERTEX,
  DOWN,
  END
} State;

State state = START;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  int ipc_status;
  message msg;
  uint8_t mouse_mask; //interpretação das interrupções

  if (mouse_subscribe_int(&mouse_mask) != 0) return 1;
  if (mouse_write(ENABLE_DATA_REPORT) != 0) return 1;

  while (cnt) { // cnt pacotes
    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 
          if (msg.m_notify.interrupts & mouse_mask){  // Se for uma interrupção do rato
            mouse_ih();                               // Lemos mais um byte
            mouse_sync_bytes();                       // Sincronizamos esse byte no pacote respectivo
            if (byte_index == 3) {                    // Quando tivermos três bytes do mesmo pacote
              mouse_bytes_to_packet();                // Formamos o pacote
              mouse_print_packet(&mouse_packet);      // Mostramos o pacote
              byte_index = 0;
              cnt--;
            }
          }
          break;
      }
    }
  }

  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {

  int ipc_status;
  message msg;
  uint8_t seconds = 0;
  uint8_t mouse_mask = 0, timer_mask = 0;
  uint16_t timer_freq = sys_hz();

  if (mouse_subscribe_int(&mouse_mask) != 0) return 1;
  if (timer_subscribe_int(&timer_mask) != 0) return 1;
  if (mouse_write(ENABLE_DATA_REPORT) != 0) return 1;

  while (seconds < idle_time) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 
          if (msg.m_notify.interrupts & timer_mask) { // timer
            timer_int_handler();
            if (counter % timer_freq == 0) seconds++;
          }
          if (msg.m_notify.interrupts & mouse_mask){ // mouse
            mouse_ih();
            mouse_sync_bytes();
            if (byte_index == 3) {
              mouse_bytes_to_packet();
              mouse_print_packet(&mouse_packet);
              byte_index = 0;
            }
            seconds = 0;
            counter = 0;
          }
          break;
      }
    }
  }

  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;
  if (timer_unsubscribe_int() != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;

  return 0;
}

// função auxiliar
void update_state_machine(uint8_t tolerence) {
  switch (state) {
      case START:
          // Transição I
          if (mouse_packet.lb && !mouse_packet.rb && !mouse_packet.mb) state = UP;
          break;
      case UP:
          // Transição II: Se soltar o botão esquerdo
          if (!mouse_packet.lb) state = VERTEX;
          // Transição III: Se o botão direito for pressionado
          else if (mouse_packet.rb) state = END;
          break;
      case VERTEX:
          // Transição IV: Se o botão esquerdo for pressionado novamente
          if (mouse_packet.lb) state = DOWN;
          // Transição F: Se o botão direito for pressionado
          else if (mouse_packet.rb) state = END;
          break;
      case DOWN:
          // Transição V: Se soltar o botão esquerdo
          if (!mouse_packet.lb) state = START;
          // Transição VI: Se o botão direito for pressionado
          else if (mouse_packet.rb) state = END;
          break;
      case END:
          // Estado final, nenhuma transição adicional
          break;
  }
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerence) {
  int ipc_status;
  message msg;
  uint8_t mouse_mask;

  if (mouse_subscribe_int(&mouse_mask) != 0) return 1;
  if (mouse_write(ENABLE_DATA_REPORT) != 0) return 1;

  while (state != END) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0){
      printf("Error");
      continue;
    }
    if (is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: 
          if (msg.m_notify.interrupts & mouse_mask){
            mouse_ih();
            mouse_sync_bytes();
            if (byte_index == 3) {
              mouse_bytes_to_packet();
              update_state_machine(tolerence); // Atualizar a Máquina de Estados
              byte_index = 0;
            }
          }
      }
    }
  }

  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;

  return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) { // remote mode (polling já é o default de LCF)

  while (cnt) {
    if (mouse_write(MOUSE_READ_DATA) != 0) return 1;
    mouse_ih();
    mouse_sync_bytes();    
    if (byte_index == 3) {
        mouse_bytes_to_packet();
        mouse_print_packet(&mouse_packet);
        byte_index = 0;
        cnt--;
        tickdelay(micros_to_ticks(period * 1000));    // microssegundos até ler o próximo pacote
    }
  }

  if (mouse_write(ENABLE_STREAM_MODE) != 0) return 1;
  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;

  // KBC volta ao estado normal
  uint8_t commandByte = minix_get_dflt_kbc_cmd_byte(); // isto já é dado pelo LCF
  if (write_kbc_cmd(KBC_IN_CMD, KBC_WRITE_CMD) != 0) return 1;
  if (write_kbc_cmd(KBC_WRITE_CMD, commandByte) != 0) return 1;

  return 0;
}
