// Copyright 2024 suikagiken (@suikagiken)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,     KC_D, KC_F,      KC_I, KC_K, KC_M,
        KC_B, KC_C, KC_E, KC_G, KC_H, KC_J, KC_L, KC_N, KC_O
    )
};
