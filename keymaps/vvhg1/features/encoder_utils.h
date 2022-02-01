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

#pragma once

#include <stdbool.h>

#include "quantum.h"

typedef enum {
    ENC_MODE_WORD_NAV = 0,
    ENC_MODE_LEFT_RIGHT,
    ENC_MODE_UP_DOWN,
    ENC_MODE_PAGING,
    ENC_MODE_NEXTEDITOR,
    ENC_MODE_NEXTTAB,
    _ENC_MODE_LAST  // Do not use, except for looping through enum values
} encoder_mode_t;

encoder_mode_t enc_mode;

void encoder_utils_init(void);

void set_encoder_mode(encoder_mode_t mode);

encoder_mode_t get_encoder_mode(void);

void cycle_encoder_mode(bool clockwise);

void encoder_action_word_nav(uint8_t clockwise);

void encoder_action_left_right(uint8_t clockwise);

void encoder_action_up_down(uint8_t clockwise);

void encoder_action_paging(uint8_t clockwise);

void encoder_action_nexteditor(uint8_t clockwise);

void encoder_action_nexttab(uint8_t clockwise);

void encoder_action(encoder_mode_t mode, uint8_t clockwise);
