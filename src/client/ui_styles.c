#include "ui_styles.h"
#include "include/lvgl/core/lv_obj_style.h"
#include "include/lvgl/core/lv_obj_style_gen.h"
#include "include/lvgl/draw/lv_color.h"
#include "magi_ipc.h"
#include <stdint.h>

const char *UI_SUBSYS = "UI STYLES SUBSYSTEM";

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

void apply_bg_grad(lv_obj_t *obj, const uint32_t START_COLOR,
                   const uint32_t END_COLOR, lv_grad_dir_t dir) {

  lv_obj_set_style_bg_color(obj, lv_color_hex(START_COLOR), DEFAULT_STATE);
  lv_obj_set_style_bg_grad_color(obj, lv_color_hex(END_COLOR), DEFAULT_STATE);
  lv_obj_set_style_bg_grad_dir(obj, dir, DEFAULT_STATE);
}
