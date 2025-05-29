#include "xpms/background.xpm"  // Certifica-te que este ficheiro XPM existe e tem o nome correto
#include <lcom/lcf.h>
#include <lcom/xpm.h>

#include "game.h"
#include "controllers/video/graphics.h"

uint8_t *bg_game;
xpm_image_t game_bg;

void load_game_assets() {
    bg_game = xpm_load(background_xpm, XPM_5_6_5, &game_bg);
    if (!bg_game)
        printf("Failed to load game background XPM!\n");
}

void draw_game() {
vg_draw_scaled_pixmap(bg_game, game_bg.width, game_bg.height, (int)xpm_source_bpp,
                      0, 0, mode_info.XResolution, mode_info.YResolution);

}
