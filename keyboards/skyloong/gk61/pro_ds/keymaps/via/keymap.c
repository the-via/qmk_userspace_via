// Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
_Bool L_WIN = 0;
_Bool L_MAC = 0;

#define WIN_MOD_INDEX 16
#define MAC_MOD_INDEX 17

enum layer_names {
    _WIN,
    _MAC,
    _WIN_INDEX,
    _MAC_INDEX,
};

enum tap_hold_keys {
    _DN_MU   //Tap--KC_DOWN  and  Hold--KC_APP
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_UP):
            return TAPPING_TERM - 80; //right shift hold time less than default tapping term 80ms
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   |Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   |Sft|   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│GUI│Alt│   │Spc│Spc│Mut│   |Spc|Alt│App│Ctl│   │Mox|
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_WIN] = LAYOUT_all(
         KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,        KC_8,      KC_9,                    KC_0,      KC_MINS,        KC_EQL,           KC_BSPC,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,        KC_I,      KC_O,                     KC_P,     KC_LBRC,       KC_RBRC,           KC_BSLS,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,        KC_K,      KC_L,                  KC_SCLN,     KC_QUOT,                           KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,     KC_COMM,    KC_DOT,                  KC_SLSH,              RSFT_T(KC_UP),
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,                             KC_SPC,   KC_RALT,  LT(_WIN_INDEX, KC_LEFT),    TD(_DN_MU),                  RCTL_T(KC_RIGHT)
    ),

     [_MAC] = LAYOUT_all(
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,                    _______,     _______,      _______,           _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,                    _______,     _______,      _______,           _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,                    _______,     _______,                         _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,     _______,   _______,                    _______,              RSFT_T(KC_UP),
        _______,  KC_LALT,  KC_LGUI,            _______,  _______,                            _______,   KC_RGUI,    LT(_MAC_INDEX, KC_LEFT),   RALT_T(KC_DOWN),           RCTL_T(KC_RIGHT)
    ),

    [_WIN_INDEX] =  LAYOUT_all(
        KC_GRV ,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        _______,  _______,    DF(0),    DF(1),  _______,  _______,     _______,  _______,  _______,  _______,   RGB_M_P,  RM_PREV,  RM_NEXT,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,   RM_SPDD,  RM_SPDU,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  RM_VALD,  RM_VALU,     KC_UP,            _______,
        _______,  _______,  _______,            _______,  _______,                         _______,  KC_LEFT,   _______,  KC_DOWN,            KC_RIGHT
    ),

    [_MAC_INDEX] = LAYOUT_all(
        KC_GRV ,   KC_F14,   KC_F15,  C(KC_UP),  G(KC_D),  G(KC_SPC),   LAG(KC_EJCT),  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_VOLU,   KC_DEL,
        _______,  _______,    DF(0),     DF(1),  _______,    _______,     _______,     _______,  _______,  _______,  RGB_M_P,   RM_PREV,  RM_NEXT,  RM_TOGG,
        _______,  _______,  _______,   _______,  _______,    _______,     _______,     _______,  _______,  _______,  RM_SPDD,   RM_SPDU,            _______,
        _______,  _______,  _______,   _______,  _______,    _______,     _______,     _______,  RM_VALD,  RM_VALU,    KC_UP,             _______,
        _______,  _______,  _______,             _______,    _______,                            _______,  KC_LEFT,  _______,   KC_DOWN,           KC_RIGHT
    )
};


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [_DN_MU] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOWN, KC_APP),
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

   switch (get_highest_layer(layer_state)) {
      case _WIN_INDEX:{
        RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 255, 255, 255);
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
         }
      } break;
      case _MAC_INDEX:{
        RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 255, 255, 255);
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
         }
      } break;

      case _WIN:{
       if (L_WIN) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 255, 255, 255);
            if (!rgb_matrix_get_flags()) {
               RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
            }
            }else{
                if (!rgb_matrix_get_flags()) {
                   RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
                 }
              }
         } break;

     case _MAC:{
       if (L_MAC) {
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 255, 255, 255);
            if (!rgb_matrix_get_flags()) {
               RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
            }
            }else{
                if (!rgb_matrix_get_flags()) {
                   RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
                 }
              }
         } break;

      default:{
         if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
         }
      }
    }
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
#    ifdef RGB_MATRIX_ENABLE
        case RM_TOGG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
         return false;
        case RM_VALU:
          rgb_matrix_set_flags(LED_FLAG_ALL);
          return true;
#    endif
     case DF(0):
      if (record->event.pressed) {
       L_WIN = 1;
       L_MAC = 0;
       layer_move(0);
       set_single_persistent_default_layer(0); // Save default layer 0 to eeprom
      } else {
       L_WIN = 0;
      }
      return false; // cancel all further processing of this key


     case DF(1):
      if (record->event.pressed) {
       L_MAC = 1;
       L_WIN = 0;
       layer_move(1);
       set_single_persistent_default_layer(1);  //Save default layer 1 to eeprom
      } else {
       L_MAC = 0;
      }
      return false; // cancel  all further processing of this key

     case TD(_DN_MU):
         action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
           if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }

     default:
       L_MAC = 0;
       L_WIN = 0;
      return true;
    }
}
