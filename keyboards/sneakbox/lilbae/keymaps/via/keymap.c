/*
Copyright 2022 Bryan Ong

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _L3,
    _L4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_all(
              KC_NO,
    KC_ESC, KC_ENT, KC_LGUI),

    [_FN]   = LAYOUT_all(
              KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS),

    [_L3]   = LAYOUT_all(
              KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS),

    [_L4]   = LAYOUT_all(
              KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_1, KC_2)},
    [_FN]   = { ENCODER_CCW_CW(KC_1, KC_2)},
    [_L3]   = { ENCODER_CCW_CW(KC_1, KC_2)},
    [_L4]   = { ENCODER_CCW_CW(KC_1, KC_2)}
};
#endif
