// Copyright 2018-2024 QMK (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "eeprom.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC,     KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSLS,   KC_BSPC,   KC_INS,
        KC_TAB,     KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,             KC_BSLS,   KC_DEL,
        KC_CAPS,    KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,
        KC_LSFT,              KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,             KC_UP, 
        KC_LCTL,    KC_LWIN,  KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),              KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
    [1] = LAYOUT_all(
        KC_TILD,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   KC_TRNS,   KC_TRNS,   KC_PGUP,
        KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SCRL,  KC_PAUS,             KC_TRNS,   KC_PGDN,
        KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,         
        KC_TRNS,              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_VOLU, KC_VOLD, KC_TRNS,  KC_TRNS,             KC_TRNS, 
        KC_TRNS,    KC_TRNS,  KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,            KC_TRNS,   KC_TRNS,   KC_TRNS
    )
};

typedef union {
    uint32_t raw;
    struct {
        bool indicator_toggle:1;           // 1 byte
        HSV indicator_hsv;                 // 3 bytes
    } __attribute__((packed));             // total 4 bytes
} brick65s_config_t;

brick65s_config_t g_brick65s_config;

#ifdef VIA_ENABLE
// via value id declaration
enum tomak_custom_value_id {
    id_custom_indicator_toggle = 0,
    id_custom_indicator_brightness,
    id_custom_indicator_color
};

// function declaration
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void indicator_config_save ( void );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);

static void read_brick65s_config_from_eeprom(brick65s_config_t* config) {
    config->raw = eeconfig_read_kb() & 0xffffffff;
}

static void write_brick65s_config_to_eeprom(brick65s_config_t* config) {
    eeconfig_update_kb(config->raw);
}

void eeconfig_init_kb(void) {
    g_brick65s_config.raw = 0;
    g_brick65s_config.indicator_toggle = true;
    g_brick65s_config.indicator_hsv.h = 255;
    g_brick65s_config.indicator_hsv.s = 255;
    g_brick65s_config.indicator_hsv.v = 255;
    write_brick65s_config_to_eeprom(&g_brick65s_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_brick65s_config_from_eeprom(&g_brick65s_config);
    matrix_init_user();
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    if (g_brick65s_config.indicator_toggle) {
        RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_brick65s_config.indicator_hsv.h,
                                          .s = g_brick65s_config.indicator_hsv.s,
                                          .v = g_brick65s_config.indicator_hsv.v } );
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(0, rgb_caps.r, rgb_caps.g, rgb_caps.b);
        } else {
            rgb_matrix_set_color(0, 0, 0, 0);
        }
        
        if (host_keyboard_led_state().scroll_lock) {
            rgb_matrix_set_color(1, rgb_caps.r, rgb_caps.g, rgb_caps.b);
        } else {
            rgb_matrix_set_color(1, 0, 0, 0);
        }
    } else {
        rgb_matrix_set_color(0, 0, 0, 0);
        rgb_matrix_set_color(1, 0, 0, 0);
    }

    return false;
}

void via_init_kb(void)
{
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        read_brick65s_config_from_eeprom(&g_brick65s_config);
    } else    {
        write_brick65s_config_to_eeprom(&g_brick65s_config);
        // DO NOT set EEPROM valid here, let caller do this
    }
}

// Some helpers for setting/getting HSV
void _set_color( HSV *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HSV *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

void indicator_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_indicator_toggle:
        {
            *value_data = g_brick65s_config.indicator_toggle;
            break;
        }
        case id_custom_indicator_brightness:
        {
            *value_data = g_brick65s_config.indicator_hsv.v;
            break;
        }
        case id_custom_indicator_color:
        {
            _get_color( &(g_brick65s_config.indicator_hsv), value_data );
            break;
        }
    }
}

void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_indicator_toggle:
        {
            g_brick65s_config.indicator_toggle = (bool) *value_data;
            break;
        }
        case id_custom_indicator_brightness:
        {
            g_brick65s_config.indicator_hsv.v = *value_data;
            break;
        }
        case id_custom_indicator_color:
        {
            _set_color( &(g_brick65s_config.indicator_hsv), value_data );
            break;
        }
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length)
{
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
                write_brick65s_config_to_eeprom(&g_brick65s_config);
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

}
#endif