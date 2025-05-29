#include "xpms/background.xpm"  // Certifica-te que este ficheiro XPM existe e tem o nome correto
#include <lcom/lcf.h>
#include <lcom/xpm.h>

#include "game.h"
#include "controllers/video/graphics.h"

uint8_t *bg_game;
xpm_image_t game_bg;

PlayState play_state = PLAY_NORMAL;

void set_play_state(PlayState new_state) {
    play_state = new_state;

    switch (new_state) {
        case PLAY_PAUSED:
            printf("Game paused.\n");
            break;
        case PLAY_NORMAL:
            printf("Game resumed at normal speed.\n");
            break;
        case PLAY_FAST:
            printf("Game set to fast speed.\n");
            break;
    }
}

void load_game_assets() {
    bg_game = xpm_load(background_xpm, XPM_5_6_5, &game_bg);
    if (!bg_game)
        printf("Failed to load game background XPM!\n");
}

void draw_game() {
vg_draw_scaled_pixmap(bg_game, game_bg.width, game_bg.height, (int)xpm_source_bpp,
                      0, 0, mode_info.XResolution, mode_info.YResolution);

}
