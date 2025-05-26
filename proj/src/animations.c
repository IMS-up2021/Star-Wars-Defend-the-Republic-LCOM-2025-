#include "animations.h"
#include "xpms/attack_1.xpm"
#include "xpms/attack_2.xpm"
#include "xpms/attack_3.xpm"
#include "xpms/attack_4.xpm"
#include "xpms/attack_5.xpm"
#include "xpms/idle_1.xpm"
#include "xpms/run_1.xpm"
#include "xpms/run_2.xpm"
#include "xpms/run_3.xpm"
#include "xpms/run_4.xpm"
#include "xpms/run_5.xpm"
#include "xpms/death_1.xpm"
#include "xpms/death_2.xpm"
#include "xpms/death_3.xpm"

// Animation lists
xpm_image_t attack_frames[5];
xpm_image_t idle_frames[1];
xpm_image_t run_frames[5];
xpm_image_t death_frames[3];

// Load all animation assets
void load_animations() {
    // Load attack animation frames
    xpm_load(attack_1_xpm, XPM_8_8_8_8, &attack_frames[0]);
    xpm_load(attack_2_xpm, XPM_8_8_8_8, &attack_frames[1]);
    xpm_load(attack_3_xpm, XPM_8_8_8_8, &attack_frames[2]);
    xpm_load(attack_4_xpm, XPM_8_8_8_8, &attack_frames[2]);
    xpm_load(attack_5_xpm, XPM_8_8_8_8, &attack_frames[2]);

    // Load idle animation frames
    xpm_load(idle_1_xpm, XPM_8_8_8_8, &idle_frames[0]);

    // Load run animation frames
    xpm_load(run_1_xpm, XPM_8_8_8_8, &run_frames[0]);
    xpm_load(run_2_xpm, XPM_8_8_8_8, &run_frames[1]);
    xpm_load(run_3_xpm, XPM_8_8_8_8, &run_frames[1]);
    xpm_load(run_4_xpm, XPM_8_8_8_8, &run_frames[1]);
    xpm_load(run_5_xpm, XPM_8_8_8_8, &run_frames[1]);

    // Load death animation frames
    xpm_load(death_1_xpm, XPM_8_8_8_8, &death_frames[0]);
    xpm_load(death_2_xpm, XPM_8_8_8_8, &death_frames[1]);
    xpm_load(death_3_xpm, XPM_8_8_8_8, &death_frames[2]);

    // Add more animations as needed
}

// Play an animation
void play_animation(xpm_image_t frames[], size_t frame_count, uint16_t x, uint16_t y, uint16_t delay) {
    for (size_t i = 0; i < frame_count; i++) {
        // Draw the current frame
        for (uint16_t row = 0; row < frames[i].height; row++) {
            for (uint16_t col = 0; col < frames[i].width; col++) {
                uint32_t color = *(uint32_t *)(frames[i].bytes + (row * frames[i].width + col) * 4);
                vg_draw_pixel(x + col, y + row, color);
            }
        }

        // Wait for the delay (in milliseconds)
        tickdelay(micros_to_ticks(delay * 1000));
    }
}


void test_animations() {
    // Load all animations
    load_animations();

    // Clear the screen (optional, depending on your graphics implementation)
    vg_draw_rectangle(0, 0, 1024, 768, 0x000000); // Assuming a 1024x768 resolution and black background

    // Display attack animation
    play_animation(attack_frames, 5, 100, 100, 100); // 100 ms delay between frames

    // Display idle animation
    play_animation(idle_frames, 1, 300, 100, 200); // 200 ms delay between frames

    // Display run animation
    play_animation(run_frames, 5, 500, 100, 100); // 100 ms delay between frames

    // Display death animation
    play_animation(death_frames, 3, 700, 100, 150); // 150 ms delay between frames
}
