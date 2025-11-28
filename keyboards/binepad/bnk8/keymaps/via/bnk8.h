// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

#ifdef CAFFEINE_ENABLE

enum bnk8_keyboard { KC_CAFFEINE_TOGGLE = QK_KB_0 };

#    define KC_COFFEE KC_CAFFEINE_TOGGLE

#endif // CAFFEINE_ENABLE

#ifdef VIA_ENABLE // Only works if VIA is enabled

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
} HS;

typedef union {
    uint8_t raw[16];
    struct {
        HS color[8];
    };
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
