/*
    Isto será irá tratar da mudança de frequencia do timer, durante o jogo.
    Se calhar, seria interessante fazer uma mini maquina de estados para o timer com os estados: 
    Paused (0 fps), Faster (por exemplo, 120 fps), Normal (por exemplo, 60 fps)

    Depois, em termos de sprites, dependendo do estado, isso pode ser tratado noutra parte

    Outra opção é adicionar mais dois estados à state machine do jogo, ou seja:

    MAIN_MENU (não vai ser utilizado)
    PLAYING (60 fps)
    INSTRUCTIONS (não vai ser utilizado)
    PAUSED (0 fps)
    FASTER (120 fps)
    EXIT (não vai ser utilizado)

    E depois, dependendo do estado, o timer irá ter uma frequencia diferente.
*/


#include "timer_handler.h"
#include "gameState.h"
#include "manager.h"



void timer_event_handler(int game_state) {
  switch (state) {
    case MAIN_MENU:
        break;
      
    case PLAYING:
        if (game_state == 0) {
            // Pause the game
            //timer_set_frequency(0);
        } else if (game_state == 1) {
            // Resume the game
            //timer_set_frequency(60);
        } else if (game_state == 2) {
            // Speed up the game
            //timer_set_frequency(120);
        }
        break;

    case INSTRUCTIONS:
        break;
      
    case EXIT:
        break;
  }
}
