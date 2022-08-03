/* Copyright 2021 @vvhg1, expanded on code from @GauthamYerroju
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

#include "encoder_utils.h"

void encoder_utils_init(void) {
    enc_mode = ENC_MODE_NEXTTAB;
}

void set_encoder_mode(encoder_mode_t mode) {
     enc_mode = mode;
}

encoder_mode_t get_encoder_mode(void) {
     return enc_mode;
}

void cycle_encoder_mode(bool clockwise) {
    encoder_mode_t mode = get_encoder_mode();
    if(clockwise){
    mode = (mode == (_ENC_MODE_LAST - 1)) ? 0 : (mode + 1);
    } else {
    mode = (mode == (ENC_MODE_NEXTTAB)) ? (_ENC_MODE_LAST - 1) : (mode - 1);
    }
    set_encoder_mode(mode);
}

// void encoder_action_word_nav(uint8_t clockwise) {
//     if (clockwise) {
//         tap_code16(C(KC_RIGHT));
//     } else {
//         tap_code16(C(KC_LEFT));
//     }
// }

// void encoder_action_left_right(uint8_t clockwise) {
//     if (clockwise) {
//         tap_code(KC_RIGHT);
//     } else {
//         tap_code(KC_LEFT);
//     }
// }

// void encoder_action_up_down(uint8_t clockwise) {
//     if (clockwise) {
//         tap_code(KC_UP);
//     } else {
//         tap_code(KC_DOWN);
//     }
// }

// void encoder_action_paging(uint8_t clockwise) {
//     if (clockwise) {
//         tap_code(KC_PGUP);
//     } else {
//         tap_code(KC_PGDN);
//     }
// }
// void encoder_action_nexteditor(uint8_t clockwise) {
//     if (clockwise) {
//         SEND_STRING(SS_LCTRL(SS_TAP(X_K)) SS_LCTRL(SS_TAP(X_RIGHT)));
//         } else {
//         SEND_STRING(SS_LCTRL(SS_TAP(X_K)) SS_LCTRL(SS_TAP(X_LEFT)));
//     }
// }
void encoder_action_nexttab(uint8_t clockwise) {
    if (clockwise) {
        register_code(KC_LCTL);
        // wait_ms(100);
        tap_code(KC_PGDN);
        // wait_ms(100);
        unregister_code(KC_LCTL);
    } else {
        register_code(KC_LCTL);
        // wait_ms(100);
        tap_code(KC_PGUP);
        // wait_ms(100);
        unregister_code(KC_LCTL);
    }
}
void encoder_action_expandselection(uint8_t clockwise) {
    if (clockwise) {
        tap_code16(LSA(KC_RIGHT));
    } else {
        tap_code16(LSA(KC_LEFT));
    }
}

void encoder_action(encoder_mode_t mode, uint8_t clockwise) {
    switch (mode) {
        case ENC_MODE_NEXTTAB:
            encoder_action_nexttab(clockwise);
            break;
        // case ENC_MODE_WORD_NAV:
        //     encoder_action_word_nav(clockwise);
        //     break;
        // case ENC_MODE_LEFT_RIGHT:
        //     encoder_action_left_right(clockwise);
        //     break;
        // case ENC_MODE_UP_DOWN:
        //     encoder_action_up_down(clockwise);
        //     break;
        // case ENC_MODE_PAGING:
        //     encoder_action_paging(clockwise);
        //     break;
        // case ENC_MODE_NEXTEDITOR:
        //     encoder_action_nexteditor(clockwise);
        //     break;
        case ENC_MODE_EXPAND_SELECTION:
            encoder_action_expandselection(clockwise);
            break;
        default:
            encoder_action_nexttab(clockwise);
    }
}
