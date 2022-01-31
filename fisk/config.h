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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x6767 //vv
#define PRODUCT_ID   0x0054 // 54 key
#define DEVICE_VER   0x0001
#define MANUFACTURER vvhg1
#define PRODUCT      fisk

/* key matrix size */
/* Rows are doubled up-------------------------------------------------------------- */
#define MATRIX_ROWS  8
#define MATRIX_COLS  7

// wiring-----------------------------------------------------------------------
#define MATRIX_ROW_PINS \
    { B4, E6, D7, D4 }
#define MATRIX_COL_PINS \
    { B6, B2, B3, B1, F7, F6, F5}
#define UNUSED_PINS

#define ENCODERS_PAD_A \
    { C6 }
#define ENCODERS_PAD_B \
    { B5 }
//second encoder
/*#define ENCODERS_PAD_A_RIGHT \
    { B5 }
#define ENCODERS_PAD_B_RIGHT \
    { C6 }
*/
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE        5

//The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and D0/D1/D2/D3 (aka PD0/PD1/PD2/PD3) between the two Pro Micros.
//Note that the pin used here is actually set by SOFT_SERIAL_PIN
#    define SOFT_SERIAL_PIN D2

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Fix for Elite C rev3
#define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// Speed up slave half startup
#define SPLIT_USB_TIMEOUT 1000

// reduce size of firmwarepp
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define DISABLE_LEADER
