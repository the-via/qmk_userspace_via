// Copyright 2023 Silvino Rodrigues (@silvinorodr)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

void matrix_scan_caffeine(void);
void housekeeping_task_caffeine(void);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_caffeine(void);
bool led_update_caffeine(led_t led_state);
#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_caffeine(void);
void eeconfig_init_caffeine(void);

bool caffeine_process_toggle_keycode(keyrecord_t *record);
