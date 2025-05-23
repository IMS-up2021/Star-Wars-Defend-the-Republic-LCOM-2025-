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

typedef struct Position {
  uint16_t x;
  uint16_t y;
} Position;


extern Position mouse_pos;

void gameLoop(void);

extern gameState state;

void setGameState(gameState newState);

#endif 

