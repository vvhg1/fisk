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
 * This is a little tool, that makes transition to new sentence a little smoother.
 * When typing two dots, the second dot will be deleted and the next character will be shifted.
 *
 */
#include "eos_util.h"
#include "keycodes.h"

void process_eos(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        lastkeypressed = thiskeypressed;
        thiskeypressed = keycode;
        switch (keycode) {
            case KC_BSPC:
                if (lastkeypressed == KC_DOT) {
                    thiskeypressed = lastkeypressed;
                    if (dot_counter > 0) {
                        dot_counter--;
                    }
                }
                break;

            case KC_DOT:
                if (dot_counter < 4) {
                    dot_counter++;
                }
                break;

            case KC_ENT:
            case KC_SPC:
            dot_counter = 0;
            break;

            default:
                if (dot_counter == 2) {
                    tap_code(KC_BSPC);
                    tap_code(KC_SPC);
#ifdef CUSTOM_ONE_SHOT_ENABLE
                    register_code16(KC_LSFT);
#else
#    ifndef CUSTOM_ONE_SHOT_ENABLE
                    add_oneshot_mods(MOD_MASK_SHIFT);
#    endif
#endif
                } else {
                    dot_counter = 0;
                }
                break;
        }
    }
}
void release_eos(uint16_t keycode, const keyrecord_t *record) {
    if ((dot_counter == 2) && (keycode != KC_DOT)) {
        if (record->event.pressed) {
#ifdef CUSTOM_ONE_SHOT_ENABLE
            unregister_code16(KC_LSFT);
#endif
            dot_counter = 0;
        }
    }
}
