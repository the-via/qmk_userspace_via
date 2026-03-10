/* Copyright 2025 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "quantum.h"
#include "lily.h"

eeprom_lily_config_t eeprom_lily_config;

void eeconfig_init_kb(void) {
    // Default values
    eeprom_lily_config.ind1.h       = 0;
    eeprom_lily_config.ind1.s       = 255;
    eeprom_lily_config.ind1.v       = 150;
    eeprom_lily_config.ind1.func    = 0x04;
    eeprom_lily_config.ind1.index   = 0;
    eeprom_lily_config.ind1.enabled = true;

    eeprom_lily_config.ind2.h       = 86;
    eeprom_lily_config.ind2.s       = 255;
    eeprom_lily_config.ind2.v       = 150;
    eeprom_lily_config.ind2.func    = 0x04;
    eeprom_lily_config.ind2.index   = 1;
    eeprom_lily_config.ind2.enabled = true;

    eeprom_lily_config.ind3.h       = 166;
    eeprom_lily_config.ind3.s       = 254;
    eeprom_lily_config.ind3.v       = 150;
    eeprom_lily_config.ind3.func    = 0x04;
    eeprom_lily_config.ind3.index   = 2;
    eeprom_lily_config.ind3.enabled = true;

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&eeprom_lily_config);

    eeconfig_init_user();
}

// On Keyboard startup
void keyboard_post_init_kb(void) {
    // Read custom menu variables from memory
    eeconfig_read_kb_datablock(&eeprom_lily_config);

    // Set the RGB LEDs range that will be used for the effects
    rgblight_set_effect_range(3, 1);

    // Call the indicator callback to set the indicator color
    indicators_callback();

    keyboard_post_init_user();
}

// This function gets called when caps, num, scroll change
bool led_update_kb(led_t led_state) {
    indicators_callback();
    return true;
}

// This function is called when layers change
__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    indicators_callback();
    return state;
}

bool func_switch(uint8_t func) {
    switch (func) {
        case 0x00: {
            return false;
            break;
        }
        case 0x01: // If indicator is set as caps lock
        {
            if (host_keyboard_led_state().caps_lock) return true;
            break;
        }
        case 0x02: // If indicator is set as num lock
        {
            if (host_keyboard_led_state().num_lock) return true;
            break;
        }
        case 0x03: // If indicator is set as scroll lock
        {
            if (host_keyboard_led_state().scroll_lock) return true;
            break;
        }
        case 0x04: // If indicator is set as layer 0
        case 0x05: // layer 1
        case 0x06: // layer 2
        case 0x07: // layer 3
        case 0x08: // layer 4
        case 0x09: // layer 5
        {
            if (IS_LAYER_ON((int)(func)-4)) return true;
            break;
        }
        default: {
            return false;
        }
    }
    return false;
}

bool set_indicator(indicator_config indicator) {
    if (!indicator.enabled) return false;
    return func_switch(indicator.func & 0x0F) | func_switch((indicator.func & 0xF0) >> 4);
}

bool indicators_callback(void) {
    // This function handles the THT LED since the QMK one get's overwritten by this function
    if (host_keyboard_led_state().caps_lock) {
        writePinLow(B0);
    } else {
        writePinHigh(B0);
    }
    // Basic functioning: for each indicator, set_indicator is used to decide if the current indicator should be lit or off.
    indicator_config *current_indicator_p;
    int               index;
    RGB               color;
    for (index = 0; index < 3; index++) {
        current_indicator_p = get_indicator_p(index);
        if (set_indicator(*(current_indicator_p))) {
            /*
               Issue: while the VIA custom GUI returns HSV values, the QMK direct operation funcs are RGB.
               So this line converts the current indicator to RGB. This was not done at the indicator_config_set_value VIA callback function
               because at the indicator_config_get_value the RGB to HSV would be required and this throttles the keyboard
               when the user is adjusting the color on the GUI.
            */
            color = hsv_to_rgb((HSV){current_indicator_p->h, current_indicator_p->s, current_indicator_p->v});
            rgblight_setrgb_at(color.r, color.g, color.b, current_indicator_p->index);
        } else
            rgblight_setrgb_at(RGB_OFF, current_indicator_p->index);
    }
    return true;
}

uint8_t *pIndicators = (uint8_t *)&eeprom_lily_config;

indicator_config *get_indicator_p(int index) {
    return (indicator_config *)(pIndicators + 6 * index);
}
