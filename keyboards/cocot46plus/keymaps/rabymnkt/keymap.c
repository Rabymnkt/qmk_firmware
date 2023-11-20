/*
Copyright 2022 aki27

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
#include <stdio.h>  
#include "quantum.h"

static bool is_lower_pressed = false;
static bool is_upper_pressed = false;
static bool is_ime_locked = false;

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD
};

#define LW_MHEN LT(1,KC_MHEN)  // lower
#define RS_HENK LT(2,KC_HENK)  // raise
#define DEL_ALT ALT_T(KC_DEL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        KC_LGUI, KC_LALT,   LOWER, KC_BSPC, KC_MS_BTN1,             KC_MS_BTN2,  KC_SPC,   RAISE, KC_RGUI, KC_RALT,
                                                                 KC_UP, KC_MS_BTN3,    KC_DOWN, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),

  [_LOWER] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
       KC_TAB, KC_1,       KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_UNDS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LCTL, XXXXXXX, RSG(KC_LEFT), KC_LNG2, ESC_ENG, TT(_NUMPAD),                              KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, KC_RCTL,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LSFT, XXXXXXX, KC_CAPS, KC_BTN2, KC_BTN1, KC_BTN3,                                       KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_RGUI, KC_RALT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        _______, _______, _______, _______,   KC_MS_BTN4,             KC_MS_BTN5,  KC_ENT,   RAISE, _______, _______,
                                                                 KC_BRIU, KC_MS_BTN3,    KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [_RAISE] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_CIRC, KC_DLR,  KC_UNDS,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LCTL, KC_MINS, KC_EQL,  KC_PLUS, KC_LCBR, KC_LPRN,                                       KC_RPRN, KC_RCBR, KC_BSLS, KC_SLSH, XXXXXXX, KC_RCTL,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LSFT, XXXXXXX, XXXXXXX,  KC_GRV,   KC_LT, KC_LBRC,                                       KC_RBRC,   KC_GT, KC_PIPE, XXXXXXX, KC_RGUI, KC_RALT,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        _______, _______,   LOWER,  KC_DEL,   KC_MS_BTN4,             KC_MS_BTN5, _______, _______, _______, _______,
                                                                 KC_VOLU, KC_MS_BTN3,    KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),

  [_ADJUST] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                         KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LCTL, KC_PSCR,  KC_INS, KC_VOLD, KC_MUTE, KC_VOLU,                                       KC_WBAK, KC_WSCH, KC_WHOM, KC_WFWD, KC_WREF, SCRL_IN,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LSFT,  CPI_SW, SCRL_SW,IME_LOCK, LAG_SWP, KC_MPLY,                                       KC_MPRV, LAG_NRM,IME_UNLOCK,KC_MNXT,_______, _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        _______, _______, _______, _______,  _______,                    _______, _______,   _______, _______, _______,
                                                                 KC_PGUP, KC_MS_BTN3,  KC_PGDOWN, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),

  [_NUMPAD] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                         KC_P7,   KC_P8,   KC_P9, KC_PMNS, KC_PDOT, KC_BSPC,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TT(_NUMPAD),                                     KC_P4,   KC_P5,   KC_P6, KC_PPLS, KC_PSLS, XXXXXXX,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                         KC_P1,   KC_P2,   KC_P3, KC_PEQL, KC_PAST,  KC_NUM,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        _______, _______, _______, _______,  _______,                      KC_P0,  KC_ENT,  _______, _______, _______,
                                                                 KC_PGUP, KC_MS_BTN3,  KC_PGDOWN, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    )
};

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

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 4, .col = 2},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 4, .col = 5},
    .pressed = false
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }

    return true;
}


void matrix_scan_user(void) {

    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

}


/*
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int8_t degree = 45;
    int8_t x_rev, y_rev;
    x_rev =  + mouse_report.x * cos(degree) + mouse_report.y * sin(degree);
    y_rev =  - mouse_report.x * sin(degree) + mouse_report.y * cos(degree);
    if (isScrollMode) {
        mouse_report.h = x_rev;
        #ifdef COCOT_DRAGSCROLL_INVERT
                // Invert vertical scroll direction
                mouse_report.v = -y_rev;
        #else
                mouse_report.v = y_rev;
        #endif
        // mouse_report.v = y_rev;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
    }
    return mouse_report;
}
*/

int hue_fst = -1;
int sat_fst = -1;
int val_fst = -1;


layer_state_t layer_state_set_user(layer_state_t state) {
    hue_fst = rgblight_get_hue();
    sat_fst = rgblight_get_sat();
    val_fst = rgblight_get_val();

    switch (get_highest_layer(state)) {
    case _LOWER:
        rgblight_sethsv_range(HSV_WHITE, 0, 2);
        cocot_set_scroll_mode(true);
        break;
    case _RAISE:
        rgblight_sethsv_range(HSV_CHARTREUSE, 0, 2);
        cocot_set_scroll_mode(true);
        break;
    case _ADJUST:
        rgblight_sethsv_range(HSV_RED, 0, 2);
        cocot_set_scroll_mode(false);
        break;
    case _NUMPAD:
        rgblight_sethsv_range(HSV_BLUE, 0, 2);
        cocot_set_scroll_mode(false);
        break;
    default:
        // rgblight_sethsv_range( 0, 0, 0, 0, 2);
        // rgblight_sethsv_range(hue_fst, sat_fst, val_fst, 0, 2);
        rgblight_sethsv_range(HSV_GREEN, 0, 2);
        cocot_set_scroll_mode(false);
        break;
    }
    rgblight_set_effect_range( 2, 10);
  return state;
};


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    render_logo();
    oled_write_layer_state();
    return false;
}
#endif

