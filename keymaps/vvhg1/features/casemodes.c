/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae, NumWord by Joshua T., adaption by 2022 @vvhg1
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

#include "casemodes.h"
#include "enumlayers.h"
#include "keycodes.h"

/* The caps word concept started with @iaap on splitkb.com discord.
 * However it has been implemented and extended by many splitkb.com users:
 * - @theol0403 made many improvements to initial implementation
 * - @precondition used caps lock rather than shifting
 * - @dnaq his own implementation which also used caps lock
 * - @sevanteri added underscores on spaces
 * - @metheon extended on @sevanteri's work and added specific modes for
 *   snake_case and SCREAMING_SNAKE_CASE
 * - @baffalop came up with the idea for xcase, which he implements in his own
 *   repo, however this is implemented by @iaap with support also for one-shot-shift.
 * - @sevanteri
 *     - fixed xcase waiting mode to allow more modified keys and keys from other layers.
 *     - Added @baffalop's separator defaulting on first keypress, with a
 *       configurable default separator and overrideable function to determine
 *       if the default should be used.
 *
 *  - @vvhg1
 *      - included adaption of NumWord by Joshua T.
 *      - added toggle for xcase
 *      - works with custom one shot mods
 *      - changed code a little, working more with switch statements
 *      - set default to shift, making caps the option, (changed termination behaviour in respect to shift modifier)
 */

#ifndef DEFAULT_XCASE_SEPARATOR
#    define DEFAULT_XCASE_SEPARATOR KC_UNDS
#endif

#define IS_OSM(keycode) (keycode >= QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX)

// bool to keep track of the caps word state
static bool caps_word_on = false;
// bool to keep track of the num word state
static bool num_word_on = false;

// enum to keep track of the xcase state
static enum xcase_state xcase_state = XCASE_OFF;
// the keycode of the xcase delimiter
static uint16_t xcase_delimiter;
// the number of keys to the last delimiter
static int8_t distance_to_last_delim = -1;

// Check whether caps word is on
bool caps_word_enabled(void) { return caps_word_on; }
bool x_case_enabled(void) {
    if (xcase_state != XCASE_OFF) {
        return true;
    } else {
        return false;
    }
}
bool num_word_enabled(void) { return num_word_on; }

// Enable caps word
void enable_caps_word(void) {
    caps_word_on = true;
#ifdef CAPSWORD_USE_CAPS
    if (!host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
#endif
}

// Disable caps word
void disable_caps_word(void) {
    caps_word_on = false;
#ifdef CAPSWORD_USE_CAPS
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
#else
    unregister_mods(MOD_LSFT);
#endif
}

// Toggle caps word
void toggle_caps_word(void) {
    if (caps_word_on) {
        disable_caps_word();
    } else {
        enable_caps_word();
    }
}

// Toggle xcase
void toggle_xcase(void) {
    if ((xcase_state == XCASE_ON) || (xcase_state == XCASE_WAIT)) {
        disable_xcase();
    } else {
        enable_xcase();
    }
}
// Get xcase state
enum xcase_state get_xcase_state(void) { return xcase_state; }

// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void) { xcase_state = XCASE_WAIT; }

// Enable xcase with the specified delimiter
void enable_xcase_with(uint16_t delimiter) {
    xcase_state            = XCASE_ON;
    xcase_delimiter        = delimiter;
    distance_to_last_delim = -1;
}

// Disable xcase
void disable_xcase(void) { xcase_state = XCASE_OFF; }

// Place the current xcase delimiter
static void place_delimiter(void) {
#ifndef NO_ACTION_TAPPING
    if (IS_OSM(xcase_delimiter)) {
        // apparently set_oneshot_mods() is dumb and doesn't deal with handedness for you
        uint8_t mods = xcase_delimiter & 0x10 ? (xcase_delimiter & 0x0F) << 4 : xcase_delimiter & 0xFF;
        set_oneshot_mods(mods);
    } else {
#endif
        tap_code16(xcase_delimiter);
#ifndef NO_ACTION_TAPPING
    }
#endif
}

// Removes a delimiter, used for double tap space exit
static void remove_delimiter(void) {
#ifndef NO_ACTION_TAPPING
    if (IS_OSM(xcase_delimiter)) {
        clear_oneshot_mods();
    } else {
        tap_code(KC_BSPC);
    }
#else
    if(xcase_delimiter == MR_sft){
        return;
    }tap_code(KC_BSPC);
#endif
}

void enable_num_word(void) {
    if (num_word_on) return;
    num_word_on = true;
    layer_on(_NUM);
}

void disable_num_word(void) {
    if (!num_word_on) return;
    num_word_on = false;
    layer_off(_NUM);
}

void toggle_num_word(void) {
    if (num_word_on) {
        disable_num_word();
    } else {
        enable_num_word();
    }
}

// overrideable function to determine whether the case mode should stop
__attribute__((weak)) bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    if (caps_word_on && (xcase_state != XCASE_WAIT)) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_UNDS:
            case KC_BSPC:
            case ML_sft:
            case MR_sft:
                break;
            default:
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
    } else if (xcase_state == XCASE_WAIT) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_UNDS:
            case KC_BSPC:
            case KC_LSHIFT:
            case KC_RSHIFT:
            case KC_LALT:
            case KC_RALT:
                return false;
            default:
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
    } else if (num_word_on) {
        switch (keycode) {
            // Keycodes which should not disable num word mode.
            // We could probably be more brief with these definitions by using
            // a couple more ranges, but I believe "explicit is better than
            // implicit"
            case KC_1 ... KC_0:
            case KC_EQL:
            case KC_SCLN:
            case KC_MINS:
            case KC_DOT:

            // Numpad keycodes
            case KC_P1 ... KC_P0:
            case KC_PSLS ... KC_PPLS:
            case KC_PDOT:

            // Misc
            case KC_UNDS:
            case KC_BSPC:
            case KC_DEL:
                return false;

            default:
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
        return false;
    }
    return false;
}

/* overrideable function to determine whether to use the default separator on
 * first keypress when waiting for the separator. */
__attribute__((weak)) bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        case KC_A ... KC_Z:
            return true;
        case KC_1 ... KC_0:
            if (get_mods() & MOD_MASK_SHIFT) {
                return false;
            }
            return true;
        case KC_SPC:
            return true;
        default:
            return false;
    }
    return false;
}

bool process_case_modes(uint16_t keycode, const keyrecord_t *record) {
    if (caps_word_on || xcase_state) {
        if ((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX) || (QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) {
            // Earlier return if this has not been considered tapped yet
#ifndef NO_ACTION_TAPPING
            if (record->tap.count == 0) return true;
#endif
            keycode = keycode & 0xFF;
        }

        if (keycode >= QK_LAYER_TAP && keycode <= QK_ONE_SHOT_LAYER_MAX) {
            // let special keys and normal modifiers go through
            return true;
        }

        if (xcase_state == XCASE_WAIT) {
            // grab the next input to be the delimiter
            if ((use_default_xcase_separator(keycode, record)) && (record->event.pressed)) {
                enable_xcase_with(DEFAULT_XCASE_SEPARATOR);  //-------------------------------------------------------could be set based on last separator
            } else if (record->event.pressed) {
                switch (keycode) {
                    case KC_LSHIFT:
                    case KC_RSHIFT:
                    case KC_LALT:
                    case KC_RALT:
                    case ML_sft:
                    case MR_sft:
                    case ML_alt:
                    case go_NUM:
                    case mo_NUM:
                        return true;

                    default:
                        // factor in mods
                        if (get_mods() & MOD_MASK_SHIFT) {
                            keycode = LSFT(keycode);
                        } else if (get_mods() & MOD_BIT(KC_RALT)) {
                            keycode = RALT(keycode);
                        } else if (get_mods() & MOD_BIT(KC_LALT)) {
                            keycode = LALT(keycode);
                        }
                        enable_xcase_with(keycode);
                        return false;
                }
            } else {
#ifndef NO_ACTION_TAPPING
                if (IS_OSM(keycode)) {
                    // this catches the OSM release if no other key was pressed
                    set_oneshot_mods(0);
                    enable_xcase_with(keycode);
                    return false;
                }
#endif
                // let other special keys go through
                return true;
            }
        }

        if (record->event.pressed) {
            // handle xcase mode
            if (xcase_state == XCASE_ON) {
                // place the delimiter if space is tapped
                switch (keycode) {
                    case KC_SPC:
                        if (distance_to_last_delim != 0) {
                            place_delimiter();
                            distance_to_last_delim = 0;
                            return false;
                        }
                        // remove the delimiter and disable modes
                        else {
                            disable_xcase();
                            disable_caps_word();
                            disable_num_word();
                            remove_delimiter();

                            return true;
                        }
                        break;
                    case KC_ESC: {
                        disable_xcase();
                        disable_caps_word();
                        disable_num_word();
                        return true;
                    } break;
                    // decrement distance to delimiter on back space
                    case KC_BSPC:
                        --distance_to_last_delim;
                        break;
                    // don't increment distance to last delim if negative
                    default:
                        if (distance_to_last_delim >= 0) {
                            // puts back a one shot delimiter if you we're back to the delimiter pos
                            if (distance_to_last_delim == 0 && ((IS_OSM(xcase_delimiter))||(xcase_delimiter == MR_sft))) {
                                tap_code16(LSFT(keycode));
                            ++distance_to_last_delim;
                            return false;
                            }
                            ++distance_to_last_delim;
                        }
                        break;
                }
            }  // end XCASE_ON
            if (caps_word_on) {
                // check if the case modes have been terminated
                if (terminate_case_modes(keycode, record)) {
                    disable_caps_word();
                    disable_xcase();
                    disable_num_word();
                }
#ifndef CAPSWORD_USE_CAPS
                else {
                    switch (keycode) {
                        // Letter keys should be shifted.
                        case KC_A ... KC_Z:
                            tap_code16(LSFT(keycode));
                            return false;
                        default:
                            return true;
                    }
                }
#endif
            }
        }
    }
    if (num_word_on) {
        if (record->event.pressed) {
            // Get the base keycode of a mod or layer tap key
            switch (keycode) {
                case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
#ifndef NO_ACTION_TAPPING
                    // Earlier return if this has not been considered tapped yet
                    if (record->tap.count == 0) return true;
#endif
                    keycode = keycode & 0xFF;
                    break;
                default:
                    break;
            }
            // check if the case modes have been terminated
            if (terminate_case_modes(keycode, record)) {
                disable_caps_word();
                disable_xcase();
                disable_num_word();
            }

            return true;
        }
        return true;
    }
    return true;
}
