#ifndef UI_BATTERY_H
#define UI_BATTERY_H
#include "../../../include/magi_ipc.h"
#include "include/lvgl/lv_types.h"
#include "lvgl/lvgl.h"
#include <stdint.h>

// to be passed to main.c
typedef struct {
  magi_battery_data_t *battery_daemon_info;
  lv_obj_t *main_label;
  int current_ui_sec_elapsed;
  int current_frame_index;
} ui_context_t;

// Function signatures for main.c to use

/**
 * @brief create_battery_label creates a pointer to a label object, centers it
 * to the screen, and returns a pointer to said label object.
 *
 * @param parent passed in ui_manager.c
 * @return pointer to newly created battery label object
 *
 */
lv_obj_t *create_battery_label(lv_obj_t *parent);

/**
 * @brief init_battery_context creates a ui context struct to pass into the lv
 * timer in ui_manager.c That holds the battery daemon info along with info on
 * the current frame (0-(FPS -1)inclusive) and the current "naive" ui seconds
 * elapsed. See render_battery_ui function for the "naive" ui seconds
 * explanation. Will also set up the render_battery_ui as a call back function
 * and thus start rendering the UI implictly once initialized.
 * @param label  passed in ui_manager.c
 * @return pointer to the initialized ui context struct containing the battery
 * info or error otherwise.
 */
ui_context_t *init_battery_context(lv_obj_t *label);

/**
 * @brief setup_battery_ui will first initialize the static parts of the ui like
 * the gradient background then call the render_battery_ui function to
 * dynamically draw the updating information. this function will be called by
 * ui_manager.c whenever the battery ui should be displayed.
 *
 * @param parent_screen can be any lv_obj_t including the active or parent
 * screen itself
 */
void setup_battery_ui(lv_obj_t *parent_screen);

/**
 * @brief render_battery_ui gets the pointer to the lv timer then will update
 * the remaining battery life remaining displayed every 1 second. This function
 * iterates which frame it is currently on from frame 0-FPS inclusive and
 * decrements the remaining time by 1 second after every FPS iterations.
 *
 * This function is essentially using a "naive ui timer" or dead reckoning
 * approach to prevent constantly overwriting the remaining timer on screen for
 * trivial changes to remaining time upon resampling. The threshold for
 * considering an update a "trivial" change is defined in magi_ipc.h as the
 * MAX_DEVIATION_SEC constant.
 * @param timer passed in ui_manager.c
 */
void render_battery_ui(lv_timer_t *timer);

#endif // UI_BATTERY_H
