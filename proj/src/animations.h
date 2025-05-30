#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <lcom/lcf.h>
#include <lcom/xpm.h>

// Animation lists
extern xpm_image_t attack_frames[];
extern xpm_image_t idle_frames[];
extern xpm_image_t run_frames[];

// Function prototypes
void load_animations(); // Load all animation assets
void play_animation(xpm_image_t frames[], size_t frame_count, uint16_t x, uint16_t y, uint16_t delay); // Play an animation

void test_animations();
#endif // ANIMATIONS_H
