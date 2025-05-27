#include "mouse.h"
#include "entity.h"
#include <lcom/xpm.h>
#include "KBC.h"
#include "gameState.h"

struct packet mouse_packet;
int mouse_hook_id = 4; // um valor qualquer [0..7], desde que seja diferente do teclado e do timer
uint8_t byte_index = 0;
uint8_t current_byte; // último byte a ser lido
uint8_t mouse_bytes[3];

bool mouse_ready = false;


// Subscrição das interrupções - Modo REENABLE para modo EXCLUSIVE
int (mouse_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = (uint8_t)mouse_hook_id;

    if (sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != 0) {
        printf("mouse_subscribe_int: sys_irqsetpolicy failed!\n");
        return 1;
    }

    return 0; // Sucesso
}

// Desativação
int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}


void (mouse_ih)() {
    uint8_t status;
    uint8_t byte_just_read;
   
    // Ler o registo de estado do KBC
    if (util_sys_inb(KBC_STAT_REG, &status)) { // KBC_STAT_REG é 0x64
        printf("mouse_ih: Error reading KBC status register\n");
        return;
    }

    // Verificar se o Output Buffer está cheio (OBF)
    if (status & FULL_OUT_BUF) {
        if (status & (ERR_PARITY | ERR_TIMEOUT)) {
            printf("IH: Erro de Paridade/Timeout no KBC Status: 0x%02X. Tentando limpar OBF.\n", status);
            uint8_t dummy_byte;
            util_sys_inb(KBC_OUT_CMD, &dummy_byte); // Lê para descartar o byte potencialmente corrompido
            byte_index = 0; // Força resincronização
            return; // Sai da IH, espera pela próxima interrupção
        }

        // Ler o byte do output buffer do KBC
        if (util_sys_inb(KBC_OUT_CMD, &byte_just_read)) { // KBC_OUT_CMD é 0x60
            printf("mouse_ih: Error reading byte from KBC output buffer\n");
            return;
        }

        if (status & BIT(5)) {
            if (byte_index == 0) {
                if (byte_just_read & FIRST_BYTE) {
                    mouse_bytes[byte_index] = byte_just_read;
                    byte_index++;
                }
            } else { // byte_index é 1 ou 2 (esperando pelo segundo ou terceiro byte)
                mouse_bytes[byte_index] = byte_just_read;
                byte_index++;
            }

            // Se o pacote de 3 bytes estiver completo
            if (byte_index == 3) {
                for (int i = 0; i < 3; i++) {
                    mouse_packet.bytes[i] = mouse_bytes[i];
                }
                mouse_packet.lb = (mouse_bytes[0] & MOUSE_LB);
                mouse_packet.rb = (mouse_bytes[0] & MOUSE_RB);
                mouse_packet.mb = (mouse_bytes[0] & MOUSE_MB);
                mouse_packet.x_ov = (mouse_bytes[0] & MOUSE_X_OVERFLOW);
                mouse_packet.y_ov = (mouse_bytes[0] & MOUSE_Y_OVERFLOW);
                int16_t dx = mouse_bytes[1];
                int16_t dy = mouse_bytes[2];
                if (mouse_bytes[0] & MOUSE_X_DELTA) dx |= 0xFF00;
                if (mouse_bytes[0] & MOUSE_Y_DELTA) dy |= 0xFF00;
                mouse_packet.delta_x = dx;
                mouse_packet.delta_y = dy;

                byte_index = 0;
                mouse_ready = true;
            }
        }
    }

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


int (mouse_write)(uint8_t command_to_mouse) {
    uint8_t mouse_response;
    int attempts = MAX_ATTEMPS;

    do {
        attempts--;
        // Dizer ao KBC que o próximo byte é para o rato
        if (kbc_write_byte(KBC_IN_CMD, 0xD4)) {
            printf("mouse_write: Failed to send 0xD4 to KBC\n");
            return 1;
        }
        // Enviar o comando para o rato através do KBC Input Buffer (que o KBC encaminhará para o rato)
        if (kbc_write_byte(KBC_WRITE_CMD, command_to_mouse)) {
            printf("mouse_write: Failed to send command (0x%02X) to KBC for mouse\n", command_to_mouse);
            return 1;
        }

        tickdelay(micros_to_ticks(20000));
        
        uint8_t status_after_cmd;
        if (util_sys_inb(KBC_STAT_REG, &status_after_cmd)) continue; 

        if (status_after_cmd & FULL_OUT_BUF) { // Se há algo para ler
            if (util_sys_inb(KBC_OUT_CMD, &mouse_response)) {
                printf("mouse_write: Failed to read mouse response\n");
                continue; // Tentar novamente
            }
            if (mouse_response == MOUSE_ACK) { // MOUSE_ACK é 0xFA
                return 0; // Sucesso
            } else {
                printf("Mouse response: 0x%02X to command 0x%02X (attempt %d)\n", mouse_response, command_to_mouse, MAX_ATTEMPS - attempts);
            }
        }
    } while (attempts > 0);

    return 1; // Falhou
}




