// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "eeprom.h"
#include "transactions.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_all(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_F13,   KC_PSCR,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_INS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,   MO(1),                                  KC_SPC,             KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [1] = LAYOUT_all(
        QK_BOOT,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  QK_BOOT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  RM_TOGG,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  RM_NEXT,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,                                KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
    )
};

typedef union {
    uint32_t raw;
    struct {
        bool indicator_toggle:1;           // | byte
        bool indicator_override:1;         // | byte
        bool per_key_toggle:1;             // | byte
        HSV indicator_hsv;                 // 3 bytes
    } __attribute__((packed));             // total 4 bytes
} tomak_config_t;

tomak_config_t g_tomak_config;

static void read_tomak_config_from_eeprom(tomak_config_t* config) {
    config->raw = eeconfig_read_kb() & 0xffffffff;
}

static void write_tomak_config_to_eeprom(tomak_config_t* config) {
    eeconfig_update_kb(config->raw);
}

void eeconfig_init_kb(void) {
    g_tomak_config.raw = 0;
    g_tomak_config.indicator_toggle = true;
    g_tomak_config.indicator_override = false;
    g_tomak_config.indicator_hsv.h = 255;
    g_tomak_config.indicator_hsv.s = 255;
    g_tomak_config.indicator_hsv.v = 255;
    g_tomak_config.per_key_toggle = true;
    write_tomak_config_to_eeprom(&g_tomak_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_tomak_config_from_eeprom(&g_tomak_config);
    matrix_init_user();
}

bool rgb_matrix_indicators_user(void) {
    if (g_tomak_config.indicator_toggle) {
        RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_tomak_config.indicator_hsv.h,
                                          .s = g_tomak_config.indicator_hsv.s,
                                          .v = g_tomak_config.indicator_hsv.v } );
        if (host_keyboard_led_state().caps_lock) {
            for (uint8_t i = 93; i <= 101; ++i) {
                rgb_matrix_set_color(i, rgb_caps.r, rgb_caps.g, rgb_caps.b);
            }
        } else if (g_tomak_config.indicator_override) {
            for (uint8_t i = 93; i <= 101; ++i) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
    
    if (g_tomak_config.per_key_toggle == false) {
        for (uint8_t i = 0; i <= 92; ++i) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
    
    return false;
}

#ifdef TOMAK_CONFIG_SYNC
void tomak_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(g_tomak_config)) {
        memcpy(&g_tomak_config, initiator2target_buffer, sizeof(g_tomak_config));
    }
}

void keyboard_post_init_kb(void) {
    
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, tomak_config_sync_handler);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave.
        static tomak_config_t last_tomak_config = {0};
        static uint32_t           last_sync     = 0;
        bool                      needs_sync    = false;

        // Check if the state values are different.
        if (memcmp(&g_tomak_config, &last_tomak_config, sizeof(g_tomak_config))) {
            needs_sync = true;
            memcpy(&last_tomak_config, &g_tomak_config, sizeof(g_tomak_config));
        }
        // Send to slave every 500ms regardless of state change.
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested.
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(g_tomak_config), &g_tomak_config)) {
                last_sync = timer_read32();
            }
        }
    }
    // No need to invoke the user-specific callback, as it's been called
    // already.
}
#endif

#ifdef VIA_ENABLE
// via value id declaration
enum tomak_custom_value_id {
    id_custom_indicator_toggle = 0,
    id_custom_indicator_override,
    id_custom_indicator_brightness,
    id_custom_indicator_color,
    id_custom_per_key_toggle
};

// function declaration
void via_tomak_config_set_value( uint8_t *data );
void via_tomak_config_get_value( uint8_t *data );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);

void via_init_kb(void)
{
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        read_tomak_config_from_eeprom(&g_tomak_config);
    } else    {
        write_tomak_config_to_eeprom(&g_tomak_config);
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

void via_tomak_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_indicator_toggle:
        {
            *value_data = g_tomak_config.indicator_toggle;
            break;
        }
        case id_custom_indicator_override:
        {
            *value_data = g_tomak_config.indicator_override;
            break;
        }
        case id_custom_indicator_brightness:
        {
            *value_data = g_tomak_config.indicator_hsv.v;
            break;
        }
        case id_custom_indicator_color:
        {
            _get_color( &(g_tomak_config.indicator_hsv), value_data );
            break;
        }
        case id_custom_per_key_toggle:
        {
            *value_data = g_tomak_config.per_key_toggle;
            break;
        }
    }
}

void via_tomak_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_indicator_toggle:
        {
            g_tomak_config.indicator_toggle = (bool) *value_data;
            break;
        }
        case id_custom_indicator_override:
        {
            g_tomak_config.indicator_override = (bool) *value_data;
            break;
        }
        case id_custom_indicator_brightness:
        {
            g_tomak_config.indicator_hsv.v = *value_data;
            break;
        }
        case id_custom_indicator_color:
        {
            _set_color( &(g_tomak_config.indicator_hsv), value_data );
            break;
        }
        case id_custom_per_key_toggle:
        {
            g_tomak_config.per_key_toggle = (bool) *value_data;
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
                via_tomak_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                via_tomak_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                write_tomak_config_to_eeprom(&g_tomak_config);
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