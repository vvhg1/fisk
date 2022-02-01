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

#pragma once

#include "keycodes.h"

#ifdef ENCODER_ENABLE
#    include "encoder_utils.h"
#endif

bool is_keyboard_left(void);

void render_layer(void);
#ifdef ENCODER_ENABLE
void render_encoder(encoder_mode_t mode);
#endif
void render_status(void);
void render_logo_l(void);
void render_logo_r(void);
#ifdef CASEMODES_ENABLE
void render_case_modes(void);
#endif
