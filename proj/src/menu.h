#ifndef MENU_H
#define MENU_H

#include <lcom/lcf.h>
#include <lcom/xpm.h>

//play button coordinates
#define PLAY_BTN_X1  340
#define PLAY_BTN_X2  485
#define PLAY_BTN_Y1  715
#define PLAY_BTN_Y2  890

//instructions button coordinates
#define INSTR_BTN_X1  565
#define INSTR_BTN_X2  710
#define INSTR_BTN_Y1  715
#define INSTR_BTN_Y2  890

//back button coordinates
#define BACK_BTN_X1  160
#define BACK_BTN_X2  260
#define BACK_BTN_Y1  80
#define BACK_BTN_Y2  140

//exit button coordinates
#define EXIT_BTN_X1  790
#define EXIT_BTN_X2  935
#define EXIT_BTN_Y1  715
#define EXIT_BTN_Y2  890

void load_menu_assets(void);
void draw_menu(void);

void load_game_assets(void);
void draw_game(void);

void load_instructions_assets(void);
void draw_instructions(void);

#endif
