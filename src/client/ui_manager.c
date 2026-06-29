#include "components/battery/ui_battery.h"
#include "include/lvgl/api_map/lv_api_map_v8.h"
#include "include/lvgl/core/lv_obj.h"
#include "ui_styles.h"

// Forward declaration so main.c can call this
void setup_main_ui(void);

void setup_main_ui(void) {
  lv_obj_t *active_screen = lv_screen_active();
  lv_obj_clear_flag(active_screen,
                    LV_OBJ_FLAG_SCROLLABLE); // prevents crashes as well

  setup_battery_ui(active_screen);
}
