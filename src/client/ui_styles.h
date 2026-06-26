#ifndef UI_STYLES_H
#define UI_STYLES_H

#include "lvgl/lvgl.h"
#include <stdint.h>

// Timing Constants
static const uint32_t RENDER_FPS = 24;
static const uint32_t FPS_REFRESH_MS = 1000 / 24;

// MAGI Style Constants
static const uint32_t MAGI_COLOR_ORANGE = 0xFF9900;
static const uint32_t MAGI_COLOR_BLACK = 0x000000;

// Fonts
extern const lv_font_t seven_segment_font;
extern const lv_font_t lv_font_7seg_400;
extern const lv_font_t lv_font_noto_150;
extern const lv_font_t lv_font_noto_40;

// Function Signatures
void apply_magi_label_style(lv_obj_t *label, const lv_font_t *font);

#endif // UI_STYLES_H
