#ifndef UI_BATTERY_H
#define UI_BATTERY_H
#include "../../../include/magi_ipc.h"
#include "lvgl/lvgl.h"

// to be passed to main.c
typedef struct {
  magi_battery_data_t *battery_daemon_info;
  lv_obj_t *main_label;
  int current_ui_sec;
  int current_frame_index;
} ui_context_t;

// Function signatures for main.c to use
void render_battery(lv_timer_t *timer);
lv_obj_t *create_battery_label(lv_obj_t *parent);
ui_context_t *init_battery_context(lv_obj_t *label);
void render_battery(lv_timer_t *timer);

#endif // UI_BATTERY_H
