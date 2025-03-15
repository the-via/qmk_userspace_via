// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LAYER_STATE_8BIT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define EE_HANDS

#ifndef OLED_FONT_H
#    define OLED_FONT_H "keyboards/uzu42/glcdfont.c"
#endif
