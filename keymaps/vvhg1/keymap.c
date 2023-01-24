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

#include "features/features.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

bool finished_logo = false;

// these are the keymaps for the different layers
/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |   ESC  |    W   |    F   |    P   |    B   |  / ?  |                                       |    "   |    J   |    L   |    U   |    Y   |  C(P)  |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |   &    |    Q   |    R   |    S   |    T   |    G   |  \ |  |                                       |    !   |    M   |    N   |    E   |    I   |  ;  :  |   ' "  |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |   #    |    A   |   X    |    C   |    D   |    V   |       |  Space |   ALT  |     |  LCTL  |RShift|        |    K   |    H   |  ,  <  |  . >   |    O   | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |  TAB   |    Z   |           |  FUNC  | ML_sc |   BRC   |    |        |  NAV   |     |  LEAD  |      |     | BSPC  | DEL   |  ENC M  |            |  - _   |    @   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 *
 */
    [_COLEMAK] = LAYOUT(
              KC_ESC,   KC_W,    KC_F  ,  KC_P ,   KC_B , KC_SLSH,                                      KC_DQT,   KC_J,    KC_L ,   KC_U ,   KC_Y ,   C(KC_P),
    KC_AMPR , KC_Q,     KC_R,    KC_S ,   KC_T ,   KC_G,  KC_BSLS,                                      KC_EXLM,   KC_M,    KC_N,    KC_E,    KC_I,    KC_SCLN,      KC_QUOT,
    KC_HASH,  KC_A,     KC_X,    KC_C,    KC_D,    KC_V,            KC_SPC, ML_alt,        ML_ctl, MR_sft,       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_O,         KC_ENT,
    KC_TAB,  KC_Z,           mo_FUNX,  ML_sc ,  mo_BR,                    go_NAV,        LEADER,              KC_BSPC, KC_DEL, Enc_M,                 KC_MINS,  KC_AT

    ),
/*
 * Base Layer: QWERTY
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |   ESC  |    W   |    E   |    R   |    T   |  / ?  |                                       |    "   |    Y   |    U   |    I   |    O   |   C(P) |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |   &    |    Q   |    S   |    D   |    F   |    G   |  \ |  |                                       |    !   |    H   |    J   |    K   |    L   |    P   |   ' "  |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |   #    |    A   |    X   |    C   |    V   |    B   |       |  Space |  ALT   |     |  LCTL  |RShift|        |    N   |    M   |  ,  <  |  . >   |  ;  :  | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |  TAB   |   Z    |           |  FUNC  | ML_sc |   BRC   |    |        |  NAV   |     |  LEAD  |      |     | BSPC  |  DEL  |  ENC M  |            |  - _   |    @   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 *
 */
    [_QW] = LAYOUT(
              KC_ESC,   KC_W,    KC_E  ,  KC_R ,   KC_T , KC_SLSH,                                      KC_DQT,   KC_Y,    KC_U ,   KC_I ,   KC_O,   C(KC_P),
    KC_AMPR , KC_Q,     KC_S,    KC_D ,   KC_F ,   KC_G,  KC_BSLS,                                      KC_EXLM,   KC_H,    KC_J,    KC_K,    KC_L,    KC_P, KC_QUOT,
    KC_HASH,  KC_A,     KC_X,    KC_C,    KC_V,    KC_B,            KC_SPC, ML_alt,         ML_ctl, MR_sft,          KC_N,   KC_M,    KC_COMM,    KC_DOT,  KC_SCLN, KC_ENT,
    KC_TAB,  KC_Z,                mo_FUNX,  ML_sc,  mo_BR,                go_NAV,          LEADER,              KC_BSPC,  KC_DEL, Enc_M,                 KC_MINS,  KC_AT

    ),
#ifdef SWAP_HANDS_ENABLE

/*
 * Mirroring Layer, only gets included if the feature is enabled
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |        |        |        |        |       |                                       |        |        |        |        |        |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |        |        |        |        |        |       |                                       |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |       | Mirror |        |     |        |      |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--.    |  Space +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |        |           |      |          |        |    |        |        |     |        |      |     |      |        |         |            |        |        |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
   [_MIR] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          Mir_spc, _______,      _______, Mir_spc,        _______, _______, _______, _______, _______, _______,
    _______, _______,            _______,  _______, _______,                MR_sft,      MR_sft,                _______, _______, _______,           _______, _______

    ),
#endif
/*
 * BRACKETS Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |        |        |        |        |       |                                       |        |        |        |        |        |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |        |        |        |        |        |       |                                       |        |        |    {   |    [   |    ]   |        |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |       |        |        |     |        |      |        |        |    (   |    <   |    >   |    }   |        |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |        |           |      |          |        |    |        |        |     |        |      |     |      |        |         |            |    )   |        |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
   [_BRACKETS] = LAYOUT(
             _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                                        _______, _______, S(KC_LBRC), KC_LBRC, KC_RBRC, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______,      _______, _______,        _______, S(KC_9), S(KC_COMM), S(KC_DOT), S(KC_RBRC), _______,
    _______, _______,            _______,  _______, _______,                _______,      _______,                _______, _______, _______,           S(KC_0), _______

    ),
/*
 * Num Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |  `     |   ~    |    %   |    ^   |       |                                       |        |    *   |   7 &  |   8 *  |   9 (  |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |    €   |  Cut   | Copy   | Paste  |  Redo  | Save  |                                       |        |   . ,  |   1 !  |   2 @  |   3 #  |   +    |   $    |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * | Sel All|  Undo  |    ↑   |    ↓   |    →   |        |       |        |        |     |        |      |        |   /    |   4 $  |   5 %  |   6 ^  |   =    | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+  0   |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |   ←    |           |      |          |        |    |        |        |     |        |      |     |      |        |         |            |   -    |   ,    |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
    [_NUM] = LAYOUT(
             _______,  KC_GRV, S(KC_GRV), S(KC_5), S(KC_6), _______,                                      _______,   S(KC_8),   KC_7 ,   KC_8 ,   KC_9 ,   _______,
    _______, EURO_SYM,    Cut,     Copy ,   Paste,    Redo, C(KC_S),                                     _______,    KC_DOT,      KC_1,    KC_2,    KC_3,    KC_PLUS,   S(KC_4),
    C(KC_A),     Undo,  KC_UP,   KC_DOWN, KC_RIGHT, _______,        _______,_______,        _______, KC_0,       KC_PSLS,   KC_4,    KC_5,    KC_6,  KC_EQL,   _______,
    _______, KC_LEFT,             _______,  _______,  _______,              _______,        _______,            _______, _______, _______,             _______,   KC_COMM

    ),
/*
 * Navigation Layer: Navigation
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |  `     |  Find  |        | SdeBar | Cmmnt |                                       |        | go def |   Home |  PG DN |  PG UP |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |   €    |  Cut   |  Copy  |  Paste |  Redo  |  Save |                                       |        | pk def |    ←   |    ↓   |    ↑   |  End   |   ' "  |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * | Sel All|  Undo  |  Xplor |  R_sft |  LCTL  |        |       |        |        |     |        |      |        | dbg log| SelWrdL| SelLn↓ | SelLn↑ |    →   | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+ R_sft|     ,--+--------+--------+--------+--------+--------+--------|
 * |        |   ←    |           |        |        |        |    |        |        |     |        |      |     |        |      |         |            | SelWrdR|   F2   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
    [_NAV] = LAYOUT(
             _______, _______, C(KC_F), _______, C(KC_B),  Cmnt,                                         _______, Go_Def, KC_HOME, KC_PGDN, KC_PGUP, _______,
    _______, _______,  Cut   ,    Copy,  Paste,    Redo, C(KC_S),                                        _______, Peek_Def, KC_LEFT, KC_DOWN, KC_UP,  KC_END, KC_QUOT,
    C(KC_A),   Undo,   C(S(KC_Q)), MR_sft, ML_ctl, _______,          _______, _______,      _______, MR_sft,         Dbg, SelWrdL,   SelLnDn,  SelLnUp, KC_RIGHT, _______,
    _______, KC_LEFT,             _______,  _______, _______,                _______,      _______,                _______, _______, _______,           SelWrdR,     KC_F2

    ),
/*
 * Mouse Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |M WH dn | M WH up| M WH R |        |       |                                       |        | go def |   Home |  PG DN |  PG UP |        |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * | M btn5 | M WH L |  M up  | M down | M right| M btn1 |       |                                       |        | pk def |  Enter |  ESC   |    ↑   |  End   |   ' "  |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * | M btn2 | M left |        |        |        |        |       |        |        |     |        |      |        | dbg log| SelWrdL| SelLn↓ | SelLn↑ |    →   | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * | M btn4 |        |           |      |          |        |    |        |        |     |        |      |     |        |      |         |            | SelWrdR|   F2   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
   [_MOUSE] = LAYOUT(
             _______, KC_WH_U, KC_WH_D, KC_WH_R, _______, _______,                                        _______, Go_Def, KC_HOME, KC_PGDN, KC_PGUP, _______,
    KC_BTN5, KC_WH_L, KC_MS_U, KC_MS_D, KC_MS_R, KC_BTN1, _______,                                        _______, Peek_Def, KC_ENT, KC_ESC, KC_UP,  KC_END, KC_QUOT,
    KC_BTN2, KC_MS_L, _______, _______, KC_NO, _______,          _______, _______,      _______, _______,         Dbg, SelWrdL,   SelLnDn,  SelLnUp, KC_RIGHT, _______,
    KC_BTN4, _______,            _______,  _______, _______,                _______,      _______,                 _______, _______, _______,           SelWrdR,     KC_F2

    ),
/*
 * Function Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |Lin/Win |        |        |        | MO AUX|                                       |In_br_s |  KC_NO |  KC_F7 |  KC_F8 |  KC_F9 |  In_br |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        | Qwerty |        |        |        |        |       |                                       |In_br_c |  KC_NO |  KC_F1 |  KC_F2 |  KC_F3 | KC_F10 |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | Colemak|        |        |       |        |        |     |        |      |        |  KC_NO |  KC_F4 |  KC_F5 |  KC_F6 | KC_F11 | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        | Mirror |           |     |        |        |       |        |        |     |        |      |     |      |        |         |            | KC_F12 |        |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
   [_FUNX] = LAYOUT(
             _______, Lin_Win, _______, _______, _______, mo_AUX,                                        _______, KC_NO,  KC_F7,   KC_F8,   KC_F9,  _______,
    _______, DF(_QW), _______, _______, _______, _______, _______,                                       _______, KC_NO,  KC_F1,   KC_F2,   KC_F3,   KC_F10,  _______,
    _______, _______,  _______, DF(_COLEMAK), _______, _______,  _______, _______,      _______, _______,       KC_NO,  KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
    _______,
    #ifdef SWAP_HANDS_ENABLE
            TG(_MIR)
#else
_______
#endif
                    ,            _______,  _______, _______,                  _______,      _______,                _______, _______, _______,          KC_F12, _______

    ),
/* * Aux Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          | RESET  | DEBUG  |        |        |        |       |                                       |        |        |        |        |        | RESET  |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |        |        |        |        |        |       |                                       |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |       |        |        |     |        |      |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |        |           |      |          |        |    |        |        |     |        |      |     |      |        |         |            |        |        |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
   [_AUX] = LAYOUT(
             RESET, DEBUGg, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, RESET,
    _______, _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______,      _______, _______,        _______, _______, _______, _______, _______, _______,
    _______, _______,            _______,  _______, _______,                _______,      _______,                _______, _______, _______,           _______, _______

    ),
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

/* clang-format on */

void matrix_init_user(void) {
#ifdef ENCODER_ENABLE
    encoder_utils_init();
#endif
}
#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    //   debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}
#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CUSTOM_LEADER_ENABLE
    if (!process_leader(keycode, record)) {
        return false;
    }
#endif
    // ------------------------------------------------------------------------call case modes----------------------------------------------------------------
#ifdef CASEMODES_ENABLE
    if (!process_case_modes(keycode, record)) {
        return false;
    }
#endif
// ------------------------------------------------------------------------------call custom one shots----------------------------------------------------------------
#ifdef CUSTOM_ONE_SHOT_ENABLE
    process_custom_one_shot(keycode, record);
#endif
    // ------------------------------------------------------------------------------process_eos_logic----------------------------------------------------------------
#ifdef EOS_ENABLE
    process_eos(keycode, record);
#endif
// ----------------------------------------------------------------------------------power brackets-----------------------------------------------------------------
#ifdef POWER_BRACKETS_ENABLE
    process_power_brackets(keycode, record);
#endif
#ifdef CUSTOM_WORD_LINE_SELECTION_ENABLE
    if (!process_word_line_selection(keycode, record)) {
        return false;
    }
#endif
    // -----------------------------------------------------------flags for line selection and a few other things----------------------------------------------------------------
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        turn_oled_on = true;
        startup_timer = timer_read();
#endif
        prev_layer_toggle_flag = layer_toggle_flag;
        layer_toggle_flag      = false;
        finished_logo          = true;
        custom_space_cadet     = true;
        if (keycode != KC_BSPC && keycode != KC_DEL) {
            space_pressed = false;
        }


#ifdef SWAP_HANDS_ENABLE
        no_swap = true;
#endif
    }
    switch (keycode) {  //!#######################################################--switch(keycode)--#######################################################

        case KC_BSPC:
            if (record->event.pressed && space_pressed) {
                tap_code16(LCTL(KC_BSPC));
                return false;
            }
            return true;

        case KC_DEL:
            if (record->event.pressed && space_pressed) {
                tap_code16(LCTL(KC_Z));
                return false;
            }
            return true;

        case KC_SPC:
            if (record->event.pressed) {
                if(!is_leading())
                {
                    space_pressed = true;
                    custom_space_cadet = false;
                }
                process_custom_layer(record, mo_NUM);
                return false;
            } else {
                if(!custom_space_cadet){
#ifdef CASEMODES_ENABLE
                    keyrecord_t new_record;
                    new_record.event.pressed = true;
                    keyrecord_t *new_record_p = &new_record;
                    if (!process_case_modes(KC_SPC, new_record_p)) {
                        if (layer_state_is(_NUM)) {
                            process_custom_layer(record, mo_NUM);
                        }
                        space_pressed = false;
                        return false;
                    }
#endif
                    tap_code(KC_SPC);
                }
                if (layer_state_is(_NUM)) {
                    custom_space_cadet = false;
                    space_pressed = false;
                    process_custom_layer(record, mo_NUM);
                }
            }
            return true;

        case Lin_Win:
            if (record->event.pressed) {
                if (is_windows) {
                    is_windows = false;
                } else {
                    is_windows = true;
                }
            }
            return true;
        case Cmnt:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(LALT(KC_A));
                } else {
                    tap_code16(C(KC_SLASH));
                }
            }
            return true;

#ifdef POWER_BRACKETS_ENABLE
        case In_br_o:
            if (record->event.pressed) {
                outside_cursor_op = outside_cursor_op ? false : true;
            }
            return true;
        case In_br_c:
            if (record->event.pressed) {
                outside_cursor_cr = outside_cursor_cr ? false : true;
            }
            return true;
        case In_br_s:
            if (record->event.pressed) {
                outside_cursor_sq = outside_cursor_sq ? false : true;
            }
            return true;
#endif

        case Go_Def:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                }
                tap_code(KC_F12);
            }
            return true;

        case Peek_Def:
            if (record->event.pressed) {
                if (is_windows) {
                    tap_code16(LALT(KC_F12));
                } else {
                    tap_code16(LCTL(LSFT(KC_F10)));
                }
            }
            return true;

        case Dbg:
            if (record->event.pressed) {
                tap_code16(LCTL(LSFT(KC_L)));
            }
            return true;
        case EURO_SYM:
            if (record->event.pressed) {
                if (is_windows)
            {
                SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P2) SS_TAP(X_P8)));  // send euro symbol
            }else{
            tap_code16(C(S(KC_U)));
            SEND_STRING("20AC");  // here euro symbol
            tap_code(KC_ENT);
            }
            }
            return false;

#ifdef SWAP_HANDS_ENABLE
        case Mir_spc:
            if (record->event.pressed) {
                swap_hands     = true;
                no_swap        = false;
                one_shot_timer = timer_read();
            } else {
                swap_hands = false;
                if (!no_swap && (timer_elapsed(one_shot_timer) < 500)) {
                    tap_code(KC_SPC);
                }
            }
            return true;
#endif
            // ------------------------------------------------------------------------custom layer logic ----------------------------------------------------------------
        case mo_BR:
            process_custom_layer(record, _BRACKETS);
            return true;

        case mo_FUNX:
            process_custom_layer(record, _FUNX);
            return true;

        case mo_AUX:
            process_custom_layer(record, _AUX);
            return true;

        case go_NAV:
            if ((get_mods() & MOD_MASK_SHIFT) || (IS_LAYER_ON(_NUM))) {
                // go to num
                process_custom_layer(record, _NUM);
            } else {
                // go to nav
                process_custom_layer(record, _NAV);
            }
            return true;

        case go_NUM:
            process_custom_layer(record, _NUM);
            return true;

            // ------------------------------------------------------------------------call leader ----------------------------------------------------------------
#ifdef CUSTOM_LEADER_ENABLE
        case LEADER:
            if (record->event.pressed) {
#    ifdef CUSTOM_LEADER_TO_DL
                //switch to default layer
                if (IS_LAYER_ON(_NAV)) {
                    layer_off(_NAV);
                }
                // if (IS_LAYER_ON(_NUM)) {
                //     layer_off(_NUM);
                // }
#    endif
                //switch to mouse layer only while pressed
                layer_on(_MOUSE);
                layer_toggle_flag = true;
            }else{
                layer_off(_MOUSE);
                //if no other keys were pressed, call leader
                if (layer_toggle_flag) {
                    layer_toggle_flag = false;
                    start_leading();
                }
            }
            return false;
#endif
            // ------------------------------------------------------------------------ cycle_encoder_mode ----------------------------------------------------------------
#ifdef ENCODER_ENABLE
        case Enc_M:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    cycle_encoder_mode(false);
                } else {
                    cycle_encoder_mode(true);
                }
            }
            break;
#endif
#ifdef CASEMODES_ENABLE
        case CAPS_WORD:
            if (record->event.pressed) {
                toggle_caps_word();
            }
            return false;

        case SNAKE_CASE:
            if (record->event.pressed) {
                toggle_xcase();
            }
            return false;

        case NUM_WORD:
            if (record->event.pressed) {
                toggle_num_word();
            }
            return false;
#endif
        // ------------------------------------------------------------------------ cut copy paste undo redo ----------------------------------------------------------------
        case Undo:
            if (record->event.pressed) {
                register_code16(C(KC_Z));
            }else {
                unregister_code16(C(KC_Z));
            }
            break;
        case Cut:
            if (record->event.pressed) {
                register_code16(C(KC_X));
            }else {
                unregister_code16(C(KC_X));
            }
            // break;
            return false;
        case Copy:
            if (record->event.pressed) {
                tap_code16(C(KC_C));
            }
            break;
        case Paste:
            if (record->event.pressed) {
                tap_code16(C(KC_V));
            }
            break;
        case Redo:
            if (record->event.pressed) {
                register_code16(C(KC_Y));
            }else {
                unregister_code16(C(KC_Y));
            }
            break;
    }
    return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CUSTOM_ONE_SHOT_ENABLE
    release_custom_one_shot(keycode, record);
#endif
#ifdef EOS_ENABLE  //----------------------------------------------------------process_eos_logic----------------------------------------------------------------
    release_eos(keycode, record);
#endif
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    turn_oled_on = true;
    cleared_oled  = false;
    return rotation;
}

#    ifndef CONSOLE_ENABLE
bool oled_task_user(void) {
    if ((timer_elapsed(startup_timer) < 6000) && !finished_logo) {
        if (is_keyboard_left()) {
            render_logo_l();
        } else {
            render_logo_r();
        }
    } else {
        if (!cleared_oled) {
            oled_clear();
            cleared_oled = true;
        }
        finished_logo = true;
        if (timer_elapsed(startup_timer) > 25000) {
            oled_off();
            turn_oled_on = false;
        } else if(turn_oled_on){
            oled_on();
            oled_clear();
            render_status();
            if((timer_elapsed(startup_timer) > 800) && (space_pressed) && !custom_space_cadet){
                register_code(KC_SPC);
            }
        }

    }
    return false;
}
#    endif
#    ifdef CONSOLE_ENABLE
bool oled_task_user(void) {
    render_status();
    return false;
}
#    endif
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action(get_encoder_mode(), clockwise);
#    ifdef OLED_ENABLE
    oled_on();
#    endif
    return true;
}
#endif
#ifdef SPLIT_TRANSPORT_MIRROR
bool should_process_keypress(void) {
    return true;
    }
#endif
