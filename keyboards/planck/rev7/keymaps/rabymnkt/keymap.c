#include QMK_KEYBOARD_H

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
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    TT(_MOUSE), KC_LALT, KC_LGUI, KC_LANG2,  MO(_LOWER),  XXXXXXX, KC_SPC,  MO(_RAISE), KC_LANG1,  KC_RGUI, KC_RALT, KC_RCTL
),

[_LOWER] = LAYOUT_planck_grid(
     KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
    KC_LCTL, XXXXXXX, SGUI(KC_LEFT), KC_ESC, ESC_ENG, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, KC_PLUS,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, TT(_NUMPAD), XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, KC_ENT, MO(_ADJUST), _______,  KC_VOLD, KC_VOLU, KC_MUTE
),

[_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_CIRC,  KC_DLR, KC_UNDS,
    KC_LCTL, KC_MINS,  KC_EQL, KC_PLUS, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_BSLS, KC_SLSH, XXXXXXX, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX,  KC_GRV,   KC_LT, KC_LBRC, KC_RBRC,   KC_GT, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, MO(_ADJUST), _______, KC_DEL, _______, _______,  _______, _______, _______
),


[_ADJUST] = LAYOUT_planck_grid(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
    KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, KC_WAKE, KC_SLEP, KC_WBAK, KC_WSCH, KC_WHOM, KC_WFWD, KC_WREF,  KC_PSCR,
    KC_LSFT, XXXXXXX, XXXXXXX, BL_DEC, BL_TOGG, BL_INC, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_INS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_MOUSE] = LAYOUT_planck_grid(
     KC_TAB, KC_HOME,   KC_UP,  KC_END, KC_PGUP, XXXXXXX, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, KC_BSPC,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, KC_ENT,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______,  _______, _______, _______
),

[_NUMPAD] = LAYOUT_planck_grid(
     KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_P7,   KC_P8,   KC_P9, KC_BSPC, KC_DEL,
    KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_P4,   KC_P5,   KC_P6, KC_ASTR,  KC_PERC,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, TT(_NUMPAD), XXXXXXX, XXXXXXX,  KC_P1,   KC_P2,   KC_P3, KC_PLUS, KC_MINS,
    _______, _______, _______, _______, _______, _______, XXXXXXX ,     KC_P0, KC_PDOT,  KC_ENT, KC_EQL, KC_NLCK
)
};

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); */
/* } */

static bool is_ime_locked = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ESC_ENG:
        if (record->event.pressed) {
            // キーコード ESC_ENG が押された時
            tap_code(KC_ESC);
            tap_code(KC_LANG2);
        }
        return false;
        break;
    }
    return true;
}
