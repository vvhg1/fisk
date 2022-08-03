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

#include "quantum.h"


/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *SWAP_HANDS_ENABLE
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
         L01, L02, L03, L04, L05, L06,                                    R05, R06, R07, R08, R09, R10, \
    L12, L13, L14, L15, L16, L17, L18,                                    R17, R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29,        L31, L32,             R31, R32,        R34, R35, R36, R37, R38, R39, \
    L40, L41,              L42, L43, L44,     L45,            R44,     R45, R46, R47,              R48, R49 \
) \
{ \
    { L06,   L05,   L04,   L03,   L02,   L01,   KC_NO   }, \
    { L18,   L17,   L16,   L15,   L14,   L13,   L12   }, \
    { L31,   L29,   L28,   L27,   L26,   L25,   L24   }, \
    { L32,   L45,   L44,   L43,   L42,   L41,   L40 }, \
    { R05,   R06,   R07,   R08,   R09,   R10,   KC_NO   }, \
    { R17,   R18,   R19,   R20,   R21,   R22,   R23   }, \
    { R32,   R34,   R35,   R36,   R37,   R38,   R39   }, \
    { R31,   R44,   R45,   R46,   R47,   R48,   R49 }, \
}
