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

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "enumlayers.h"

uint8_t DotC_mod_state;
uint8_t mod_state;

uint16_t startup_timer;
uint16_t one_shot_timer;

bool mns_flipped;
bool layer_toggle_flag;
bool prev_layer_toggle_flag;
bool came_from_NAV;
bool cleared_oled;
#ifdef SWAP_HANDS_ENABLE
bool no_swap;
#endif

enum custom_keycodes {
    Undo = SAFE_RANGE,
    Cut,
    Copy,
    Paste,
    Redo,
    Sq_Br,
    Cr_Br,
    Op_Br,
    Sq_BrS,
    Cr_BrS,
    Op_BrS,
    Enc_M,
    go_NAV,
    go_NUM,
    CAPS_WORD,
    SNAKE_CASE,
    NUM_WORD,
    DotC,
    SelWrdL,
    SelWrdR,
    SelLn,
    SelLnUp,
    SelLnDn,
    FLP_MIN,
    QuotWrap,
    LEADER,
    // Ins_Cursor,
    ML_sft,
    MR_sft,
    ML_alt,
    ML_ctl,
    mo_FUNX,
#ifdef SWAP_HANDS_ENABLE
    Mir_spc,
#endif
    mo_AUX

};

#ifdef CONSOLE_ENABLE
# define DEBUGg DEBUG
#else
# define DEBUGg _______
#endif


