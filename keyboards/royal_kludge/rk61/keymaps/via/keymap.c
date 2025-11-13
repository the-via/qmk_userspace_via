// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    WIN_BASE,
    MAC_BASE,
    WIN_FN,
    MAC_FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_UP,                      KC_RSFT,
        KC_LCTL, KC_LWIN, KC_LALT,                KC_SPC,                 KC_LEFT, KC_DOWN, KC_RIGHT,          MO(WIN_FN)
    ),
    [WIN_FN]   = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,        KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______,      _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, RM_VALD, RM_VALU, RM_NEXT,
        _______, _______, DF(MAC_BASE), _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, RM_SPDD, RM_SPDU,          _______,
        _______, _______, _______,      _______, _______, NK_TOGG, KC_DEL,  KC_END,  KC_PGDN, RM_HUEU, KC_SLSH,                   _______,
        _______, GU_TOGG, _______,                           KC_NO,                           KC_RALT, KC_APP,  KC_RCTL,          _______
    ),
    [MAC_BASE] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_UP,                      KC_RSFT,
        KC_LCTL, KC_LOPT, KC_LCMD,                KC_SPC,                 KC_LEFT, KC_DOWN, KC_RIGHT,          MO(MAC_FN)
    ),
    [MAC_FN]   = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,        KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______,      _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, RM_VALD, RM_VALU, RM_NEXT,
        _______, DF(WIN_BASE), _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______, RM_SPDD, RM_SPDU,          _______,
        _______, _______,      _______, _______, _______, NK_TOGG, KC_DEL,  KC_END,  KC_PGDN, RM_HUEU, KC_SLSH,                   _______,
        _______, _______,      GU_TOGG,                        KC_NO,                         KC_RALT, KC_APP,  KC_RCTL,          _______
    ),
};

#ifdef CAPS_LOCK_LED_INDEX
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }

    return false;
}
#endif
