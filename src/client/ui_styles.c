#include "ui_styles.h"
#include "include/lvgl/api_map/lv_api_map_v8.h"
#include "include/lvgl/core/lv_obj_style.h"
#include "include/lvgl/core/lv_obj_style_gen.h"
#include "include/lvgl/core/lv_style.h"
#include "include/lvgl/core/lv_style_gen.h"
#include "include/lvgl/draw/lv_color.h"
#include "include/lvgl/draw/lv_grad.h"
#include "magi_ipc.h"
#include <stdint.h>

// Style Object Definitions
// magi is for more general styles
static lv_style_t magi_ui_container;
static lv_style_t magi_rect;
static lv_style_t magi_text;

static bool is_styles_initialized = false;

// Style functions

// style initializer
void init_magi_styles(void) {
  if (is_styles_initialized) {
    return;
  }

  // magi ui_container
  lv_style_init(&magi_ui_container);
  lv_style_set_bg_color(&magi_ui_container, lv_color_hex(MAGI_COLOR_BLACK));
  lv_style_set_border_width(&magi_ui_container, 0);
  lv_style_set_bg_opa(&magi_ui_container, LV_OPA_COVER);
  lv_style_set_outline_width(&magi_ui_container, 0);
  lv_style_set_shadow_width(&magi_ui_container, 0);

  // magi rect
  lv_style_init(&magi_rect);
  lv_style_set_bg_color(&magi_rect, lv_color_hex(MAGI_COLOR_BLACK));
  lv_style_set_border_color(&magi_rect, lv_color_hex(MAGI_COLOR_ORANGE));
  lv_style_set_border_width(&magi_rect, RECT_BORDER_WIDTH);
  lv_style_set_pad_all(&magi_rect, RECT_PADDING);

  // magi text
  lv_style_init(&magi_text);
  lv_style_set_text_color(&magi_text, lv_color_hex(MAGI_COLOR_ORANGE));
  lv_style_set_text_font(&magi_text, &lv_font_noto_40);

  // bloom stuff for text
  lv_style_set_shadow_color(&magi_text, lv_color_hex(MAGI_COLOR_ORANGE));
  lv_style_set_shadow_opa(&magi_text, MAGI_TEXT_OPACITY);
  lv_style_set_shadow_offset_x(&magi_text, MAGI_TEXT_OFFSET_X);
  lv_style_set_shadow_offset_y(&magi_text, MAGI_TEXT_OFFSET_Y);
  lv_style_set_shadow_width(&magi_text, 0);

  is_styles_initialized = true;
}

// getters and check to see if already intialized
void initialize_styles_check(void) {
  if (!is_styles_initialized) {
    init_magi_styles();
  }
}

// gets pointers to the style objects
lv_style_t *get_magi_ui_container(void) {
  initialize_styles_check();
  return &magi_ui_container;
}

lv_style_t *get_magi_rect(void) {
  initialize_styles_check();
  return &magi_rect;
}

lv_style_t *get_magi_text(void) {
  initialize_styles_check();
  return &magi_text;
}

lv_style_t *get_magi_font(const lv_font_t *font) {
  initialize_styles_check();
  static lv_style_t magi_font;
  lv_style_init(&magi_font);
  lv_style_set_text_font(&magi_font, font);
  return &magi_font;
}

// Globals
static const char *UI_SUBSYS = "UI STYLES SUBSYSTEM";

void apply_rainbow_gradient(lv_obj_t *ui_container) {
  static lv_color_t rbw_grad_colors[NUM_COLORS_RAINBOW];
  for (int i = 0; i < NUM_COLORS_RAINBOW; i++) {
    rbw_grad_colors[i] = lv_color_hex(rainbow_hex[i]);
  }

  static const uint8_t fracs[NUM_COLORS_RAINBOW] = {0,   42,  85, 127,
                                                    170, 212, 255};
  static lv_grad_dsc_t grad_dsc;
  lv_grad_init_stops(&grad_dsc, rbw_grad_colors, NULL, fracs,
                     sizeof(rainbow_hex) / sizeof(uint32_t));
  lv_grad_horizontal_init(&grad_dsc);

  lv_obj_set_style_bg_grad(ui_container, &grad_dsc, DEFAULT_STATE);
}

// gonig to be replaced with just styles
void apply_label_font_and_color(lv_obj_t *label, const lv_font_t *font,
                                const uint32_t color) {
  if (!label) {
    MAGI_LOG_ERROR(UI_SUBSYS, "Label pointer is null.");
    return;
  }

  if (!font) {
    MAGI_LOG_ERROR(UI_SUBSYS, "Font pointer is null.");
    return;
  }

  lv_obj_set_style_text_font(label, font, DEFAULT_STATE);
  lv_obj_set_style_text_color(label, lv_color_hex(color), DEFAULT_STATE);
}

// replace with styles
void apply_bg_grad(lv_obj_t *obj, const uint32_t START_COLOR,
                   const uint32_t END_COLOR, lv_grad_dir_t dir) {

  lv_obj_set_style_bg_color(obj, lv_color_hex(START_COLOR), DEFAULT_STATE);
  lv_obj_set_style_bg_grad_color(obj, lv_color_hex(END_COLOR), DEFAULT_STATE);
  lv_obj_set_style_bg_grad_dir(obj, dir, DEFAULT_STATE);
}
