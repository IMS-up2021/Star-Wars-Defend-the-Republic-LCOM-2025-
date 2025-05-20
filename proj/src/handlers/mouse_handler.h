#include <stdio.h>
#include "controllers/keyboardMouse/mouse.h"
#include "gameState.h"

void handle_mouse_event(struct packet pp);

void handle_mouse_game_event(struct packet pp);

void handle_mouse_menu_event(struct packet pp);

void handle_mouse_instructions_event(struct packet pp);