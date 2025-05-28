#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

#include <stdio.h>
#include "controllers/timer/timer.h"
#include <lcom/timer.h>
#include "manager.h"
#include "gameState.h"

void timer_event_handler(gameState game_state);

#endif // TIMER_HANDLER_H
