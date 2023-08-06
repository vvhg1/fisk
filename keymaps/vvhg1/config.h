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
// !this defines which side and which font to use
// #define IS_LEFT

#ifdef CUSTOM_LEADER_ENABLE
#    define LEADER_DISPLAY_STR
#endif

#ifdef CASEMODES_ENABLE
// #define CAPSWORD_USE_CAPS
#endif

#ifdef OLED_ENABLE
#    define OLED_BRIGHTNESS 128
// #define OLED_DISPLAY_128X32
#    define OLED_TIMEOUT 7000
#    define SPLIT_OLED_ENABLE
#    define SPLIT_MODS_ENABLE
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#endif
// #define NO_USB_STARTUP_CHECK

#ifdef ENCODER_ENABLE
//#    define ENCODER_DIRECTION_FLIP
// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#    define ENCODER_RESOLUTION 4
#endif

#ifndef IS_LEFT
#    define OLED_FONT_H "keyboards/handwired/fisk/fonts/glcdfont_fisk_right.c"
#else
#    define OLED_FONT_H "keyboards/handwired/fisk/fonts/glcdfont_fisk_left.c"
#endif

#define NO_ACTION_TAPPING
#ifdef CUSTOM_ONE_SHOT_ENABLE
#    define NO_ACTION_ONESHOT
#endif
