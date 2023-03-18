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
 * This is intended as a cheap workaround to save space by defining NO_ACTION_TAPPING or NO_ACTION_ONESHOT and still use some oneshot functionality
 * more modifiers can be added easily, but I want to keep it as lightweight as I can for my use.
 */
#include "custom_oneshot.h"
#include "keycodes.h"

__attribute__((weak)) bool process_custom_one_shot(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // if ML_sc is pressed, it will be registered as MR_sft and if pressed again add ML_ctl, if pressed again remove MR_sft, if pressed again remove ML_ctl
        case ML_sc:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LCTL)) {
                    if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
                        combo_flag = 1;
                        process_custom_one_shot(ML_ctl, record);
                    } else {
                        combo_flag = 2;
                        process_custom_one_shot(ML_sft, record);
                    }
                } else if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
                    combo_flag = 2;
                    process_custom_one_shot(ML_sft, record);
                } else {
                    combo_flag = 1;
                    process_custom_one_shot(ML_ctl, record);
                }
            } else {
                if (combo_flag == 1) {
                    process_custom_one_shot(ML_ctl, record);
                } else if (combo_flag == 2) {
                    process_custom_one_shot(ML_sft, record);
                }
            }
            return true;
        case MR_sft:
            if (record->event.pressed) {
                if (!rshift_on) {
                    rshift_on = true;
                    register_code(KC_RSFT);
                    one_shot_timer = timer_read();
                } else {
                    rshift_on         = false;
                    is_oneshot_rshift = false;
                }
            } else {
                if ((rshift_on) && (!lshift_on) && (timer_elapsed(one_shot_timer) < 500)) {
                    is_oneshot_rshift = true;
                } else {
                    if (timer_elapsed(one_shot_timer) >= 500) {
                        is_oneshot_rshift = false;
                    }
                    if (lshift_on) {
                        is_oneshot_lshift = false;
                        lshift_on         = false;
                        unregister_code(KC_LSFT);
                    }
                    is_oneshot_rshift = false;
                    rshift_on         = false;
                    unregister_code(KC_RSFT);
                }
            }
            return true;
        case ML_sft:
            if (record->event.pressed) {
                if (!lshift_on) {
                    lshift_on = true;
                    register_code(KC_LSFT);
                    one_shot_timer = timer_read();
                } else {
                    lshift_on         = false;
                    is_oneshot_lshift = false;
                }
            } else {
                if ((!rshift_on) && (lshift_on) && (timer_elapsed(one_shot_timer) < 500)) {
                    is_oneshot_lshift = true;
                } else {
                    if (timer_elapsed(one_shot_timer) >= 500) {
                        is_oneshot_lshift = false;
                    }
                    if (rshift_on) {
                        is_oneshot_rshift = false;
                        rshift_on         = false;
                        unregister_code(KC_RSFT);
                    }
                    is_oneshot_lshift = false;
                    lshift_on         = false;
                    unregister_code(KC_LSFT);
                }
            }
            return true;
        case ML_alt:
            if (record->event.pressed) {
                if (!lalt_on) {
                    lalt_on = true;
                    register_code(KC_LALT);
                    one_shot_timer = timer_read();
                } else {
                    lalt_on         = false;
                    is_oneshot_lalt = false;
                }
            } else {
                if (lalt_on && (timer_elapsed(one_shot_timer) < 500)) {
                    is_oneshot_lalt = true;
                } else {
                    is_oneshot_lalt = false;
                    lalt_on         = false;
                    unregister_code(KC_LALT);
                }
            }
            return true;
        case ML_ctl:
            if (record->event.pressed) {
                if (!lctl_on) {
                    lctl_on = true;
                    register_code(KC_LCTL);
                    one_shot_timer = timer_read();
                } else {
                    lctl_on         = false;
                    is_oneshot_lctl = false;
                }
            } else {
                if (lctl_on && (timer_elapsed(one_shot_timer) < 500)) {
                    is_oneshot_lctl = true;
                } else {
                    is_oneshot_lctl = false;
                    lctl_on         = false;
                    unregister_code(KC_LCTL);
                }
            }
            return true;
        default:
            return true;
    }
}

void release_custom_one_shot(uint16_t keycode, const keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case ML_alt:
            // case KC_BSPC:
            case KC_DEL:
            case KC_SPC:
            case mo_FUNX:
            // case go_NAV:
            case go_NUM:
            case ML_ctl:
            case ML_sft:
            case MR_sft:
            case ML_sc:
#ifdef SWAP_HANDS_ENABLE
            case Mir_spc:
#endif
                break;

            default:
                if (is_oneshot_rshift) {
                    unregister_code(KC_RSFT);
                    is_oneshot_rshift = false;
                }
                if (rshift_on) {
                    rshift_on = false;
                }

                if (is_oneshot_lshift) {
                    unregister_code(KC_LSFT);
                    is_oneshot_lshift = false;
                }
                if (lshift_on) {
                    lshift_on = false;
                }
                if (is_oneshot_lalt) {
                    unregister_code(KC_LALT);
                    is_oneshot_lalt = false;
                }
                if (lalt_on) {
                    lalt_on = false;
                }
                if (is_oneshot_lctl) {
                    unregister_code(KC_LCTL);
                    is_oneshot_lctl = false;
                }
                if (lctl_on) {
                    lctl_on = false;
                }
        }
    }
}
