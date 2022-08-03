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
 *                                                                                                         wrap brackets on ALT
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |   ESC  |    W   |    F   |    P   |    B   |  / ?  |                                       |  [c] + |    J   |    L   |    U   |    Y   |  (c) ! |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |   &    |    Q   |    R   |    S   |    T   |    G   |  \ |  |                                       |  {c} = |    M   |    N   |    E   |    I   |  ;  :  |   ' "  | wrap quote on ALT
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |   #    |    A   |   X    |    C   |    D   |    V   |       |  Space |   ALT  |     |  LCTL  |RShift|        |    K   |    H   |  ,  <  |  . >   |    O   | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |  TAB   |    Z   |           |  FUNC   | RShift |  LCTL |    |        |  NAV   |     |  LEAD  |      |     | BSPC  | DEL   |  ENC M  |            |  - _   |    @   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 *
 */
    [_COLEMAK] = LAYOUT(
              KC_ESC,   KC_W,    KC_F  ,  KC_P ,   KC_B , KC_SLSH,                                      Sq_Br,   KC_J,    KC_L ,   KC_U ,   KC_Y ,   Op_Br,
    KC_AMPR , KC_Q,     KC_R,    KC_S ,   KC_T ,   KC_G,  KC_BSLS,                                      Cr_Br,   KC_M,    KC_N,    KC_E,    KC_I,    KC_SCLN,      QuotWrap,
    KC_HASH,  KC_A,     KC_X,    KC_C,    KC_D,    KC_V,            KC_SPC, ML_alt,        ML_ctl, MR_sft,       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_O,         KC_ENT,
    KC_TAB,  KC_Z,           mo_FUNX,  MR_sft ,  go_NUM,                    go_NAV,        LEADER,              KC_BSPC, KC_DEL, Enc_M,                 KC_MINS,  KC_AT

    ),
/*
 * Base Layer: QWERTY
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |   ESC  |    W   |    E   |    R   |    T   |  / ?  |                                       |  [c] + |    Y   |    U   |    I   |    O   |  (c) ! |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |   &    |    Q   |    S   |    D   |    F   |    G   |  \ |  |                                       |  {c} = |    H   |    J   |    K   |    L   |    P   |   ' "  |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |   #    |    A   |    X   |    C   |    V   |    B   |       |  Space |  ALT   |     |  LCTL  |RShift|        |    N   |    M   |  ,  <  |  . >   |  ;  :  | Enter  |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |  TAB   |   Z    |           |  FUNC  | RShift |  LCTL  |    |        |  NAV   |     |  LEAD  |      |     | BSPC  |  DEL  |  ENC M  |            |  - _   |    @   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 *
 */
    [_QW] = LAYOUT(
              KC_ESC,   KC_W,    KC_E  ,  KC_R ,   KC_T , KC_SLSH,                                      Sq_Br,   KC_Y,    KC_U ,   KC_I ,   KC_O,   Op_Br,
    KC_AMPR , KC_Q,     KC_S,    KC_D ,   KC_F ,   KC_G,  KC_BSLS,                                      Cr_Br,   KC_H,    KC_J,    KC_K,    KC_L,    KC_P, QuotWrap,
    KC_HASH,  KC_A,     KC_X,    KC_C,    KC_V,    KC_B,            KC_SPC, ML_alt,         ML_ctl, MR_sft,          KC_N,   KC_M,    KC_COMM,    KC_DOT,  KC_SCLN, KC_ENT,
    KC_TAB,  KC_Z,           mo_FUNX,  MR_sft,  go_NUM,                go_NAV,          LEADER,              KC_BSPC,  KC_DEL, Enc_M,                 KC_MINS,  KC_AT

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
 * Num Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |  ` ~   |    Up  |    %   |    (   |   )   |                                       |  {c} + |    *   |   7 &  |   8 *  |   9 (  | (e) £  |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        |    €   |    ↑   |    ↓   |    →   |        |       |                                       |  [c] = |   0 )  |   1 !  |   2 @  |   3 #  |   . ,  |   $    |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |    ←   |  Cut   |  Copy  |  Redo  |  Paste |       |        |        |     |        |      |        |   /    |   4 $  |   5 %  |   6 ^  |   +    |        |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |   Undo |           |      |          |        |    |        |        |     |        |      |     |      |        |         |            |        |    =   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
    [_NUM] = LAYOUT(
             _______,  KC_GRV,   KC_UP  , KC_PERC ,KC_LPRN , KC_RPRN,                                      _______,   KC_PAST,   KC_7 ,   KC_8 ,   KC_9 ,   Op_BrS,
    _______, EURO_SYM, KC_UP,   KC_DOWN , KC_RIGHT,_______, _______,                                     _______,  KC_0,      KC_1,    KC_2,    KC_3,    DotC,   S(KC_4),
    _______, KC_LEFT,     Cut,    Copy,  Redo,   Paste,               _______,_______,        _______, _______,    KC_PSLS,   KC_4,    KC_5,    KC_6,  KC_PLUS,   _______,
    _______,    Undo,           _______,  _______,  _______,                  _______,        _______,            _______, _______, _______,                   _______,   KC_EQL

    ),
/*
 * Navigation Layer: Mouse Navigation
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        | M WH dn| M up   | M WH up| M WH R | Cmmnt |                                       |   { +  | go def |   Home |  PG DN |  PG UP |  ( !   |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        | M WH L | M left | M down | M right| M btn1 |  Save |                                       |   [ =  | pk def |    ←   |    ↓   |    ↑   |  End   |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * | back   | Sel All|  Cut   |  Copy  |  Redo  |  Paste |       |        |        |     |        |      |        | dbg log| SelWrdL| SelLn↓ | SelLn↑ |    →   |        |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        |  Undo  |           |        |        |  LCTL  |    |        |        |     |        |      |     |        |      |         |            | SelWrdR|   F2   |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
    [_NAV] = LAYOUT(
             _______, KC_WH_D, KC_MS_U, KC_WH_U,  KC_WH_R,  Cmnt,                                         _______, Go_Def, KC_HOME, KC_PGDN, KC_PGUP, Op_Br,
    _______, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, C(KC_S),                                        _______, Peek_Def, KC_LEFT, KC_DOWN, KC_UP,  KC_END, KC_QUOT,
    KC_BTN4, C(KC_A),  Cut   ,    Copy,   Redo,   Paste,          _______, _______,      _______, _______,         Dbg, SelWrdL,   SelLnDn,  SelLnUp, KC_RIGHT, _______,
    _______,    Undo,           _______,  _______, ML_ctl,                _______,      _______,                _______, _______, _______,           SelWrdR,     KC_F2

    ),
/*
 * Function Layer
 *
 *          ,----------------------------------------------------.                                       ,-----------------------------------------------------.
 *          |        |Lin/Win | Flp MIN|        |        | MO AUX|                                       |In_br_s |  KC_NO |  KC_F7 |  KC_F8 |  KC_F9 |  In_br |
 * +--------+--------+--------+--------+--------+--------+-------|                                       |--------+--------+--------+--------+--------+--------+--------.
 * |        | Qwerty |        |        |        |        |       |                                       |In_br_c |  KC_NO |  KC_F1 |  KC_F2 |  KC_F3 | KC_F10 |        |
 * |--------+--------+--------+--------+--------+--------+-------+--------+--------.     ,---------------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | Colemak|FLP_DOT |        |       |        |        |     |        |      |        |  KC_NO |  KC_F4 |  KC_F5 |  KC_F6 | KC_F11 |        |
 * |--------+--------+--------+--------+--------+--------+--.    |        +--------|     |--------+      |     ,--+--------+--------+--------+--------+--------+--------|
 * |        | Mirror |           |     |        |        |       |        |        |     |        |      |     |      |        |         |            | KC_F12 |        |
 * `-----------------'           `--------------------------'    '--------+--------'     `---------------'     '-------------------------'            '-----------------'
 */
   [_FUNX] = LAYOUT(
             _______, Lin_Win, FLP_MIN, _______, _______, mo_AUX,                                        In_br_s, KC_NO,  KC_F7,   KC_F8,   KC_F9,  In_br_o,
    _______, DF(_QW), _______, _______, _______, _______, _______,                                       In_br_c, KC_NO,  KC_F1,   KC_F2,   KC_F3,   KC_F10,  _______,
    _______, _______,  _______, DF(_COLEMAK), FLP_DOT_C, _______,  _______, _______,      _______, _______,       KC_NO,  KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
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
        prev_layer_toggle_flag = layer_toggle_flag;
        layer_toggle_flag      = false;
        finished_logo          = true;
#ifdef SWAP_HANDS_ENABLE
        no_swap = true;
#endif
    }
    switch (keycode) {  //!#######################################################--switch(keycode)--#######################################################
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
            // windows
                SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P2) SS_TAP(X_P8)));  // send euro symbol
            }else{
            // linux
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
        case mo_FUNX:
            process_custom_layer(record, _FUNX);
            return true;

        case mo_AUX:
            process_custom_layer(record, _AUX);
            return true;

        case go_NAV:
            // if (get_mods() & MOD_MASK_SHIFT) {
            //     // go to num
            //     process_custom_layer(record, _NUM);
            // } else {
                // go to nav
                process_custom_layer(record, _NAV);
            // }
            return true;

        case go_NUM:
            process_custom_layer(record, _NUM);
            return true;

            // ------------------------------------------------------------------------call leader ----------------------------------------------------------------
#ifdef CUSTOM_LEADER_ENABLE
        case LEADER:
            if (record->event.pressed) {
#    ifdef CUSTOM_LEADER_TO_DL
                if (IS_LAYER_ON(_NAV)) {
                    layer_off(_NAV);
                    layer_toggle_flag = false;
                }
                if (IS_LAYER_ON(_NUM)) {
                    layer_off(_NUM);
                    layer_toggle_flag = false;
                }
#    endif
                start_leading();
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
        // ------------------------------------------------------------------------ toggles minus and underscore flip ----------------------------------------------------------------
        case FLP_MIN:
            if (record->event.pressed) {
                if (mns_flipped) {
                    mns_flipped = false;
                } else {
                    mns_flipped = true;
                }
            }
            break;
        // ------------------------------------------------------------------------ toggles num dot and comma flip ----------------------------------------------------------------
        case FLP_DOT_C:
            if (record->event.pressed) {
                if (dot_flipped) {
                    dot_flipped = false;
                } else {
                    dot_flipped = true;
                }
            }
            break;
        // ------------------------------------------------------------------------ processes minus and accounts for flipped minus ----------------------------------------------------------------
        case KC_MINS:
            if (record->event.pressed) {
                if (mns_flipped) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        mod_state = get_mods();
                        del_mods(MOD_MASK_SHIFT);
                        tap_code(KC_MINS);
                        set_mods(mod_state);
                    } else {
                        tap_code16(KC_UNDS);
                    }
                    return false;
                }
            }
            break;
            // ------------------------------------------------------------------------ toggles case modes ----------------------------------------------------------------
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
        // ------------------------------------------------------------------------ custom key on num layer with dot and comma when shifted ----------------------------------------------------------------
        case DotC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    if (dot_flipped) {
                        tap_code(KC_DOT);
                    } else {
                        tap_code(KC_COMM);
                    }
                } else {
                    if (dot_flipped) {
                        tap_code(KC_COMM);
                    } else {
                        tap_code(KC_DOT);
                    }
                }
                return false;
            }
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
        oled_clear();
        render_status();
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
