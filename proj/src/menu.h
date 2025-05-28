#ifndef MENU_H
#define MENU_H

#include <lcom/lcf.h>
#include <lcom/xpm.h>

//instructions button coordinates
#define INSTR_BTN_X1  565
#define INSTR_BTN_X2  710
#define INSTR_BTN_Y1  715
#define INSTR_BTN_Y2  850

void load_menu_assets(void);
void draw_menu(void);

void load_game_assets(void);
void draw_game(void);

void load_instructions_assets(void);
void draw_instructions(void);

#endif
