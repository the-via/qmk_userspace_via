// Copyright 2024 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "binepad_common.h"
#include "bnk8.h"

#ifdef CAFFEINE_ENABLE
#    include "caffeine.h"
#    define COFFEE KC_CAFFEINE_TOGGLE
#endif // CAFFEINE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 1 │ 2 │(K)│
     * ├───┼───┼───┤
     * │ 3 │ 4 │ 5 │
     * ├───┼───┼───┤
     * │ 6 │ 7 │ 8 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x3(
        KC_P1,    KC_P2,    KC_MUTE,
        KC_P3,    KC_P4,    KC_P5,
        KC_P6,    KC_P7,    LT(1, KC_P8)
    ),
    [1] = LAYOUT_ortho_3x3(
        RM_HUEU, RM_SATU, RM_SPDU,
        RM_HUED, RM_SATD, RM_SPDD,
        RM_TOGG, RM_NEXT, _______
    )
};
// clanf-format on

#ifdef ENCODER_MAP_ENABLE

// clanf-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
// clanf-format on

#endif // ENCODER_MAP_ENABLE

// ---------- Optional Add-ons -----------

#if defined(CAFFEINE_ENABLE)

#    ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_user(void) {
#        ifdef CAFFEINE_ENABLE
    if (!rgb_matrix_indicators_caffeine()) return false;
#        endif
    return true;
}

bool led_update_user(led_t led_state) {
#    ifdef CAFFEINE_ENABLE
    if (!led_update_caffeine(led_state)) return false;
#    endif
    return true;
}

#    endif // RGB_MATRIX_ENABLE

void matrix_scan_user(void) {
#    ifdef CAFFEINE_ENABLE
    matrix_scan_caffeine();
#    endif
}

void housekeeping_task_user(void) {
#    ifdef CAFFEINE_ENABLE
    housekeeping_task_caffeine();
#    endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#    ifdef CAFFEINE_ENABLE
        case KC_CAFFEINE_TOGGLE:
          return caffeine_process_toggle_keycode(record);
          break;
#    endif
        default: break;
    }
    return true;
}

#endif // CAFFEINE_ENABLE
