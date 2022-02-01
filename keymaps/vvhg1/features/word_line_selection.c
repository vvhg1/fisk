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
 *
 */
#include "word_line_selection.h"
#include "keycodes.h"
// #ifdef CUSTOM_ONE_SHOT_ENABLE
// #include "features/word_line_selection.h"
// #endif


bool process_word_line_selection(uint16_t keycode, const keyrecord_t *record) {
        if (record->event.pressed) {
        prev_SelWrd_counter    = SelWrd_counter;
        SelWrd_counter         = 0;
        oldlineflag            = lineflag;
        lineflag               = false;
        }

   switch (keycode) {
        // ------------------------------------------------------------------------ wraps quotes around word ----------------------------------------------------------------
                case SelLn:
            if (record->event.pressed) {  // nees to set flag
                lineflag = true;
                SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
                return false;
            }
        case SelLnDn:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_DOWN)));
                return false;
            }

        case SelLnUp:
            if (record->event.pressed) {
                if (oldlineflag) {
                    SEND_STRING(SS_TAP(X_END) SS_LSFT(SS_TAP(X_HOME)) SS_LSFT(SS_TAP(X_UP)));
                } else {
                    SEND_STRING(SS_LSFT(SS_TAP(X_UP)));
                }
                    return false;
            }

        case SelWrdL:
            if (record->event.pressed) {
                SelWrd_counter = prev_SelWrd_counter;
                if (SelWrd_counter < 2) {
                    SelWrd_counter++;
                }
                if (SelWrd_counter > 1) {
                    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))));
                }
                return false;
            }

        case SelWrdR:
            if (record->event.pressed) {
                SelWrd_counter = prev_SelWrd_counter;
                if (SelWrd_counter < 2) {
                    SelWrd_counter++;
                }
                if (SelWrd_counter > 1) {
                    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT))));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT) SS_LSFT(SS_TAP(X_RIGHT))));
                }
                return false;
            }
    }
    return true;
}

