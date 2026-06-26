#include "components/battery/ui_battery.h"
#include "ui_styles.h"

// Forward declaration so main.c can call this
void setup_main_ui(void);

void setup_main_ui(void) {
  lv_obj_t *active_screen = lv_screen_active();

  // Set background using the style constant
  lv_obj_set_style_bg_color(active_screen, lv_color_hex(MAGI_COLOR_BLACK),
                            LV_PART_MAIN);

  // Build the label via the component
  lv_obj_t *bat_label = create_battery_label(active_screen);

  // Apply styles to it using our style function
  apply_magi_label_style(bat_label, &seven_segment_font);
  lv_label_set_text(bat_label, "MAGI SYSTEM:\nAWAITING DATA....");

  // Register the logic
  init_battery_context(bat_label);
}
