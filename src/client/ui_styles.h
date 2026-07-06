#ifndef UI_STYLES_H
#define UI_STYLES_H

#include "include/lvgl/lv_types.h"
#include "lvgl/lvgl.h"
#include <stdint.h>

// color ref:
// https://zemnmez.medium.com/why-we-dont-have-uis-like-the-ones-in-neon-genesis-9b6631dc3714

// MAGI HEX COLORS
static const uint32_t MAGI_COLOR_BLACK = 0x000000;
static const uint32_t MAGI_COLOR_RED = 0xBB0304;
static const uint32_t MAGI_COLOR_ORANGE = 0xEE950B;

// battery specific ui colors
static const uint32_t BATTERY_START_GRAD_RED = 0x821F06;
static const uint32_t BATTERY_END_GRAD_GREEN = 0X4A7414;
static const uint32_t BATTERY_END_GRAD_PINK = 0x625C94;

// mainly for battery UI gradients but probably useful later
static const uint32_t GRAD_RED = 0x861d09, GRAD_ORANGE = 0x964516,
                      GRAD_YELLOW = 0xb68b26, GRAD_GREEN_1 = 0x888918,
                      GRAD_GREEN_2 = 0x567b10, GRAD_TEAL = 0x4c6e49,
                      GRAD_PURP = 0x645e97;

#define NUM_COLORS_RAINBOW 7
static const uint32_t rainbow_hex[NUM_COLORS_RAINBOW] = {
    GRAD_RED,     GRAD_ORANGE, GRAD_YELLOW, GRAD_GREEN_1,
    GRAD_GREEN_2, GRAD_TEAL,   GRAD_PURP};

static const lv_opa_t MAGI_TEXT_OPACITY = 10;                        // percent
static const int32_t MAGI_TEXT_OFFSET_X = 2, MAGI_TEXT_OFFSET_Y = 2; // px

static const uint32_t RECT_BORDER_WIDTH = 2; // px
static const uint32_t RECT_PADDING = 25;

// is being used as a lv_style_selector_t
static const lv_style_selector_t DEFAULT_STATE = 0;

// 7 Segment Fonts
extern const lv_font_t seven_segment_font; // size 16
extern const lv_font_t lv_font_7seg_400;   // size 400
extern const lv_font_t lv_font_7seg_300;   // size 300
extern const lv_font_t lv_font_7seg_200;   // size 200
extern const lv_font_t lv_font_7seg_175;   // size 175

// EN/JP NOTO Fonts for all text //includes kanji for battery daemon
extern const lv_font_t lv_font_noto_150;
extern const lv_font_t lv_font_noto_40;

// Object style's getter functions

/**
 * @brief checks if styles have been intialized yet. If so, allow the follwing
 * functions to return their intended pointers. If not, initialize all styles by
 * calling init_magi_styles().
 */
void initialize_styles_check(void);

/**
 * @brief serves as the parent object to attach the rest of the ui elements to.
 * using this instead of the actual parent screen to make preserving my desired
 * aspect ratio and other sizing stuff easier. a black background with 0
 * border.
 *
 * @return pointer to ui container style
 */
lv_style_t *get_magi_ui_container(void);

/**
 * @brief style object that provides a black rectangle with a magi-orange
 * border of width RECT_BORDER_WIDTH (in px) and RECT_PADDING padding on all
 * sides.
 *
 * @return pointer to magi_rect style.
 */
lv_style_t *get_magi_rect(void);

/**
 * @brief style object that provides text with MAGI_COLOR_ORANGE with slight
 * offsets to emulate the reference bloom.
 *
 * @return a pointer to magi_text style.
 */
lv_style_t *get_magi_text(void);

/**
 * @brief procedurally generated style object for the font specificed as an
 * argument
 *
 * @param pointer to lv_font_t
 * @return pointer to generated magi_font style for specified font
 */
lv_style_t *get_magi_font(const lv_font_t *font);

/**
 * @brief initializes all style objects
 */
void init_magi_styles(void);

// Function Signatures

// battery specific functions
/**
 * @brief applies a 7-color gradient starting from red and ending at purple on
 * the ui container element for the battery ui. will implictly apply the
 * magi_ui_container style to the ui_container object as well.
 *
 * @param pinter to ui container object
 */
void apply_rainbow_gradient(lv_obj_t *ui_container);

#endif // UI_STYLES_H
