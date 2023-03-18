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

#pragma once

#include QMK_KEYBOARD_H

bool rshift_on;
int  combo_flag;
bool is_oneshot_rshift;
bool lshift_on;
bool is_oneshot_lshift;
bool lctl_on;
bool is_oneshot_lctl;
bool lalt_on;
bool is_oneshot_lalt;

bool process_custom_one_shot(uint16_t keycode, const keyrecord_t *record);
void release_custom_one_shot(uint16_t keycode, const keyrecord_t *record);
