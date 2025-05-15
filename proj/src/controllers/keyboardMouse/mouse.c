#include "mouse.h"
#include "KBC.h"
#include <lcom/lcf.h>

struct packet mouse_packet;
int mouse_hook_id = 4; // um valor qualquer [0..7], desde que seja diferente do teclado e do timer
uint8_t byte_index = 0;
uint8_t current_byte; // último byte a ser lido
uint8_t mouse_bytes[3];

// Subscrição das interrupções - Modo REENABLE para modo EXCLUSIVE
int (mouse_subscribe_int)(uint8_t *bit_no) {
    if(bit_no == NULL) return 1;
    *bit_no = BIT(mouse_hook_id);
    return sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
    return 0;
}

// Desativação
int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

// a cada chamada do interrupt handler, lê o byte mais recente do rato
void (mouse_ih)() {
    if (read_kbc_out(KBC_WRITE_CMD, &current_byte, 1)) printf("Error reading byte from mouse \n");
}

void (mouse_sync_bytes)() {
    if(byte_index == 0 && (current_byte & FIRST_BYTE)) {
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    }
    else if (byte_index > 0) {
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    }
}

void (mouse_bytes_to_packet)() {
    for (int i = 0; i < 3; i++) {
        mouse_packet.bytes[i] = mouse_bytes[i];
    }
    mouse_packet.rb = mouse_bytes[0] & MOUSE_RB;
    mouse_packet.mb = mouse_bytes[0] & MOUSE_MB;
    mouse_packet.lb = mouse_bytes[0] & MOUSE_LB;
    mouse_packet.x_ov = mouse_bytes[0] & MOUSE_X_OVERFLOW;
    mouse_packet.y_ov = mouse_bytes[0] & MOUSE_Y_OVERFLOW;
    mouse_packet.delta_x = (mouse_bytes[0] & MOUSE_X_DELTA) ? (0xFF00 | mouse_bytes[1]) : mouse_bytes[1];
    mouse_packet.delta_y = (mouse_bytes[0] & MOUSE_Y_DELTA) ? (0xFF00 | mouse_bytes[2]) : mouse_bytes[2];
}

// Em comparação com o kbd, a escrita do mouse tem de ser muito mais controlada, e a realização de um comando tem que ser feito diretamente e depois temos de esperar por uma resposta afirmativa
int (mouse_write)(uint8_t command) {
    uint8_t attemps = MAX_ATTEMPS;
    uint8_t mouse_response;

    do {
        attemps--;
        if (write_kbc_cmd(KBC_IN_CMD, MOUSE_CFG)) return 1;
        if (write_kbc_cmd(KBC_OUT_CMD, command)) return 1;
        tickdelay(micros_to_ticks(WAIT_KBC));
        if (util_sys_inb(KBC_OUT_CMD, &mouse_response)) return 1;
        if (mouse_response == MOUSE_ACK) return 0;
    } while (mouse_response != MOUSE_ACK && attemps);

    return 1;
}
