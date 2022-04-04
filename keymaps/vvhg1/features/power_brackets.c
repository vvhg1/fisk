/* Copyright 2021 @vvhg1
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

/*
 * These are bracket pairs of different types, single- and double-quote pairs.
 *
 */
#include "power_brackets.h"
#include "keycodes.h"
#ifdef CUSTOM_ONE_SHOT_ENABLE
#include "features/custom_oneshot.h"
#endif
uint8_t current_mod_state;

void process_power_brackets(uint16_t keycode, const keyrecord_t *record) {
   switch (keycode) {
        // ------------------------------------------------------------------------ wraps quotes around word ----------------------------------------------------------------
        case QuotWrap:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT){
                    del_mods(MOD_MASK_ALT);
                    if (get_mods() & MOD_MASK_SHIFT){
                        del_mods(MOD_MASK_SHIFT);
                        SEND_STRING(SS_TAP(X_ESC) SS_LCTL(SS_TAP(X_LEFT)) SS_LSFT(SS_TAP(X_QUOT)) SS_LCTL(SS_TAP(X_RGHT)) SS_LSFT(SS_TAP(X_QUOT)));
                    } else {
                        SEND_STRING(SS_TAP(X_ESC) SS_LCTL(SS_TAP(X_LEFT)) SS_TAP(X_QUOT) SS_LCTL(SS_TAP(X_RGHT)) SS_TAP(X_QUOT));
                    }
                } else {
                    SEND_STRING(SS_TAP(X_QUOT));
                }
            }
            break;
                    // ------------------------------------------------------------------------ empty and wrapping bracket pairs ----------------------------------------------------------------
        case Op_BrS:  // like the other but £ instead of ! on shift
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {
                    del_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_TAP(X_ESC) SS_LCTL(SS_TAP(X_LEFT)) SS_LSFT(SS_TAP(X_9)) SS_LCTL(SS_TAP(X_RGHT)) SS_LSFT(SS_TAP(X_0)));
                } else if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P6) SS_TAP(X_P3)));
                } else {
                    tap_code16(S(KC_9));
                    tap_code16(S(KC_0));
                    if(outside_cursor) {tap_code(KC_LEFT);}
                }
            }
            break;
        case Sq_Br:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {
                    del_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_TAP(X_ESC) SS_LCTL(SS_TAP(X_LEFT)) SS_TAP(X_LBRC) SS_LCTL(SS_TAP(X_RGHT)) SS_TAP(X_RBRC));
                } else if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(KC_PLUS);
                } else {
                    tap_code(KC_LBRC);
                    tap_code(KC_RBRC);
                    if(outside_cursor_other) {tap_code(KC_LEFT);}
                }
            }
            break;
        case Cr_Br:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {
                    del_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_TAP(X_ESC) SS_LCTL(SS_TAP(X_LEFT)) SS_LSFT(SS_TAP(X_LBRC)) SS_LCTL(SS_TAP(X_RGHT)) SS_LSFT(SS_TAP(X_RBRC)));
                } else if (get_mods() & MOD_MASK_SHIFT) {
                    current_mod_state = get_mods();
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_EQL);
                    set_mods(current_mod_state);
                } else {
                    tap_code16(S(KC_LBRC));
                    tap_code16(S(KC_RBRC));
                    if(outside_cursor_other) {tap_code(KC_LEFT);}
                }
            }
            break;
        case Op_Br:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {
                    del_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_TAP(X_ESC) SS_LCTL(SS_TAP(X_LEFT)) SS_LSFT(SS_TAP(X_9)) SS_LCTL(SS_TAP(X_RGHT)) SS_LSFT(SS_TAP(X_0)));
                } else if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code(KC_1);
                } else {
                    tap_code16(S(KC_9));
                    tap_code16(S(KC_0));
                    if(outside_cursor) {tap_code(KC_LEFT);}
                }
            }
            break;
        default:
            break;
   }
}
