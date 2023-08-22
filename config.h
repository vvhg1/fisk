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

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
/* Serial connection between halfs */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* I2C config for display */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP11
#define I2C1_SDA_PIN GP10

/* key matrix size */
/* Rows are doubled up-------------------------------------------------------------- */
#define MATRIX_ROWS 8
#define MATRIX_COLS 7

// wiring-----------------------------------------------------------------------
#define MATRIX_ROW_PINS \
    { GP27, GP26, GP15, GP14 }
#define MATRIX_COL_PINS \
    { GP9, GP8, GP7, GP6, GP5, GP4, GP3 }

// encoder
#define ENCODERS_PAD_A \
    { GP12 }
#define ENCODERS_PAD_B \
    { GP13 }
// second encoder
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
#define DEBOUNCE 10

// The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and D0/D1/D2/D3 (aka PD0/PD1/PD2/PD3) between the two Pro Micros.

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Speed up slave half startup
#define SPLIT_USB_TIMEOUT 1000

// reduce size of firmwarepp
#define LAYER_STATE_16BIT
#define DISABLE_LEADER
