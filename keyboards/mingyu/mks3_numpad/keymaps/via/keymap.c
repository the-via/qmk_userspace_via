/* MKS3 9-Key Numpad — VIA keymap (the-via/qmk_userspace_via)
 * Path: keyboards/mingyu/mks3_numpad/keymaps/via/
 *
 * Default dynamic keymap written to EEPROM on the first VIA launch.
 * Later changes made in VIA are kept in EEPROM and survive reflashing.
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE = 0,
    _RGB,
    _VIA2,
    _VIA3,
};

/* Tap for Esc, hold for the lighting layer */
#define RGB_LAYER_KEY LT(_RGB, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        RGB_LAYER_KEY, KC_F1, KC_F2, KC_F3, KC_TAB,
        LCTL(KC_C), LCTL(KC_V), KC_ENT, KC_UP),

    [_RGB] = LAYOUT(
        _______, RM_TOGG, RM_NEXT, RM_PREV, RM_SPDU,
        RM_SPDD, RM_VALU, RM_VALD, RM_HUEU),

    [_VIA2] = LAYOUT(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______),

    [_VIA3] = LAYOUT(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______),
};
