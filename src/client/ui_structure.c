#include "ui_structure.h"
#include "include/lvgl/api_map/lv_api_map_v8.h"
#include "include/lvgl/core/lv_area.h"
#include "include/lvgl/core/lv_obj.h"
#include "magi_ipc.h"

const char *UI_STRUCT_SUBSYS = "UI Structure";

void apply_ui_container_structure(lv_obj_t *ui_cntr) {
  if (!ui_cntr) {
    MAGI_LOG_ERROR(UI_STRUCT_SUBSYS, "UI container pointer null.");
    return;
  }

  lv_obj_clear_flag(ui_cntr, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(ui_cntr, UI_WIDTH, UI_HEIGHT);
  lv_obj_center(ui_cntr);
}

void apply_rect_structure(lv_obj_t *rect) {
  if (!rect) {
    MAGI_LOG_ERROR(UI_STRUCT_SUBSYS, "Rect container pointer null.");
    return;
  }

  lv_obj_clear_flag(rect, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(rect, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_center(rect);
}
