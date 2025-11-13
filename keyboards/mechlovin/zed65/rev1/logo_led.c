/*
Copyright 2025 Mechlovin'

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

#include "logo_led.h"
#include "rgblight.h"

enum via_rgblight_value {
    id_rgblight_logo_toggle = 1,
    id_rgblight_ug_toggle   = 2,
};

// Process commands from VIA
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    if (data[1] == id_custom_channel) {
        switch (data[0]) {
            case id_custom_set_value:
                rgblight_config_set_value(&data[2]);
                break;
            case id_custom_get_value:
                rgblight_config_get_value(&data[2]);
                break;
            case id_custom_save:
                rgblight_config_save();
                break;
            default:
                data[0] = id_unhandled;
        }
        return;
    }
    data[0] = id_unhandled;
}

// Set values
void rgblight_config_set_value(uint8_t *data) {
    switch (data[0]) {
        case id_rgblight_logo_toggle:
            g_custom_rgblight_config.logo_enabled = data[1];
            break;
        case id_rgblight_ug_toggle:
            g_custom_rgblight_config.ug_enabled = data[1];
            break;
    }
    rgblight_config_save();
    update_rgblight();
}

// Get values
void rgblight_config_get_value(uint8_t *data) {
    data[1] = (data[0] == id_rgblight_logo_toggle) ? g_custom_rgblight_config.logo_enabled : g_custom_rgblight_config.ug_enabled;
}