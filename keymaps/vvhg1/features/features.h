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

#ifdef CASEMODES_ENABLE
#include "features/casemodes.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
#include "features/leader.h"
#include "features/leaderfuncs.h"
#endif
#ifdef CUSTOM_ONE_SHOT_ENABLE
#include "features/custom_oneshot.h"
#endif

#include "features/custom_layers.h"

#ifdef ENCODER_ENABLE
#    include "features/encoder_utils.h"
#endif

#ifdef OLED_ENABLE
#    include "features/oled_utils.h"
#endif
#ifdef   EOS_ENABLE
#    include "features/eos_util.h"
#endif
#ifdef   POWER_BRACKETS_ENABLE
#    include "features/power_brackets.h"
#endif
#ifdef CUSTOM_WORD_LINE_SELECTION_ENABLE
#    include "features/word_line_selection.h"
#endif
