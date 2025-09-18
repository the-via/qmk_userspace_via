/* Copyright 2025 BlindAssassin111
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
#include "util.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [0] = LAYOUT_splitbs_splitshift_ansi_7u(
    KC_F1,    KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,         KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,    KC_DEL,
    KC_F2,    KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y,         KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,            KC_HOME,
    KC_F3,    KC_CAPS, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H,         KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,             KC_PGUP,
    KC_F4,    KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N,         KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(2),                       KC_PGDN,
                       KC_LCTL, KC_LALT,                   LT(1,KC_SPC),                                 KC_RALT, KC_RCTL
    ),

    [1] = LAYOUT_splitbs_splitshift_ansi_7u(
    _______,        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______, _______,        _______,
    _______,        _______, _______, _______,  KC_UP,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,
    _______,        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______,          _______,                 _______,
    _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                          _______,
                             _______, _______,                            _______,                                     _______, _______
    ),

    [2] = LAYOUT_splitbs_splitshift_ansi_7u(
    QK_BOOT,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
    _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,
    _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                 _______,
    _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                          _______,
                             _______, _______,                            _______,                                     _______, _______
    )
    // clang-format on
};

#ifdef RGB_MATRIX_ENABLE

typedef struct _single_indicator_config_t {
    uint8_t h; // Indicator
    uint8_t s;
    uint8_t v;
    bool    dual;
    uint8_t h_dual;
    uint8_t s_dual;
    bool    rest; // Static Color
    uint8_t h_rest;
    uint8_t s_rest;
    uint8_t v_rest;
    bool    choice;
} single_indicator_config;

typedef struct _dual_indicator_config_t {
    uint8_t h_1; // Indicator 1
    uint8_t s_1;
    uint8_t v_1;
    bool    dual_1;
    uint8_t h_dual_1;
    uint8_t s_dual_1;
    uint8_t h_2; // Indicator 2
    uint8_t s_2;
    uint8_t v_2;
    bool    dual_2;
    uint8_t h_dual_2;
    uint8_t s_dual_2;
    bool    rest; // Static Color
    uint8_t h_rest;
    uint8_t s_rest;
    uint8_t v_rest;
} dual_indicator_config;

typedef struct {
    single_indicator_config top;
    single_indicator_config mid;
    dual_indicator_config   btm;
} vkr94_config_t;

// Check if the size of the reserved persistent memory is the same as the size of struct vkr94_config_t
_Static_assert(sizeof(vkr94_config) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");

vkr94_config_t vkr94;

void eeconfig_init_user(void) {
    // Default values
    vkr94.top.h        = 0;
    vkr94.top.s        = 0;
    vkr94.top.v        = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    vkr94.top.dual     = false;
    vkr94.top.h_dual   = 0;
    vkr94.top.s_dual   = 0;
    vkr94.top.rest     = false;
    vkr94.top.h_rest   = 0;
    vkr94.top.s_rest   = 0;
    vkr94.top.v_rest   = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    vkr94.top.choice   = false;
    vkr94.mid.h        = 0;
    vkr94.mid.s        = 0;
    vkr94.mid.v        = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    vkr94.mid.dual     = false;
    vkr94.mid.h_dual   = 0;
    vkr94.mid.s_dual   = 0;
    vkr94.mid.rest     = false;
    vkr94.mid.h_rest   = 0;
    vkr94.mid.s_rest   = 0;
    vkr94.mid.v_rest   = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    vkr94.mid.choice   = false;
    vkr94.btm.h_1      = 0;
    vkr94.btm.s_1      = 0;
    vkr94.btm.v_1      = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    vkr94.btm.dual_1   = false;
    vkr94.btm.h_dual_1 = 0;
    vkr94.btm.s_dual_1 = 0;
    vkr94.btm.h_2      = 0;
    vkr94.btm.s_2      = 0;
    vkr94.btm.v_2      = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    vkr94.btm.dual_2   = false;
    vkr94.btm.h_dual_2 = 0;
    vkr94.btm.s_dual_2 = 0;
    vkr94.btm.rest     = false;
    vkr94.btm.h_rest   = 0;
    vkr94.btm.s_rest   = 0;
    vkr94.btm.v_rest   = RGB_MATRIX_MAXIMUM_BRIGHTNESS;

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&vkr94);
}

// On Keyboard startup
void keyboard_post_init_user(void) {
    // Read our custom menu variables from memory
    eeconfig_read_kb_datablock(&vkr94);
}

// Declaring enums for VIA config menu
enum via_vkr94 {
    // clang-format off
    id_top_rest = 1,
    id_top_rest_brightness = 2,
    id_top_rest_color = 3,
    id_mid_rest = 4,
    id_mid_rest_brightness = 5,
    id_mid_rest_color = 6,
    id_btm_rest = 7,
    id_btm_rest_brightness = 8,
    id_btm_rest_color = 9,
    id_top_choice = 10,
    id_top_brightness = 11,
    id_top_color = 12,
    id_top_dual = 13,
    id_top_color_2 = 14,
    id_mid_choice = 15,
    id_mid_brightness = 16,
    id_mid_color = 17,
    id_mid_dual = 18,
    id_mid_color_2 = 19,
    id_btm_1_brightness = 20,
    id_btm_1_color = 21,
    id_btm_1_dual = 22,
    id_btm_1_color_2 = 23,
    id_btm_2_brightness = 24,
    id_btm_2_color = 25,
    id_btm_2_dual = 26,
    id_btm_2_color_2 = 27
    // clang-format on
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv_top_color      = {vkr94.top.h, vkr94.top.s, vkr94.top.v};
    HSV hsv_top_color_2    = {vkr94.top.h_dual, vkr94.top.s_dual, vkr94.top.v};
    HSV hsv_top_color_rest = {vkr94.top.h_rest, vkr94.top.s_rest, vkr94.top.v_rest};
    HSV hsv_mid_color      = {vkr94.mid.h, vkr94.mid.s, vkr94.mid.v};
    HSV hsv_mid_color_2    = {vkr94.mid.h_dual, vkr94.mid.s_dual, vkr94.mid.v};
    HSV hsv_mid_color_rest = {vkr94.mid.h_rest, vkr94.mid.s_rest, vkr94.mid.v_rest};
    HSV hsv_btm_1_color    = {vkr94.btm.h_1, vkr94.btm.s_1, vkr94.btm.v_1};
    HSV hsv_btm_1_color_2  = {vkr94.btm.h_dual_1, vkr94.btm.s_dual_1, vkr94.btm.v_1};
    HSV hsv_btm_2_color    = {vkr94.btm.h_2, vkr94.btm.s_2, vkr94.btm.v_2};
    HSV hsv_btm_2_color_2  = {vkr94.btm.h_dual_2, vkr94.btm.s_dual_2, vkr94.btm.v_2};
    HSV hsv_btm_color_rest = {vkr94.btm.h_rest, vkr94.btm.s_rest, vkr94.btm.v_rest};

    RGB rgb_top_color      = hsv_to_rgb(hsv_top_color);
    RGB rgb_top_color_2    = hsv_to_rgb(hsv_top_color_2);
    RGB rgb_top_color_rest = hsv_to_rgb(hsv_top_color_rest);
    RGB rgb_mid_color      = hsv_to_rgb(hsv_mid_color);
    RGB rgb_mid_color_2    = hsv_to_rgb(hsv_mid_color_2);
    RGB rgb_mid_color_rest = hsv_to_rgb(hsv_mid_color_rest);
    RGB rgb_btm_1_color    = hsv_to_rgb(hsv_btm_1_color);
    RGB rgb_btm_1_color_2  = hsv_to_rgb(hsv_btm_1_color_2);
    RGB rgb_btm_2_color    = hsv_to_rgb(hsv_btm_2_color);
    RGB rgb_btm_2_color_2  = hsv_to_rgb(hsv_btm_2_color_2);
    RGB rgb_btm_color_rest = hsv_to_rgb(hsv_btm_color_rest);

    // Top Bar
    if (host_keyboard_led_state().caps_lock) {
        if (vkr94.top.dual) {
            rgb_matrix_set_color(4, rgb_top_color_2.r, rgb_top_color_2.g, rgb_top_color_2.b);
        } else {
            rgb_matrix_set_color(4, rgb_top_color.r, rgb_top_color.g, rgb_top_color.b);
        }
        rgb_matrix_set_color(5, rgb_top_color.r, rgb_top_color.g, rgb_top_color.b);
    } else if (vkr94.top.rest) { // Default top LED bar color. Overrides vibe lighting.
        rgb_matrix_set_color(4, rgb_top_color_rest.r, rgb_top_color_rest.g, rgb_top_color_rest.b);
        rgb_matrix_set_color(5, rgb_top_color_rest.r, rgb_top_color_rest.g, rgb_top_color_rest.b);
    }

    // Middle Bar
    if (host_keyboard_led_state().scroll_lock && !vkr94.mid.choice) {
        if (vkr94.mid.dual) {
            rgb_matrix_set_color(3, rgb_mid_color_2.r, rgb_mid_color_2.g, rgb_mid_color_2.b);
        } else {
            rgb_matrix_set_color(3, rgb_mid_color.r, rgb_mid_color.g, rgb_mid_color.b);
        }
        rgb_matrix_set_color(2, rgb_mid_color.r, rgb_mid_color.g, rgb_mid_color.b);
    } else if (get_highest_layer(layer_state | default_layer_state) == 1 && vkr94.mid.choice) {
        if (vkr94.mid.dual) {
            rgb_matrix_set_color(3, rgb_mid_color_2.r, rgb_mid_color_2.g, rgb_mid_color_2.b);
        } else {
            rgb_matrix_set_color(3, rgb_mid_color.r, rgb_mid_color.g, rgb_mid_color.b);
        }
        rgb_matrix_set_color(2, rgb_mid_color.r, rgb_mid_color.g, rgb_mid_color.b);
    } else if (vkr94.mid.rest) { // Default middle LED bar color. Overrides vibe lighting.
        rgb_matrix_set_color(3, rgb_mid_color_rest.r, rgb_mid_color_rest.g, rgb_mid_color_rest.b);
        rgb_matrix_set_color(2, rgb_mid_color_rest.r, rgb_mid_color_rest.g, rgb_mid_color_rest.b);
    }

    // Bottom Bar
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 1:
            if (!vkr94.mid.choice) {
                if (vkr94.btm.dual_1) {
                    rgb_matrix_set_color(0, rgb_btm_1_color_2.r, rgb_btm_1_color_2.g, rgb_btm_1_color_2.b);
                } else {
                    rgb_matrix_set_color(0, rgb_btm_1_color.r, rgb_btm_1_color.g, rgb_btm_1_color.b);
                }
                rgb_matrix_set_color(1, rgb_btm_1_color.r, rgb_btm_1_color.g, rgb_btm_1_color.b);
            }
            break;
        case 2:
            if (vkr94.btm.dual_2) {
                rgb_matrix_set_color(0, rgb_btm_2_color_2.r, rgb_btm_2_color_2.g, rgb_btm_2_color_2.b);
            } else {
                rgb_matrix_set_color(0, rgb_btm_2_color.r, rgb_btm_2_color.g, rgb_btm_2_color.b);
            }
            rgb_matrix_set_color(1, rgb_btm_2_color.r, rgb_btm_2_color.g, rgb_btm_2_color.b);
            break;
        default:
            if (vkr94.btm.rest) { // Default bottom LED bar color. Overrides vibe lighting.
                rgb_matrix_set_color(1, rgb_btm_color_rest.r, rgb_btm_color_rest.g, rgb_btm_color_rest.b);
                rgb_matrix_set_color(0, rgb_btm_color_rest.r, rgb_btm_color_rest.g, rgb_btm_color_rest.b);
            }
            break;
    }

    return false;
}

void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_top_rest: {
            vkr94.top.rest = value_data[0];
            break;
        }
        case id_top_rest_brightness: {
            vkr94.top.v_rest = value_data[0];
        }
        case id_top_rest_color: {
            vkr94.top.h_rest = value_data[0];
            vkr94.top.s_rest = value_data[1];
            break;
        }
        case id_mid_rest: {
            vkr94.mid.rest = value_data[0];
            break;
        }
        case id_mid_rest_brightness: {
            vkr94.mid.v_rest = value_data[0];
        }
        case id_mid_rest_color: {
            vkr94.mid.h_rest = value_data[0];
            vkr94.mid.s_rest = value_data[1];
            break;
        }
        case id_btm_rest: {
            vkr94.btm.rest = value_data[0];
            break;
        }
        case id_btm_rest_brightness: {
            vkr94.btm.v_rest = value_data[0];
        }
        case id_btm_rest_color: {
            vkr94.btm.h_rest = value_data[0];
            vkr94.btm.s_rest = value_data[1];
            break;
        }
        case id_top_choice: {
            vkr94.top.choice = value_data[0];
        }
        case id_top_brightness: {
            vkr94.top.v = value_data[0];
            break;
        }
        case id_top_color: {
            vkr94.top.h = value_data[0];
            vkr94.top.s = value_data[1];
            break;
        }
        case id_top_dual: {
            vkr94.top.dual = value_data[0];
            break;
        }
        case id_top_color_2: {
            vkr94.top.h_dual = value_data[0];
            vkr94.top.s_dual = value_data[1];
            break;
        }
        case id_mid_choice: {
            vkr94.mid.choice = value_data[0];
            break;
        }
        case id_mid_brightness: {
            vkr94.mid.v = value_data[0];
            break;
        }
        case id_mid_color: {
            vkr94.mid.h = value_data[0];
            vkr94.mid.s = value_data[1];
            break;
        }
        case id_mid_dual: {
            vkr94.mid.dual = value_data[0];
            break;
        }
        case id_mid_color_2: {
            vkr94.mid.h_dual = value_data[0];
            vkr94.mid.s_dual = value_data[1];
            break;
        }
        case id_btm_1_brightness: {
            vkr94.btm.v_1 = value_data[0];
            break;
        }
        case id_btm_1_color: {
            vkr94.btm.h_1 = value_data[0];
            vkr94.btm.s_1 = value_data[1];
            break;
        }
        case id_btm_1_dual: {
            vkr94.btm.dual_1 = value_data[0];
            break;
        }
        case id_btm_1_color_2: {
            vkr94.btm.h_dual_1 = value_data[0];
            vkr94.btm.s_dual_1 = value_data[1];
            break;
        }
        case id_btm_2_brightness: {
            vkr94.btm.v_2 = value_data[0];
            break;
        }
        case id_btm_2_color: {
            vkr94.btm.h_2 = value_data[0];
            vkr94.btm.s_2 = value_data[1];
            break;
        }
        case id_btm_2_dual: {
            vkr94.btm.dual_2 = value_data[0];
            break;
        }
        case id_btm_2_color_2: {
            vkr94.btm.h_dual_2 = value_data[0];
            vkr94.btm.s_dual_2 = value_data[1];
            break;
        }
    }
}

void via_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_top_rest: {
            value_data[0] = vkr94.top.rest;
            break;
        }
        case id_top_rest_brightness: {
            value_data[0] = vkr94.top.v_rest;
        }
        case id_top_rest_color: {
            value_data[0] = vkr94.top.h_rest;
            value_data[1] = vkr94.top.s_rest;
            break;
        }
        case id_mid_rest: {
            value_data[0] = vkr94.mid.rest;
            break;
        }
        case id_mid_rest_brightness: {
            value_data[0] = vkr94.mid.v_rest;
        }
        case id_mid_rest_color: {
            value_data[0] = vkr94.mid.h_rest;
            value_data[1] = vkr94.mid.s_rest;
            break;
        }
        case id_btm_rest: {
            value_data[0] = vkr94.btm.rest;
            break;
        }
        case id_btm_rest_brightness: {
            value_data[0] = vkr94.btm.v_rest;
        }
        case id_btm_rest_color: {
            value_data[0] = vkr94.btm.h_rest;
            value_data[1] = vkr94.btm.s_rest;
            break;
        }
        case id_top_choice: {
            value_data[0] = vkr94.top.choice;
        }
        case id_top_brightness: {
            value_data[0] = vkr94.top.v;
            break;
        }
        case id_top_color: {
            value_data[0] = vkr94.top.h;
            value_data[1] = vkr94.top.s;
            break;
        }
        case id_top_dual: {
            value_data[0] = vkr94.top.dual;
            break;
        }
        case id_top_color_2: {
            value_data[0] = vkr94.top.h_dual;
            value_data[1] = vkr94.top.s_dual;
            break;
        }
        case id_mid_choice: {
            value_data[0] = vkr94.mid.choice;
            break;
        }
        case id_mid_brightness: {
            value_data[0] = vkr94.mid.v;
            break;
        }
        case id_mid_color: {
            value_data[0] = vkr94.mid.h;
            value_data[1] = vkr94.mid.s;
            break;
        }
        case id_mid_dual: {
            value_data[0] = vkr94.mid.dual;
            break;
        }
        case id_mid_color_2: {
            value_data[0] = vkr94.mid.h_dual;
            value_data[1] = vkr94.mid.s_dual;
            break;
        }
        case id_btm_1_brightness: {
            value_data[0] = vkr94.btm.v_1;
            break;
        }
        case id_btm_1_color: {
            value_data[0] = vkr94.btm.h_1;
            value_data[1] = vkr94.btm.s_1;
            break;
        }
        case id_btm_1_dual: {
            value_data[0] = vkr94.btm.dual_1;
            break;
        }
        case id_btm_1_color_2: {
            value_data[0] = vkr94.btm.h_dual_1;
            value_data[1] = vkr94.btm.s_dual_1;
            break;
        }
        case id_btm_2_brightness: {
            value_data[0] = vkr94.btm.v_2;
            break;
        }
        case id_btm_2_color: {
            value_data[0] = vkr94.btm.h_2;
            value_data[1] = vkr94.btm.s_2;
            break;
        }
        case id_btm_2_dual: {
            value_data[0] = vkr94.btm.dual_2;
            break;
        }
        case id_btm_2_color_2: {
            value_data[0] = vkr94.btm.h_dual_2;
            value_data[1] = vkr94.btm.s_dual_2;
            break;
        }
    }
}

void via_config_save(void) {
    eeconfig_update_kb_datablock(&vkr94);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                via_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}

#endif
