#include "KBC.h"


int (read_KBC_status)(uint8_t* status){
    return util_sys_inb(KBD_STAT_REG, status);
}

int (write_kbc_cmd)(uint8_t port, uint8_t cmdByte) {

    uint8_t status;
    uint8_t attemps = MAX_ATTEMPS;
     
    while(attemps) {
        if(read_KBC_status(&status) != 0) {
            printf("Error: status read failed\n");
            return 1;
        }

        if((status & BIT(0)) == 0) {
            if(sys_outb(port, cmdByte) != 0) {
                printf("Error: command write failed\n");
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(WAIT_KBC));
        attemps--;
    }
    return 1;
}

int (read_kbc_out)(uint8_t port, uint8_t *cmdByteOut) {

    uint8_t status;
    uint8_t attemps = MAX_ATTEMPS;

    while (attemps){
        if(read_KBC_status(&status) != 0) {
            printf("Error: status read failed\n");
            return 1;
        }

        if((status & BIT(0)) != 0) {
            if(util_sys_inb(port, cmdByteOut) != 0) {
                printf("Error: output read failed\n");
                return 1;
            }
            if((status & ERR_PARITY) != 0) {
                printf("Error: Parity error\n");
                return 1;
            }
            if((status & ERR_TIMEOUT) != 0) {
                printf("Error: Timeout error\n");
                return 1;
            }
            return 0;
        }
        tickdelay(micros_to_ticks(WAIT_KBC));
        attemps--;
    }
    return 1;    
}

int (kbc_restore)() {
    uint8_t commandWord;

    if(write_kbc_cmd(0x64, 0x20) != 0) return 1; // Solicita o byte de comando atual do KBC
    if(read_kbc_out(0x60, &commandWord) != 0) return 1; // Lê o byte de comando (retornado pela porta 0x60)

    commandWord = commandWord | BIT(0); // Define o bit 0 para ativar interrupções do teclado

    if(write_kbc_cmd(0x64, 0x60) != 0) return 1; // Diz ao KBC que vamos escrever um novo byte de comando
    if(write_kbc_cmd(0x60, commandWord) != 0) return 1; // Escreve o byte de comando atualizado

    return 0; // Retorna sucesso
}
