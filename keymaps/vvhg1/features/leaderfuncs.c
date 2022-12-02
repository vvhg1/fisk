/* Copyright 2022 @vvhg1
 * Original author: @andrewjrae
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
#include "leaderfuncs.h"
#include "casemodes.h"
#ifdef ENCODER_ENABLE
#    include "encoder_utils.h"
#endif
#ifdef POWER_BRACKETS_ENABLE
#    include "power_brackets.h"
#endif
#include "keycodes.h"

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {

        case KC_A:
            tap_code16(LCTL(KC_F2));  //  Ctrl+F2 Select all occurrences of word VSCode
            return NULL;
       case KC_B:
            return vscode_stuff_brackets;
        case KC_E:
            tap_code16(LCTL(LSFT(KC_P)));  //  Ctrl+Shift+P Show command palette VSCode
            // tap_code16(KC_F1);             //  Ctrl+Shift+P Show command palette VSCode
            return NULL;
        case KC_F:
            return f_key_stuff; // Function keys
        case KC_G:
            tap_code16(C(S(KC_G)));  // open github sidebar
            tap_code((KC_G));
            return NULL;
        case KC_H:
            tap_code16(C(KC_K));  // show tool tip
            tap_code16(C(KC_I));
            return NULL;
        case KC_I:
            return operator_stuff; // Operators
#ifdef DYNAMIC_MACRO_ENABLE
        case KC_M:
            return macro_stuff;  // here m is the start for Macro related actions
#else
        case KC_M:
            tap_code16(KC_F20); // Mute
            return NULL;
#endif
        case KC_N:
            tap_code16(C(KC_PGUP));  //  n select editor left
            return vscode_stuff_no;
        case KC_O:
            tap_code16(C(KC_PGDN));  // i select editor right
            return vscode_stuff_no;
        case KC_Q:
            tap_code16(C(KC_F4));  // Q closes window
            return NULL;
        case KC_R:
            if (get_mods() & MOD_MASK_SHIFT) {  // run w/o debugging, with shift stop debugging
                tap_code(KC_F5);
            } else {
                tap_code16(C(KC_F5));
            }
            return NULL;
        case KC_T:
            tap_code16(LCTL(KC_GRV)); //  Ctrl+` Toggle terminal VSCode
            return NULL;
        case KC_U:
            return umlaut_stuff;  // here U is the start for Umlaut related actions
        case KC_V:
            return vscode_stuff;  // here V is the start for VSCode related actions
        case KC_W:
            return windows_stuff;  // here W is the start for Win related actions
        case KC_Z:
            tap_code16(LCTL(KC_K));  //  Ctrl+K,Z VSCode Zen Mode
            tap_code16(KC_Z);        //  Ctrl+K,Z VSCode Zen Mode
            return NULL;
        case KC_ENTER:
            // tap_code16(KC_ESC);  // escape
            tap_code16(LCTL(LSFT(KC_P)));  //  Ctrl+Shift+P Show command palette VSCode
            tap_code16(KC_F1);             //  Ctrl+Shift+P Show command palette VSCode
            return NULL;
        case KC_AT:
            send_string("victor.hobe.gelting@gmail.com");
            return NULL;

#ifdef CASEMODES_ENABLE
        case KC_C:
            toggle_caps_word();
            break;
        case KC_S:
            toggle_xcase();
            break;
        case KC_X:
            toggle_xcase();
            toggle_caps_word();
            break;
        // case KC_M:
        //     toggle_num_word();
        //     break;
        case KC_D:
            enable_xcase_with(MR_sft);
            break;
#endif
        case KC_LSHIFT:
        case KC_RSHIFT:
        case ML_sft:
        case MR_sft:
            return leader_start_func;  // escape mods
        default:
            return NULL;
    }
    return NULL;
}

void *operator_stuff(uint16_t keycode) {
    switch (keycode) {
        case KC_L: // larger or larger equal
            return operator_stuff_larger;
        case KC_S: // smaller or smaller equal
            return operator_stuff_smaller;
        case KC_N: // !=
            tap_code16(S(KC_1));
            tap_code16(KC_EQL);
            return NULL;
        case KC_E: // ==
            tap_code16(KC_EQL);
            tap_code16(KC_EQL);
            return NULL;
        case KC_O: // ||
            tap_code16(S(KC_BSLS));
            tap_code16(S(KC_BSLS));
            return NULL;
        case KC_A: // &&
            tap_code16(KC_AMPR);
            tap_code16(KC_AMPR);
            return NULL;
    }
    return NULL;
}
void *operator_stuff_larger(uint16_t keycode) {
    switch (keycode) {
        case KC_E: // >=
            tap_code16(S(KC_DOT));
            tap_code16(KC_EQL);
            return NULL;
        case KC_L: // >
            tap_code16(S(KC_DOT));
            return NULL;
    }
    return NULL;
}
void *operator_stuff_smaller(uint16_t keycode) {
    switch (keycode) {
        case KC_E: // <=
            tap_code16(S(KC_COMM));
            tap_code16(KC_EQL);
            return NULL;
        case KC_S: // <
            tap_code16(S(KC_COMM));
            return NULL;
    }
    return NULL;
}

void *umlaut_stuff(uint16_t keycode) {
    switch (keycode) {
        case KC_S:
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
            }
            if (is_windows) {
                // windows
                SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P2) SS_TAP(X_P2) SS_TAP(X_P3)));  // here S ß
            } else {
                // linux
                tap_code16(C(S(KC_U)));
                SEND_STRING("00DF");  // here S ß
                tap_code(KC_ENT);
            }
            break;
        case KC_A:
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                if (is_windows) {
                    // windows
                    SEND_STRING(SS_LALT(SS_TAP(X_P1) SS_TAP(X_P4) SS_TAP(X_P2)));  // here Ä
                } else {
                    // linux
                    tap_code16(C(S(KC_U)));
                    SEND_STRING("00C4");  // here Ä
                    tap_code(KC_ENT);
                }

            } else {
                if (is_windows) {
                    // windows
                    SEND_STRING(SS_LALT(SS_TAP(X_P1) SS_TAP(X_P3) SS_TAP(X_P2)));  // here ä
                } else {
                    // linux
                    tap_code16(C(S(KC_U)));
                    SEND_STRING("00E4");  // here ä
                    tap_code(KC_ENT);
                }
            }
            break;
        case KC_U:
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                if (is_windows) {
                    // windows
                    SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P2) SS_TAP(X_P2) SS_TAP(X_P0)));  // here U Ü
                } else {
                    // linux
                    tap_code16(C(S(KC_U)));
                    SEND_STRING("00DC");  // here U
                    tap_code(KC_ENT);
                }
            } else {
                if (is_windows) {
                    // windows
                    SEND_STRING(SS_LALT(SS_TAP(X_P1) SS_TAP(X_P2) SS_TAP(X_P9)));  //  here U Ü
                } else {
                    // linux
                    tap_code16(C(S(KC_U)));
                    SEND_STRING("00FC");  // here u
                    tap_code(KC_ENT);
                }
            }
            break;
        case KC_O:
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                if (is_windows) {
                    // windows
                    SEND_STRING(SS_LALT(SS_TAP(X_P0) SS_TAP(X_P2) SS_TAP(X_P1) SS_TAP(X_P4)));  // here O Ö
                } else {
                    // linux
                    tap_code16(C(S(KC_U)));
                    SEND_STRING("00D6");  // here O
                    tap_code(KC_ENT);
                }
            } else {
                if (is_windows) {
                    // windows
                    SEND_STRING(SS_LALT(SS_TAP(X_P1) SS_TAP(X_P4) SS_TAP(X_P8)));  // here O Ö
                } else {
                    // linux
                    tap_code16(C(S(KC_U)));
                    SEND_STRING("00F6");  // here o
                    tap_code(KC_ENT);
                }
            }
            break;
        case KC_LSHIFT:
        case KC_RSHIFT:
        case ML_sft:
        case MR_sft:
            return umlaut_stuff;

        default:
            return NULL;
    }
    return NULL;
}
#ifdef DYNAMIC_MACRO_ENABLE
void *macro_stuff(uint16_t keycode) {
    switch (keycode) {
        case KC_R:
            tap_code16(DM_REC1);  // here R record
            return NULL;
        case KC_S:
            tap_code16(DM_RSTP);  // here S stop recording
            return NULL;
        case KC_P:
            tap_code16(DM_PLY1);  // here P play recorded macro
            return NULL;
        default:
            return NULL;
    }
}
#endif
void *windows_stuff(uint16_t keycode) {
    switch (keycode) {  // here WS is Start menu, WM is context menu
        case KC_S:
            tap_code(KC_LGUI);  // here WS is Start menu, WM is context menu
            return NULL;
        case KC_M:
            tap_code(KC_APP);  // here WS is Start menu, WM is context menu
            return NULL;
        case KC_Q:
            tap_code16(C(KC_F4));  // here WQ closes window
            return windows_stuff;
        default:
            return NULL;
    }
}
void *vscode_stuff(uint16_t keycode) {
    switch (keycode) {
        case KC_M:
            return vscode_stuff_m;
        case KC_F:
            return vscode_stuff_f;
        case KC_A:
            return vscode_stuff_a;
        case KC_P:
            tap_code16(LCTL(KC_K));  // format selection
            tap_code16(LCTL(KC_F));  // format selection
            return vscode_stuff_p;

        default:
            return NULL;
    }
}
void *vscode_stuff_brackets(uint16_t keycode){
switch (keycode) {
        case KC_G:
            tap_code16(C(S(KC_BSLS)));  //  vg
            return NULL;
        case KC_S:
            tap_code16(KC_END);  //  vs
            tap_code16(KC_HOME);  //  vs
            tap_code16(KC_HOME);  //  vs
            tap_code16(LSA(KC_RIGHT));
            return NULL;
        case KC_D:
            tap_code16(KC_END);  //  vs
            tap_code16(KC_HOME);  //  vs
            tap_code16(KC_HOME);  //  vs
            tap_code16(LSA(KC_RIGHT));
            tap_code16(KC_DEL);  //  vs
            return NULL;
        default:
            return NULL;
    }
}
void *vscode_stuff_no(uint16_t keycode) {
    switch (keycode) {
        case KC_N:
            tap_code16(C(KC_PGUP));  //  vi left
            return vscode_stuff_no;
        case KC_O:
            tap_code16(C(KC_PGDN));  // vn select editor right
            return vscode_stuff_no;

        default:
            return NULL;
    }
}
void *vscode_stuff_a(uint16_t keycode) {
    switch (keycode) {
        case KC_P:
            tap_code16(LSA(KC_F));  // format document
            return NULL;
        default:
            return NULL;
    }
}
void *vscode_stuff_p(uint16_t keycode) {
    switch (keycode) {
        case KC_P:
            tap_code16(LCTL(KC_K));  // format selection
            tap_code16(LCTL(KC_F));  // format selection
            return vscode_stuff_p;
        default:
            return NULL;
    }
}
void *vscode_stuff_m(uint16_t keycode) {
    switch (keycode) {
        case KC_N:
            tap_code16(LCA(KC_LEFT));  // vmn editor left
            return vscode_stuff_m;
        case KC_O:
            tap_code16(LCA(KC_RIGHT));  //  vmi right
            return vscode_stuff_m;
        default:
            return NULL;
    }
}
void *vscode_stuff_f(uint16_t keycode) {
    switch (keycode) {
        case KC_N:
            tap_code16(LCTL(KC_K));  // vfn focus left
            tap_code16(LCTL(KC_LEFT));
            return vscode_stuff_f;
        case KC_O:
            tap_code16(LCTL(KC_K));  //  vfo focus right
            tap_code16(LCTL(KC_RIGHT));
            return vscode_stuff_f;
        default:
            return NULL;
    }
}
void *f_key_stuff(uint16_t keycode) {
    switch (keycode) {
        case KC_N:
            tap_code(KC_F1);  // here F1
            return f_key_stuff;
        case KC_E:
            tap_code(KC_F2);  // here F2
            return f_key_stuff;
        case KC_I:  // here F3
            tap_code(KC_F3);
            return f_key_stuff;
        case KC_H:
            tap_code(KC_F4);  // here F4
            return f_key_stuff;
        case KC_COMM:
            tap_code(KC_F5);  // here F5
            return f_key_stuff;
        case KC_DOT:
            tap_code(KC_F6);  // here F6
            return f_key_stuff;
        case KC_L:
            tap_code(KC_F7);  // here F7
            return f_key_stuff;
        case KC_U:
            tap_code(KC_F8);  // here F8
            return f_key_stuff;
        case KC_Y:
            tap_code(KC_F9);  // here F9
            return f_key_stuff;
        case KC_M:
            tap_code(KC_F10);  // here F10
            return f_key_stuff;
        case KC_O:
            tap_code(KC_F11);  // here F11
            return f_key_stuff;
        default:
            return NULL;
    }
}
/* #ifdef ENCODER_ENABLE
void *encoder_stuff(uint16_t keycode) {  // e+  h horizontal scroll / v vertical scroll / e editor / t tab / p paging
    switch (keycode) {
        case KC_H:
            set_encoder_mode(ENC_MODE_LEFT_RIGHT);
            break;
        case KC_V:
            set_encoder_mode(ENC_MODE_UP_DOWN);
            break;
        case KC_E:
            set_encoder_mode(ENC_MODE_NEXTEDITOR);
            break;
        case KC_T:
            set_encoder_mode(ENC_MODE_NEXTTAB);
            break;
        case KC_P:
            set_encoder_mode(ENC_MODE_PAGING);
            break;
        case KC_W:
            set_encoder_mode(ENC_MODE_WORD_NAV);
            break;
        default:
            return NULL;
    }
    return NULL;
}
#endif
 */
