// Copyright 2023 Silvino Rodrigues (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "report.h"
#include "binepad_common.h"

#include "color.h"

RGB adjust_to_brightness(uint8_t r, uint8_t g, uint8_t b, uint8_t min, uint8_t max) {
    RGB ret = {r: 0, g: 0, b: 0};

    uint8_t brightness = rgblight_get_val();
    if (brightness > max) brightness = max;
    if (brightness < min) brightness = min;

    ret.r = (uint16_t)(r * (brightness / 255));
    ret.g = (uint16_t)(g * (brightness / 255));
    ret.b = (uint16_t)(b * (brightness / 255));

    return ret;
}
