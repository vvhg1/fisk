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

#include "oled_utils.h"
#include "keycodes.h"
#ifdef CUSTOM_LEADER_ENABLE
#    include "leader.h"
#endif

#ifdef CASEMODES_ENABLE
#    include "features/casemodes.h"
#endif

#ifdef EE_HANDS
#    include "eeprom.h"
#    include "eeconfig.h"
#endif

bool is_keyboard_left(void) {
#ifdef IS_LEFT
    return true;
#else
    return false;
#endif
    // #ifdef EE_HANDS
    //     return eeprom_read_byte(EECONFIG_HANDEDNESS);
    // #endif
}

//! this is the complete code from ai03, Website: [ai03 Keyboard Designs](https://kb.ai03.me/)
// __attribute__((weak))
// bool is_keyboard_left(void) {
//   #ifdef SPLIT_HAND_PIN
//     // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
//     setPinInput(SPLIT_HAND_PIN);
//     return readPin(SPLIT_HAND_PIN);
//   #else
//     #ifdef EE_HANDS
//       return eeprom_read_byte(EECONFIG_HANDEDNESS);
//     #else
//       #ifdef MASTER_RIGHT
//         return !is_keyboard_master();
//       #else
//         return is_keyboard_master();
//       #endif
//     #endif
//   #endif
// }
#ifndef CONSOLE_ENABLE
void render_fisk_logo(int line, bool newline) {
    static const char PROGMEM fisk_logo1[] = {0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0x00};
    static const char PROGMEM fisk_logo2[] = {0xD8, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0x00};
    static const char PROGMEM fisk_logo3[] = {0x20, 0x20, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0x00};
    static const char PROGMEM fisk_logo4[] = {0x20, 0x20, 0x20, 0x20, 0x92, 0x93, 0x94, 0x95, 0x96, 0x00};
    static const char PROGMEM new_line[]   = {0x0D, 0x00};

    switch (line) {
        case 1:
            oled_write_P(fisk_logo1, false);
            break;
        case 2:
            oled_write_P(fisk_logo2, false);
            break;
        case 3:
            oled_write_P(fisk_logo3, false);
            break;
        case 4:
            oled_write_P(fisk_logo4, false);
            break;
        default:
            break;
    }
    if (newline) {
        oled_write_P(new_line, false);
    }
}
void render_logo_l(void) {
    render_fisk_logo(1, true);
    render_fisk_logo(2, false);
    oled_write_P(PSTR(" fisk v2.0\n"), false);
    render_fisk_logo(3, true);
    render_fisk_logo(4, false);
}
void render_logo_r(void) {
    oled_write_P(PSTR("      fisk v2.0\n    Powered by QMK"), false);
}
#    ifdef CUSTOM_LEADER_ENABLE
static const char mod_display1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x90, 0x91, 0x92, 0x93, 0x0D, 0x20, 0x20, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xB0, 0xB1, 0xB2, 0xB3, 0x0D, 0x20, 0x20, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xD0, 0xD1, 0xD2, 0xD3, 0};
#    else
static const char mod_display1[] = {0x20, 0x20, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x20, 0x20, 0x0D, 0x20, 0x20, 0x20, 0x20, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0x20, 0x20, 0x0D, 0x20, 0x20, 0x20, 0x20, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0x20, 0x20, 0};
#    endif
static char mod_display11[55];

void reset_mod_display(void) {
    memcpy(mod_display11, mod_display1, 55);
}
void write_oled(void) {
    oled_set_cursor(2, 0);
    oled_write_ln(mod_display11, false);
}
void set_mod_display(const char string_part1[], const char string_part2[], const char string_part3[], int idx) {
#    ifdef CUSTOM_LEADER_ENABLE
    memcpy(mod_display11 + idx, string_part1, 4);
    memcpy(mod_display11 + (idx + 19), string_part2, 4);
    memcpy(mod_display11 + (idx + 38), string_part3, 4);
#    else
    memcpy(mod_display11 + (idx + 2), string_part1, 4);
    memcpy(mod_display11 + (idx + 21), string_part2, 4);
    memcpy(mod_display11 + (idx + 40), string_part3, 4);

#    endif
}
void render_mod_status(uint8_t modifiers) {
    static const char ctrl_on1[]  = {0x8C, 0x8D, 0x8E, 0x8F};
    static const char ctrl_on2[]  = {0xAC, 0xAD, 0xAE, 0xAF};
    static const char ctrl_on3[]  = {0xCC, 0xCD, 0xCE, 0xCF};
    static const char shift_on1[] = {0x98, 0x99, 0x9A, 0x9B};
    static const char shift_on2[] = {0xB8, 0xB9, 0xBA, 0xBB};
    static const char shift_on3[] = {0xD8, 0xD9, 0xDA, 0xDB};
    static const char alt_on1[]   = {0x9C, 0x9D, 0x9E, 0x9F};
    static const char alt_on2[]   = {0xBC, 0xBD, 0xBE, 0xBF};
    static const char alt_on3[]   = {0xDC, 0xDD, 0xDE, 0xDF};
#    ifdef CUSTOM_LEADER_ENABLE
    static const char lead_on1[] = {0x94, 0x95, 0x96, 0x97};
    static const char lead_on2[] = {0xB4, 0xB5, 0xB6, 0xB7};
    static const char lead_on3[] = {0xD4, 0xD5, 0xD6, 0xD7};
#    endif
    reset_mod_display();
    if ((modifiers & MOD_MASK_CTRL)) {
        set_mod_display(ctrl_on1, ctrl_on2, ctrl_on3, 0);
    }
    if ((modifiers & MOD_MASK_SHIFT)) {
        set_mod_display(shift_on1, shift_on2, shift_on3, 4);
    }
    if ((modifiers & MOD_MASK_ALT)) {
        set_mod_display(alt_on1, alt_on2, alt_on3, 8);
    }
#    ifdef CUSTOM_LEADER_ENABLE
    if (is_leading()) {
        set_mod_display(lead_on1, lead_on2, lead_on3, 12);
    }
#    endif
    write_oled();
}
#endif

#ifdef CONSOLE_ENABLE
void render_mod_status(uint8_t modifiers) {
    if (get_mods() & MOD_MASK_SHIFT) {
        oled_write_P(PSTR("SHIFT "), false);
    }
    if (get_mods() & MOD_MASK_CTRL) {
        oled_write_P(PSTR("CTRL "), false);
    }
    if (get_mods() & MOD_MASK_ALT) {
        oled_write_P(PSTR("ALT "), false);
    }
    if (is_leading()) {
        oled_write_P(PSTR("LDR "), false);
    }
}
#endif
#ifdef CONSOLE_ENABLE
void render_layer(void) {
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("COLEMAK\n"), false);
            break;
        case _QW:
            oled_write_P(PSTR("Qwerty\n"), false);
            break;
#    ifdef SWAP_HANDS_ENABLE
        case _MIR:
            oled_write_P(PSTR("Mirror\n"), false);
            break;
#    endif
        case _NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Num\n"), false);
            break;
        case _FUNX:
            oled_write_P(PSTR("Func\n"), false);
            break;
        case _AUX:
            oled_write_P(PSTR("Aux\n"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}
#endif
#ifdef CASEMODES_ENABLE
void render_case_modes(void) {
    if (caps_word_enabled()) {
        if (x_case_enabled()) {
            oled_write_P(PSTR(" X"), false);
        } else {
            oled_write_P(PSTR(" C"), false);
        }
    } else if (x_case_enabled()) {
        if (num_word_enabled()) {
            oled_write_P(PSTR(" SN"), false);
        } else {
            oled_write_P(PSTR(" S"), false);
        }
    } else if (num_word_enabled()) {
        oled_write_P(PSTR(" N"), false);
    }
}
#endif
#ifndef CONSOLE_ENABLE
void render_layer(void) {
    static const char PROGMEM COMMON1[]   = {0x20, 0x20, 0x20, 0x8D, 0x00};
    static const char PROGMEM COMMON2[]   = {0x20, 0x20, 0xAC, 0x00};
    static const char PROGMEM COMMON3[]   = {0x20, 0x20, 0xCC, 0x00};
    static const char PROGMEM COMMON4[]   = {0x20, 0x20, 0x20, 0x20, 0x80, 0x81, 0x00};
    static const char PROGMEM BASE1[]     = {0xA0, 0xA2, 0x88, 0x91, 0x00};
    static const char PROGMEM QW2[]       = {0xB3, 0xB4, 0xB5, 0xA1, 0xB7, 0xB2, 0x00};
    static const char PROGMEM QW3[]       = {0xD3, 0xD4, 0xC0, 0xC1, 0xD7, 0xD2, 0x00};
    static const char PROGMEM QW4[]       = {0x82, 0x00};
    static const char PROGMEM NAV1[]      = {0x84, 0x85, 0x86, 0x91, 0x00};
    static const char PROGMEM NAV2[]      = {0xAD, 0xA4, 0xA5, 0xA6, 0xB1, 0xB2, 0x00};
    static const char PROGMEM NAV_QW3[]   = {0xCD, 0xCE, 0xC3, 0xC8, 0xD1, 0xD2, 0x00};
    static const char PROGMEM NUM1[]      = {0x8E, 0x8F, 0x90, 0x91, 0x00};
    static const char PROGMEM NUM2[]      = {0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0x00};
    static const char PROGMEM NUM_QW3[]   = {0xCD, 0xCE, 0xC2, 0xC6, 0xD1, 0xD2, 0x00};
    static const char PROGMEM FUNX1[]     = {0x8E, 0x87, 0x88, 0x91, 0x00};
    static const char PROGMEM FUNX2[]     = {0xAD, 0xA4, 0xA7, 0x20, 0xB1, 0xB2, 0x00};
    static const char PROGMEM FUNX_QW3[]  = {0xCD, 0xCE, 0xC3, 0xC8, 0xD1, 0xD2, 0x00};
    static const char PROGMEM AUX1[]      = {0x89, 0x8A, 0x8B, 0x91, 0x00};
    static const char PROGMEM AUX2[]      = {0xAD, 0xA9, 0xAA, 0xAB, 0xB1, 0xB2, 0x00};
    static const char PROGMEM AUX_QW3[]   = {0xCD, 0xC9, 0xC2, 0x8C, 0xD1, 0xD2, 0x00};
    static const char PROGMEM EMPTY1[]    = {0xA0, 0x85, 0x88, 0x91, 0x00};
    static const char PROGMEM EMPTY2[]    = {0xAD, 0x20, 0x20, 0x20, 0xB1, 0xB2, 0x00};
    static const char PROGMEM BRACKETS2[] = {0xAD, 0x42, 0x52, 0x43, 0xB1, 0xB2, 0x00};
    static const char PROGMEM MOUSE2[]    = {0xAD, 0x52, 0x41, 0x54, 0xB1, 0xB2, 0x00};
    // static const char PROGMEM EMPTY_QW3[]   = {0xCD, 0xA8, 0xC3, 0xC8, 0xD1, 0xD2, 0x00};
    static const char PROGMEM COLE2[]       = {0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB2, 0x00};
    static const char PROGMEM COLE3[]       = {0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD2, 0x00};
    static const char PROGMEM COLE4[]       = {0x83, 0x00};
    static const char PROGMEM NAV_COLE3[]   = {0xCD, 0xCE, 0xC5, 0xD0, 0xD1, 0xD2, 0x00};
    static const char PROGMEM NUM_COLE3[]   = {0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0x00};
    static const char PROGMEM FUNX_COLE3[]  = {0xCD, 0xCE, 0xC5, 0xC7, 0xD1, 0xD2, 0x00};
    static const char PROGMEM AUX_COLE3[]   = {0xCD, 0xC9, 0xCA, 0xCB, 0xD1, 0xD2, 0x00};
    static const char PROGMEM EMPTY_COLE3[] = {0xCD, 0xA8, 0xC5, 0xC7, 0xD1, 0xD2, 0x00};
    static const char PROGMEM NEW_LINE[]    = {0x0D, 0x00};

#    ifndef CONSOLE_ENABLE
    render_fisk_logo(1, false);
#    endif
    oled_write_P(COMMON1, false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
        case _QW:
#    ifdef SWAP_HANDS_ENABLE
        case _MIR:
#    endif
            oled_write_P(BASE1, false);
            break;
        case _NAV:
            oled_write_P(NAV1, false);
            break;
        case _NUM:
            oled_write_P(NUM1, false);
            break;
        case _FUNX:
            oled_write_P(FUNX1, false);
            break;
        case _AUX:
            oled_write_P(AUX1, false);
            break;
        default:
            oled_write_P(EMPTY1, false);
            break;
    }
    oled_write_P(NEW_LINE, false);
#    ifndef CONSOLE_ENABLE
    render_fisk_logo(2, false);
#    endif
    oled_write_P(COMMON2, false);
    switch (get_highest_layer(layer_state)) {
#    ifdef SWAP_HANDS_ENABLE
        case _MIR:
            switch (get_highest_layer(default_layer_state)) {
                case _QW:
                    oled_write_P(QW2, false);
                    break;
                case _COLEMAK:
                    oled_write_P(COLE2, false);
                    break;
            }
            break;
#    endif
        case _COLEMAK:
            oled_write_P(COLE2, false);
            break;
        case _QW:
            oled_write_P(QW2, false);
            break;
        case _NAV:
            oled_write_P(NAV2, false);
            break;
        case _NUM:
            oled_write_P(NUM2, false);
            break;
        case _FUNX:
            oled_write_P(FUNX2, false);
            break;
        case _AUX:
            oled_write_P(AUX2, false);
            break;
        case _BRACKETS:
            oled_write_P(BRACKETS2, false);
            break;
        case _MOUSE:
            oled_write_P(MOUSE2, false);
            break;
        default:
            oled_write_P(EMPTY2, false);
            break;
    }
    oled_write_P(NEW_LINE, false);
#    ifndef CONSOLE_ENABLE
    render_fisk_logo(3, false);
#    endif
    oled_write_P(COMMON3, false);
    switch (get_highest_layer(default_layer_state)) {
        case _QW:
            switch (get_highest_layer(layer_state)) {
                case _QW:
#    ifdef SWAP_HANDS_ENABLE
                case _MIR:
#    endif
                    oled_write_P(QW3, false);
                    break;
                case _NAV:
                    oled_write_P(NAV_QW3, false);
                    break;
                case _NUM:
                    oled_write_P(NUM_QW3, false);
                    break;
                case _FUNX:
                    oled_write_P(FUNX_QW3, false);
                    break;
                case _AUX:
                    oled_write_P(AUX_QW3, false);
                    break;
                default:
                    oled_write_P(QW3, false); // EMPTY_QW3, false);
                    break;
            }
            oled_write_P(NEW_LINE, false);
#    ifndef CONSOLE_ENABLE
            render_fisk_logo(4, false);
#    endif
            oled_write_P(COMMON4, false);
            oled_write_P(QW4, false);
            break;
        case _COLEMAK:
            switch (get_highest_layer(layer_state)) {
#    ifdef SWAP_HANDS_ENABLE
                case _MIR:
#    endif
                case _COLEMAK:
                    oled_write_P(COLE3, false);
                    break;
                case _NAV:
                    oled_write_P(NAV_COLE3, false);
                    break;
                case _NUM:
                    oled_write_P(NUM_COLE3, false);
                    break;
                case _FUNX:
                    oled_write_P(FUNX_COLE3, false);
                    break;
                case _AUX:
                    oled_write_P(AUX_COLE3, false);
                    break;
                default:
                    oled_write_P(EMPTY_COLE3, false);
                    break;
            }

            oled_write_P(NEW_LINE, false);
#    ifndef CONSOLE_ENABLE
            render_fisk_logo(4, false);
#    endif
            oled_write_P(COMMON4, false);
            oled_write_P(COLE4, false);
            break;
    }
}
#endif

#ifdef ENCODER_ENABLE
void render_encoder(encoder_mode_t mode) {
#    ifdef CUSTOM_LEADER_ENABLE
    if (is_leading()) {
        oled_set_cursor(0, 3);
    } else {
        oled_set_cursor(4, 3);
    }
#    else
    oled_set_cursor(4, 3);
#    endif
    switch (mode) {
        // case ENC_MODE_WORD_NAV:
        //     oled_write_P(PSTR(" \x0B\x0E WORD \x7F\x02 "), false);
        //     break;
        // case ENC_MODE_LEFT_RIGHT:
        //     oled_write_P(PSTR("   \x0B\x0B\x0E\x7F\x02\x02 "), false);
        //     break;
        // case ENC_MODE_UP_DOWN:
        //     oled_write_P(PSTR("  \x1E\x1F" " U D " "\x1C\x1D "), false);
        //     break;
        // case ENC_MODE_PAGING:
        //     oled_write_P(PSTR("   \x1E\x1F" " PG " "\x1C\x1D "), false);
        //     break;
        // case ENC_MODE_NEXTEDITOR:
        //     oled_write_P(PSTR("\x0B\x0E EDITOR \x7F\x02 "), false);
        //     break;
        case ENC_MODE_NEXTTAB:
            oled_write_P(PSTR("  \x0B\x0E TAB \x7F\x02 "), false);
            break;
        // case ENC_MODE_EXPAND_SELECTION:
        //     oled_write_P(PSTR("  \x1E\x1F" " SEL " "\x1C\x1D "), false);
        //     break;
        case ENC_MODE_CODE_CHANGES:
            oled_write_P(PSTR("  \x1E\x1F"
                              " CHG "
                              "\x1C\x1D "),
                         false);
            break;
        default:
            oled_write_P(PSTR("??? "), false);
    }
}
#endif

void render_status(void) {
#ifdef SWAP_HANDS_ENABLE
    if (IS_LAYER_ON(_MIR)) {
        oled_invert(true);
    } else {
        oled_invert(false);
    }
#endif
    if (is_keyboard_left()) {
        render_layer();
#ifdef CASEMODES_ENABLE
        render_case_modes();
#endif
        oled_set_cursor(20, 0);
        oled_write_P(is_windows ? PSTR("W") : PSTR("L"), false);
    } else {
        render_mod_status(get_mods());
#ifdef ENCODER_ENABLE
        render_encoder(get_encoder_mode());
#endif
#ifdef CUSTOM_LEADER_ENABLE
#    ifdef LEADER_DISPLAY_STR
        if (is_leading()) {
            oled_write_ln(leader_display_str(), false);
        }
#    endif
#endif
    }
}
