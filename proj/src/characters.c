#include "xpms/selected1.xpm"
#include "xpms/selected2.xpm"
#include "xpms/selected3.xpm"

#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include "characters.h"
#include "gameState.h"
#include "controllers/video/graphics.h"

uint8_t *sel2, *sel3;
xpm_image_t selected2, selected3;

void load_characters2_assets(){
    sel2 = xpm_load(selected2_xpm, XPM_5_6_5, &selected2);
}

void draw_characters2(){
    vg_draw_scaled_pixmap(sel2, selected2.width, selected2.height, 2, 0, 0, mode_info.XResolution, mode_info.YResolution);
}

void load_characters3_assets(){
    sel3 = xpm_load(selected3_xpm, XPM_5_6_5, &selected3);
}

void draw_characters3(){
    vg_draw_scaled_pixmap(sel3, selected3.width, selected3.height, 2, 0, 0, mode_info.XResolution, mode_info.YResolution);
}
