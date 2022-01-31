/* Copyright 2022 @vvhg1 and original by 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
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
 *
 *  - @vvhg1 changed leader key to toggle on off,
 *  - shortened display string and made it scroll when it gets too long,
 *    as I don't use space in my leader sequences, I deleted that bit.
 */

#include "leader.h"
#include "keycodes.h"
#include <string.h>

#ifndef LEADER_ESC_KEY
#define LEADER_ESC_KEY KC_ESC
#endif

static bool leading = false;
static leader_func_t leader_func = NULL;

#ifdef LEADER_DISPLAY_STR

#ifndef LEADER_DISPLAY_LEN
#define LEADER_DISPLAY_LEN 7 //change this value to display a longer or shorter string
#endif

static const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};
static uint8_t    leader_display_size;
// static const char space_ascii[] = "SPC";
static char leader_display[LEADER_DISPLAY_LEN + 1];  // add space for null terminator

static void update_leader_display(uint16_t keycode) {
    if (leader_display_size < LEADER_DISPLAY_LEN - 2) {
        ++leader_display_size;
        leader_display[leader_display_size] = '-';
        ++leader_display_size;
        if (keycode < sizeof(keycode_to_ascii_lut)) {
            leader_display[leader_display_size] = keycode_to_ascii_lut[keycode];
        } else {
            leader_display[leader_display_size] = '?';
        }
    } else {
        memcpy(leader_display, (leader_display + 2), (sizeof(leader_display) - 2));
        leader_display[leader_display_size - 1] = '-';
        if (keycode < sizeof(keycode_to_ascii_lut)) {
            leader_display[leader_display_size] = keycode_to_ascii_lut[keycode];
        } else {
            leader_display[leader_display_size] = '?';
        }
    }
}

char *leader_display_str(void) { return leader_display; }
#endif

// The entry point for leader sequenc functions
__attribute__((weak)) void *leader_start_func(uint16_t keycode) { return NULL; }

// Check to see if we are leading
bool is_leading(void) { return leading; }
// Start leader sequence
void start_leading(void) {
    if (is_leading()) {
        stop_leading();
        return;
    }
    leading     = true;
    leader_func = leader_start_func;
#ifdef LEADER_DISPLAY_STR
    memset(leader_display, 0, sizeof(leader_display));
    leader_display[0]   = 'L';
    leader_display[1]   = '-';
    leader_display_size = 1;
#endif
}
// Stop leader sequence
void stop_leading(void) {
    leading     = false;
    leader_func = NULL;
#ifdef LEADER_DISPLAY_STR
    leader_display[leader_display_size] = ' ';
#endif
}

// Process keycode for leader sequences
bool process_leader(uint16_t keycode, const keyrecord_t *record) {
    if (leading) {
#ifndef NO_ACTION_TAPPING
        // Get the base keycode of a mod or layer tap key
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) return true;
                keycode = keycode & 0xFF;
                break;
            default:
                break;
        }
#endif
        // let through anything above that's normal keyboard keycode or a mod
        if (keycode > QK_MODS_MAX || IS_MOD(keycode)) {
            switch (keycode) {
                // special keycodes used in leader funcs
                case Op_Br:
                case Sq_Br:
                case Cr_Br:
                    break;
                case LEADER_ESC_KEY:
                    // early exit if the esc key was hit
                    if (record->event.pressed) {
                        stop_leading();
                    }
                    return false;
                default:
                    return true;
            }
        }
        if (record->event.pressed) {
#ifdef LEADER_DISPLAY_STR
            update_leader_display(keycode);
#endif
            // update the leader function
            leader_func = leader_func(keycode);
            if (leader_func == NULL) {
                stop_leading();
            }
        }
        return false;
    }
    return true;
}
