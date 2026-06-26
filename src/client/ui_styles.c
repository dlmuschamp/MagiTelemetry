#include "ui_styles.h"

void apply_magi_label_style(lv_obj_t *label, const lv_font_t *font) {
  // Apply the exact MAGI orange color using the constant defined in your header
  lv_obj_set_style_text_color(label, lv_color_hex(MAGI_COLOR_ORANGE),
                              LV_PART_MAIN);

  // Apply the passed font
  lv_obj_set_style_text_font(label, font, 0);
}
