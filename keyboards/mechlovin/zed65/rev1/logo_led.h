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

#pragma once

#include "quantum.h"
#include "rgblight.h"
#include "via.h"
#include "eeconfig.h"
#include "rev1.h"

enum via_rgblight_value {
    id_rgblight_logo_toggle = 1,
    id_rgblight_ug_toggle   = 2,
};

void rgblight_config_set_value(uint8_t *data);
void rgblight_config_get_value(uint8_t *data);