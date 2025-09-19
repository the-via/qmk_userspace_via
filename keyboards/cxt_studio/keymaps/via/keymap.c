/* Copyright 2023 Brian McKenna
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_ESC, KC_F11, KC_NO, KC_MSTP,
        KC_NO, KC_NO, KC_MRWD, KC_MFFD,
        KC_NO, KC_MPLY, KC_MPLY, KC_MNXT,

        KC_MUTE, KC_NO, KC_NO, RGB_M_G
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t index_to_light = NO_LED;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 1:
            index_to_light = 3;
            break;
        case 2:
            index_to_light = 2;
            break;
        case 3:
            index_to_light = 1;
            break;
        case 4:
            index_to_light = 0;
            break;
        default:
            break;
    }

    // Light up only the selected LED if it's within the current render range
    if (index_to_light != NO_LED && index_to_light >= led_min && index_to_light < led_max) {
        rgb_matrix_set_color(index_to_light, RGB_GREEN); // You can choose any color
    }

    return false;  // Let other lighting effects (if any) still apply
}