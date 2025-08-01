// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "analog.h"
#include "gpio.h"

#define DEADZONE 100

// Posiciones en la matriz física (fila 4)
#define ROW 4
#define COL_UP    0
#define COL_DOWN  1
#define COL_LEFT  2
#define COL_RIGHT 3
#define COL_BTN   4

enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    NEW_SAFE_RANGE  // esto puedes usar si quieres seguir extendiendo después
};




// Estados de las teclas
static bool left_pressed = false;
static bool right_pressed = false;
static bool up_pressed = false;
static bool down_pressed = false;
static bool button_pressed = false;

void matrix_init_user(void) {
    setPinInputHigh(B2); // pull-up para botón del joystick
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                // Envía el texto "Hola Mundo"
                SEND_STRING("Hola Mundo");
            }
            return false;

        case MACRO_2:
            if (record->event.pressed) {
                // Envía Ctrl+S
                tap_code16(C(S(KC_S)));
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    int16_t x = analogReadPin(F7) - 512;
    int16_t y = analogReadPin(F6) - 512;

    uint8_t layer = get_highest_layer(layer_state);

    // --- IZQUIERDA ---
    if (x < -DEADZONE && !left_pressed) {
        register_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_LEFT}));
        left_pressed = true;
    } else if (x >= -DEADZONE && left_pressed) {
        unregister_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_LEFT}));
        left_pressed = false;
    }

    // --- DERECHA ---
    if (x > DEADZONE && !right_pressed) {
        register_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_RIGHT}));
        right_pressed = true;
    } else if (x <= DEADZONE && right_pressed) {
        unregister_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_RIGHT}));
        right_pressed = false;
    }

    // --- ARRIBA ---
    if (y < -DEADZONE && !up_pressed) {
        register_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_UP}));
        up_pressed = true;
    } else if (y >= -DEADZONE && up_pressed) {
        unregister_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_UP}));
        up_pressed = false;
    }

    // --- ABAJO ---
    if (y > DEADZONE && !down_pressed) {
        register_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_DOWN}));
        down_pressed = true;
    } else if (y <= DEADZONE && down_pressed) {
        unregister_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_DOWN}));
        down_pressed = false;
    }

    // --- BOTÓN CENTRAL ---
    bool btn = !gpio_read_pin(B2);
    if (btn && !button_pressed) {
        register_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_BTN}));
        button_pressed = true;
    } else if (!btn && button_pressed) {
        unregister_code16(keymap_key_to_keycode(layer, (keypos_t){ROW, COL_BTN}));
        button_pressed = false;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x5(
        KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  // joystick
    )
};

