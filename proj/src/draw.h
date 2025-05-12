#ifndef _DRAW_H_
#define _DRAW_H_

#include "entity.h"


extern Wall *top_wall;
extern Wall *bottom_wall;


extern Button *play_button;
extern Button *quit;
extern Button *instruction_button;
extern Button *back_button;
extern Button *play_again_button;

extern Player *player;
extern Player *enemy_player;

extern uint16_t x_max;
extern uint16_t y_max;

extern uint8_t *background;
extern uint8_t *background_menu;
extern uint8_t *background_instructions;
extern uint8_t *background_game_over;

bool init_buttons(void);
bool init_cursor(void);
bool init_walls(void);
bool init_players(void); // provavelmente vai ser preciso criar um sprite para as barras de vida, através da struct Player, por ter esse único atributo

bool init_background(void);
bool init_background_menu(void);
bool init_background_instructions(void);
bool init_background_game_over(void);

int draw_button(Button *button);
int draw_cursor(Cursor *cursor);
int draw_wall(Wall *wall);
int draw_background(uint8_t *background);
int draw_charater(Character *character); // isto depois vai ser preciso mudar para o sprite do personagem, que vai ser uma struct com o xpm e a posição (isto é só um exemplo)

int draw_health_bar(Player *player); // isto depois vai ser preciso mudar para o sprite do personagem, que vai ser uma struct com o xpm e a posição (isto é só um exemplo)
int draw_health_bar_enemy(Player *player); // isto depois vai ser preciso mudar para o sprite do personagem, que vai ser uma struct com o xpm e a posição (isto é só um exemplo)
int draw_gold_bar(Player *player); // isto depois vai ser preciso mudar para o sprite do personagem, que vai ser uma struct com o xpm e a posição (isto é só um exemplo)
int draw_menu(); // dependendo do estado do jogo, vai desenhar o background, os personagens, os botões e o cursor
int draw_instructions(); // dependendo do estado do jogo, vai desenhar o background, os personagens, os botões e o cursor
int draw_game(); // dependendo do estado do jogo, vai desenhar o background, os personagens, as paredes e os botões

#endif 