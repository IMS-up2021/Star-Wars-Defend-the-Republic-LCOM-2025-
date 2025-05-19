#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>
#include <lcom/lcf.h>

typedef enum {
    MAIN_MENU,
    PLAYING,
    INSTRUCTIONS,
    EXIT
} gameState;

extern gameState state;

void setGameState(gameState newState);

#endif 

