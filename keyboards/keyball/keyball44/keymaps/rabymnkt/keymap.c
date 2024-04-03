/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"

static bool is_lower_pressed = false;
static bool is_upper_pressed = false;
static bool is_ime_locked = false;

enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
    _NUMPAD
};

enum planck_keycodes {
    ESC_ENG = SAFE_RANGE,
    LOWER,
    RAISE,
    IME_LOCK,
    IME_UNLOCK
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
    [_QWERTY] = LAYOUT_universal(
        KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
        KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     , KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
        KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                 TT(_NUMPAD),TT(_MOUSE), KC_LALT  , LOWER    , KC_BSPC  , KC_SPC   , RAISE    , XXXXXXX  , XXXXXXX  , SCRL_MO
    ),

    [_LOWER] = LAYOUT_universal(
        KC_TAB   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     , KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_UNDS  ,
        _______  , XXXXXXX  , RSG(KC_LEFT),KC_LNG2, ESC_ENG  , XXXXXXX  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , XXXXXXX  , KC_RCTL  ,
        _______  , XXXXXXX  , KC_X     , KC_C     , KC_V     , KC_B     , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , KC_RGUI  , KC_RALT  ,
                   _______  , _______  , _______  , _______  , _______  , KC_ENT   , RAISE    , _______  , _______  , _______
    ),

    [_RAISE] = LAYOUT_universal(
        KC_TILD  , KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  , KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_CIRC  , KC_DLR   , KC_UNDS  ,
        _______  , KC_MINS  , KC_EQL   , KC_PLUS  , KC_LCBR  , KC_LPRN  , KC_RPRN  , KC_RCBR  , KC_BSLS  , KC_SLSH  , XXXXXXX  , KC_RCTL  ,
        _______  , XXXXXXX  , XXXXXXX  , KC_GRV   , KC_LT    , KC_LBRC  , KC_RBRC  , KC_GT    , KC_PIPE  , XXXXXXX  , KC_RGUI  , KC_RALT  ,
                   _______  , _______  , _______  , LOWER    , KC_DEL   , _______  , _______  , _______  , _______  , _______
    ),

    [_ADJUST] = LAYOUT_universal(
        KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   , KC_F12   ,
        _______  , KC_PSCR  , XXXXXXX  , KC_VOLD  , KC_MUTE  , KC_VOLU  , KC_WBAK  , KC_WSCH  , KC_WHOM  , KC_WFWD  , KC_WREF  , _______  ,
        _______  , XXXXXXX  , XXXXXXX  , IME_LOCK , LAG_SWP  , KC_MPLY  , KC_MPRV  , LAG_NRM  , IME_UNLOCK,KC_MNXT  , _______  , _______  ,
                   _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______
    ),

    [_MOUSE] = LAYOUT_universal(
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , AML_TO   , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , SCRL_MO  ,
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_BTN1  , KC_BTN3  , KC_BTN2  , XXXXXXX  , XXXXXXX  ,
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
                   _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______
    ),

    [_NUMPAD] = LAYOUT_universal(
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_NUM   , KC_P7    , KC_P8    , KC_P9    , KC_PDOT  , KC_PEQL,
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_P4    , KC_P5    , KC_P6    , KC_PAST  , KC_PSLS  ,
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_P1    , KC_P2    , KC_P3    , KC_PPLS  , KC_PMNS  ,
                 TT(_NUMPAD), XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_BSPC  , KC_ENT   , KC_P0    , XXXXXXX  , XXXXXXX  , XXXXXXX
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ESC_ENG:
        if (record->event.pressed) {
            // キーコード ESC_ENG が押された時
            tap_code(KC_ESC);
        }else{
            // キーコード ESC_ENG が離された時
            tap_code(KC_LNG2);
        }

        return false;
        break;
    case LOWER:
        if (record->event.pressed) {
            layer_on(_LOWER);
            is_lower_pressed = true;
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            if (is_lower_pressed){
                tap_code(KC_LNG2);
            }
            is_lower_pressed = false;
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            layer_on(_RAISE);
            is_upper_pressed = true;
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            if(is_upper_pressed && !is_ime_locked){
                tap_code(KC_LNG1);
            }
            is_upper_pressed = false;
        }
        return false;
        break;
    case IME_LOCK:
        if (record->event.pressed) {
            is_ime_locked = true;
        }
        return false;
        break;
    case IME_UNLOCK:
        if (record->event.pressed) {
            is_ime_locked = false;
        }
        return false;
        break;
    default:
        if (record->event.pressed) {
            is_lower_pressed = false;
            is_upper_pressed = false;
        }
    }
    return true;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
