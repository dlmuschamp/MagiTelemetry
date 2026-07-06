
/**
 * Handles all of the structural aspects of the UI. Does not handle any of the
 * styling. Handles all of the physical constraints as well like RENDER_FPS,
 * ASPECT_RATIO, and timing constants.
 */

#ifndef UI_STRUCTURE_H
#define UI_STRUCTURE_H

// include
#include "lvgl/lvgl.h"

// screen constants
static const uint32_t HOR_RES = 1920, VER_RES = 1200; // px

// UI will have a 21:9 aspect ratio.
static const double ASPECT_W = 21.0, ASPECT_H = 9.0;
static const double ASPECT_RATIO = ASPECT_W / ASPECT_H;
static const int UI_WIDTH = HOR_RES, UI_HEIGHT = HOR_RES * (1.0 / ASPECT_RATIO);

// Timing Constants
static const uint32_t RENDER_FPS = 24;
static const uint32_t FPS_REFRESH_MS = 1000 / RENDER_FPS;

// all functions disable the LV_OBJ_FLAG_SCROLLABLE flag for simplicity

/**
 * @brief Sets the ui container's size to UI_WIDTH * UI_HEIGHT, centers it.
 */
void apply_ui_container_structure(lv_obj_t *ui_container);

/**
 * @brief sets the object size to LV_SIZE_CONTENT constants and centers the box.
 */
void apply_rect_structure(lv_obj_t *rect);

#endif
