// Copyright 2025 Alex Havermale (@haversnail), Moritz Plattner (@ebastler)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "transactions.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_all(
        RM_TOGG, KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_F13,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  KC_HOME,
        KC_F14,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_F15,  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_F16,  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_F17,  KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,  MO(1),   KC_SPC,                    KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_all(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_MPLY,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
};
#endif

////////////////////////////////
// BEGIN VIA INDICATOR CONFIG //
////////////////////////////////

/**
 * A struct containing config data for a single LED indicator.
 */
typedef struct _indicator_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    bool    enabled;
} indicator_t;

/**
 * A struct containing config data for all LED indicators.
 */
typedef struct _indicator_config_t {
    indicator_t caps;
} indicator_config_t;

indicator_config_t indicator_config;

void indicator_config_write_to_eeprom(void) {
    eeconfig_update_user_datablock(&indicator_config, 0, EECONFIG_USER_DATA_SIZE);
    dprintf("Indicator config written to EEPROM\n");
}

void indicator_config_read_from_eeprom(void) {
    eeconfig_read_user_datablock(&indicator_config, 0, EECONFIG_USER_DATA_SIZE);
    dprintf("Indicator config read from EEPROM\n");
}

void indicator_config_slave_handler(uint8_t m2s_size, const void* m2s_buffer, uint8_t s2m_size, void* s2m_buffer) {
    if (m2s_size == sizeof(indicator_config_t)) {
        memcpy(&indicator_config, m2s_buffer, sizeof(indicator_config_t));
        indicator_config_write_to_eeprom();
    } else {
        dprintf("Unexpected response in slave handler\n"); // TODO: add split debug logging
    }
}

void eeconfig_init_user(void) {
    indicator_config.caps.h       = 0;
    indicator_config.caps.s       = 0;
    indicator_config.caps.v       = INDICATOR_MAX_BRIGHTNESS;
    indicator_config.caps.enabled = true;
    indicator_config_write_to_eeprom();
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(RPC_ID_INDICATOR_CONFIG, indicator_config_slave_handler);
    indicator_config_read_from_eeprom();
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock && indicator_config.caps.enabled) {
        HSV hsv = {indicator_config.caps.h, indicator_config.caps.s, indicator_config.caps.v};
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, rgb.r, rgb.g, rgb.b);
    } else {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
    }
    return false;
}
#endif

enum indicator_value {
    id_caps_indicator_enabled    = 1,
    id_caps_indicator_brightness = 2,
    id_caps_indicator_color      = 3
};

void indicator_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled:
        {
            indicator_config.caps.enabled = value_data[0];
            break;
        }
        case id_caps_indicator_brightness:
        {
            indicator_config.caps.v = value_data[0];
            break;
        }
        case id_caps_indicator_color:
        {
            indicator_config.caps.h = value_data[0];
            indicator_config.caps.s = value_data[1];
            break;
        }
    }
}

void indicator_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_indicator_enabled:
        {
            value_data[0] = indicator_config.caps.enabled;
            break;
        }
        case id_caps_indicator_brightness:
        {
            value_data[0] = indicator_config.caps.v;
            break;
        }
        case id_caps_indicator_color:
        {
            value_data[0] = indicator_config.caps.h;
            value_data[1] = indicator_config.caps.s;
            break;
        }
    }
}

void indicator_config_save(void) {
    indicator_config_write_to_eeprom();
    // Send data to slave so that it can be written to its EEPROM as well:
    transaction_rpc_send(RPC_ID_INDICATOR_CONFIG, sizeof(indicator_config_t), &indicator_config);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                indicator_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                indicator_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                indicator_config_save();
                break;
            }
            default:
            {
                // Unhandled message:
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state:
    *command_id = id_unhandled;
}
