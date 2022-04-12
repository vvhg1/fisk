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
 * This is a little tool, that makes transition to new sentence a little smoother. When typing two dots, the second dot will be deleted and the next character will be shifted.
q *
 */
#include "word_line_selection.h"
#include "keycodes.h"

bool process_word_line_selection(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed && keycode != MR_sft && keycode != KC_RSHIFT) {
        oldlineflag = lineflag;
        lineflag    = false;
    }

    switch (keycode) {
            // ------------------------------------------------------------------------ wraps quotes around word ----------------------------------------------------------------
        case SelLn:
             if (record->event.pressed) {
                uint8_t temp_mods = get_mods();
                lineflag = true;
                if (oldlineflag) {
                    if (get_mods() & MOD_MASK_SHIFT) {
                        register_code(KC_UP);
                        } else {
                        register_code16(S(KC_DOWN));
                        return true;
                    }
                }else if (get_mods() & MOD_MASK_SHIFT) {
                    clear_mods();
                                tap_code(KC_DOWN);
                                tap_code(KC_END);
                                tap_code(KC_HOME);
                                tap_code(KC_HOME);
                    set_mods(temp_mods);
                    register_code(KC_UP);
                } else {

                                tap_code(KC_END);
                                tap_code(KC_HOME);
                                tap_code(KC_HOME);
                    register_code16(LSFT(KC_DOWN));
                }
                return true;
            } else {
                        unregister_code16(S(KC_UP));
                        unregister_code16(LSFT(KC_DOWN));
                break;
            }

        case SelLnDn:
            if (record->event.pressed) {
                lineflag = true;
                register_code16(LSFT(KC_DOWN));
                return false;
            } else {
                unregister_code16(LSFT(KC_DOWN));
                break;
            }

        case SelWrdL:
            if (record->event.pressed) {
                lineflag = true;
                if (oldlineflag) {
                    register_code16(C(S(KC_LEFT)));
                } else {
                    tap_code16(LCTL(KC_RIGHT));
                    register_code16(C(S(KC_LEFT)));
                }
                return false;
            } else {
                unregister_code16(LSFT(KC_LEFT));
                break;
            }

        case SelWrdR:
            if (record->event.pressed) {
                lineflag = true;
                if (oldlineflag) {
                    register_code16(C(S(KC_RIGHT)));
                } else {
                    tap_code16(LCTL(KC_LEFT));
                    register_code16(C(S(KC_RIGHT)));
                }
                return false;
            } else {
                unregister_code16(LSFT(KC_RIGHT));
                break;
            }
    }
    return true;
}
