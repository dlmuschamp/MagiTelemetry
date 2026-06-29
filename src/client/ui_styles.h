#ifndef UI_STYLES_H
#define UI_STYLES_H

#include "include/lvgl/draw/lv_grad.h"
#include "include/lvgl/lv_types.h"
#include "lvgl/lvgl.h"
#include <stdint.h>

// color ref:
// https://zemnmez.medium.com/why-we-dont-have-uis-like-the-ones-in-neon-genesis-9b6631dc3714

// Timing Constants
static const uint32_t RENDER_FPS = 24;
static const uint32_t FPS_REFRESH_MS = 1000 / 24;

// MAGI HEX COLORS
static const uint32_t MAGI_COLOR_BLACK = 0x000000;
static const uint32_t MAGI_COLOR_RED = 0xBB0304;
static const uint32_t MAGI_COLOR_ORANGE = 0xEE950B;

static const uint32_t BATTERY_START_GRAD_RED = 0x821F06;
static const uint32_t BATTERY_END_GRAD_GREEN = 0X4A7414;

static const lv_style_selector_t DEFAULT_STATE = 0;

// 7 Segment Fonts
extern const lv_font_t seven_segment_font; // size 16
extern const lv_font_t lv_font_7seg_400;   // size 400
extern const lv_font_t lv_font_7seg_300;   // size 300
extern const lv_font_t lv_font_7seg_200;   // size 200
extern const lv_font_t lv_font_7seg_175;   // size 200

// EN/JP NOTO Fonts for all text
extern const lv_font_t lv_font_noto_150;
extern const lv_font_t lv_font_noto_40;

// Function Signatures

/**
 * @brief apply_label_font_and_color will set the lvgl text object's font and
 * color to the hex color argument and a font from ui_styles.h
 *
 * @param label created in the ui_telemetryType.c
 * @param font from ui_styles.h. pass the address of the font using &.
 * @param color passed from ui_telemetryType.c. Can either be a custom hex color
 * or one defined from ui_styles.h
 */
void apply_label_font_and_color(lv_obj_t *label, const lv_font_t *font,
                                const uint32_t color);

/**
 * @brief will apply a background gradient to the passed object (which can be an
 * active screen). will start gradient with START_COLOR and end with
 * FINISH_COLOR following the direction set by dir.
 *
 * @param active_screen
 * @param START_COLOR hex color
 * @param FINISH_COLOR hex color
 * @param dir an enum that can be set to either LV_GRAD_DIR_NONE,
 * LV_GRAD_DIR_HOR, LV_GRAD_DIR_VER and others as listed here:
 * https://lvgl.io/docs/open/api/draw/lv_grad_h
 */
void apply_bg_grad(lv_obj_t *obj, const uint32_t START_COLOR,
                   const uint32_t FINISH_COLOR, lv_grad_dir_t dir);
#endif // UI_STYLES_H
