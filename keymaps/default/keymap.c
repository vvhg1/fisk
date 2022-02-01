/* Copyright 2022 @vvhg1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif



//these are the keymaps for the different layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: QWERTY
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |   ESC  |    W   |    E   |    R   |    T   |  / ?  |                                       |    [   |    Y   |    U   |    I   |    O   |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |   &    |    Q   |    S   |    D   |    F   |    G   |  \ |  |                                       |    ]   |    H   |    J   |    K   |    L   |    P   |   ' "  |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |   #    |    A   |    X   |    C   |    V   |    B   |       |  Space |  ALT   |     |        |RShift|        |    N   |    M   |  ,  <  |  . >   |  ;  :  | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |  TAB   |   Z    |           |        |        |  LCTL  |    |        |        |     |  LCTL  |      |     | BSPC  |  DEL  |         |            |  - _   |    @   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 *
 */
    [_QW] = LAYOUT(
              KC_ESC,   KC_W,    KC_E  ,  KC_R ,   KC_T , KC_SLSH,                                      KC_RBRC,   KC_Y,    KC_U ,   KC_I ,   KC_O,   KC_NO,
    KC_AMPR , KC_Q,     KC_S,    KC_D ,   KC_F ,   KC_G,  KC_BSLS,                                      KC_LBRC,   KC_H,    KC_J,    KC_K,    KC_L,    KC_P, KC_QUOT,
    KC_HASH,  KC_A,     KC_X,    KC_C,    KC_V,    KC_B,            KC_SPC, KC_LALT,         KC_NO, KC_RSFT,          KC_N,   KC_M,    KC_COMM,    KC_DOT,  KC_SCLN, KC_ENT,
    KC_TAB,  KC_Z,           KC_NO,  KC_NO,  KC_LCTL,                KC_NO,          KC_LCTL,              KC_BSPC,  KC_DEL, KC_NO,                 KC_MINS,  KC_AT

    )
/*
 * template Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |        |        |        |        |       |                                       |        |        |        |        |        |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |        |        |        |        |        |       |                                       |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |       |        |        |     |        |      |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |        |           |      |          |        |    |        |        |     |        |      |     |      |        |         |            |        |        |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
//    [_NAV] = LAYOUT(
//              _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______,          _______, _______,      _______, _______,        _______, _______, _______, _______, _______, _______,
//     _______, _______,            _______,  _______, _______,                _______,      _______,                _______, _______, _______,           _______, _______

//     ),
};

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    //   debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}
#endif
