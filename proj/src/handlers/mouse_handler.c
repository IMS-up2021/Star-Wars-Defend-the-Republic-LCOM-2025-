#include <math.h>
#include "mouse_handler.h"
#include "menu.h"
#include "gameState.h"

Button *play_button;
Button *instruction_button;
Button *exit_button;

Button *pause_button;
Button *faster_button;
Button *slower_button;

Button *back_button;

Position mouse_pos;


bool mouse_over_button(Position mouse, Button *btn) {
    return mouse.x >= btn->pos_x && mouse.x <= btn->pos_x + btn->width &&
           mouse.y >= btn->pos_y && mouse.y <= btn->pos_y + btn->height;
}


void mouse_event_handler(struct packet pp) {
    switch (state) {

        case MAIN_MENU:
            update_mouse(pp.delta_x, pp.delta_y);
            if (!pp.lb) return;

            if (mouse_over_button(mouse_pos, play_button)) play_button->on_click();
            else if (mouse_over_button(mouse_pos, exit_button)) exit_button->on_click();
            else if (mouse_over_button(mouse_pos, instruction_button)) instruction_button->on_click();
            
            break;

        case PLAYING:
            update_mouse(pp.delta_x, pp.delta_y);
            if (!pp.lb) return;

            if (mouse_over_button(mouse_pos, pause_button)) pause_button->on_click(); 
            else if (mouse_over_button(mouse_pos, faster_button)) faster_button->on_click();
            else if (mouse_over_button(mouse_pos, slower_button)) slower_button->on_click();
            
            
            // falta meter a lógica das setas verdes, para dar spawn do personagem

            break;

        case INSTRUCTIONS:
            update_mouse(pp.delta_x, pp.delta_y);
            if (!pp.lb) return;

            if (mouse_over_button(mouse_pos, back_button)) back_button->on_click();
            break;

        case EXIT:
            break;
    }
}
