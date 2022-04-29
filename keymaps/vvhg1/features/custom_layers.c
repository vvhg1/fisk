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

#include "custom_layers.h"
#include "enumlayers.h"
#include "keycodes.h"

void process_custom_layer(const keyrecord_t *record, uint8_t targetlayer) {
    if (record->event.pressed) {
        switch (targetlayer) {
            case _NAV:
                one_shot_timer = timer_read();

                if (IS_LAYER_ON(_NUM)) {
                    layer_off(_NUM);
                    came_from_NAV = true;
                }
                if (IS_LAYER_ON(_NAV)) {
                    came_from_NAV = false;
                    break;
                } else {
                    layer_toggle_flag = true;
                    layer_on(_NAV);
                }
                break;

            case _NUM:
                one_shot_timer = timer_read();

                if (IS_LAYER_ON(_NAV)) {
                    layer_off(_NAV);
                    came_from_NAV = true;
                }
                if (IS_LAYER_ON(_NUM)) {
                    came_from_NAV = false;
                    break;
                } else {
                    layer_toggle_flag = true;
                    layer_on(_NUM);
                }
                break;

            case _FUNX:
            case _AUX:
                layer_on(targetlayer);
                break;
        }
    } else {
        switch (targetlayer) {
            case _NAV:
                if (!layer_toggle_flag || (timer_elapsed(one_shot_timer) > 500)) {
                    if (IS_LAYER_ON(_NUM)) {
                        layer_off(_NUM);
                        if (came_from_NAV) {
                            layer_on(_NAV);
                            came_from_NAV = false;
                        }
                    } else if (IS_LAYER_ON(_NAV)) {
                        layer_off(_NAV);
                        if (came_from_NAV) {
                            layer_on(_NUM);
                            came_from_NAV = false;
                        }
                    }
                }
                break;
            case _NUM:
                if (!layer_toggle_flag || (timer_elapsed(one_shot_timer) > 500)) {
                    if (IS_LAYER_ON(_NUM)) {
                        layer_off(_NUM);
                        if (came_from_NAV) {
                            layer_on(_NAV);
                            came_from_NAV = false;
                        }
                    }
                }
                break;

            case _FUNX:
            case _AUX:
                layer_off(targetlayer);
                break;
        }
    }
}
