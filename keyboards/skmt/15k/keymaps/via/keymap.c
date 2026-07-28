// Copyright 2022 Jimmy Lye (@satorusaka)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬─────────────────────┐
     * │ Q │ W │ E │ R │ BACKSPACE (LAYER 1) │
     * ├───┼───┼───┼───┼─────────────────────┤
     * │ A │ S │ D │ F │ ENTER               │
     * ├───┼───┼───┼───┼─────────────────────┤
     * │ Z │ X │ C │ V │ SPACE               │
     * └───┴───┴───┴───┴─────────────────────┘
     */
    [0] = LAYOUT_default(
        KC_Q,   KC_W,   KC_E,   KC_R,   LT(1, KC_BSPC),
        KC_A,   KC_S,   KC_D,   KC_F,   LT(2, KC_ENT),
        KC_Z,   KC_X,   KC_C,   KC_V,   LT(3, KC_SPC)
    ),
    [1] = LAYOUT_default(
        RM_TOGG,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        RM_NEXT,RM_HUEU,RM_SATU,RM_VALU,RM_SPDU,
        RM_PREV,RM_HUED,RM_SATD,RM_VALD,RM_SPDD
    ),
    [2] = LAYOUT_default(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
    ),
    [3] = LAYOUT_default(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
    )
};
