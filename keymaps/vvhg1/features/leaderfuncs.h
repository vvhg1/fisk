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
// int variable to store the number
int numberofiterationsforleader;
int myint;

//string to store the sequence
char sequence[10];
// Leader functions
// void *reset_keyboard1(uint16_t keycode); // here LDR qrk will reset the keyboard
// void *reset_keyboard2(uint16_t keycode); //
void *windows_stuff(uint16_t keycode); // here WS is Start menu, WM is context menu WQ  close tab
void *vscode_stuff(uint16_t keycode);
void *vscode_stuff_no(uint16_t keycode); // here vn select editor right/ vi left
void *vscode_stuff_m(uint16_t keycode); // vmn moves editor to right group / vmi to left
void *vscode_stuff_f(uint16_t keycode); // vfn vfi focus on group left right
void *vscode_stuff_p(uint16_t keycode); // vu ve move ln up dn
void *vscode_stuff_a(uint16_t keycode); // vu ve move ln up dn
void *vscode_stuff_brackets(uint16_t keycode); // bracket selection
// void *encoder_stuff(uint16_t keycode); // h horizontal scroll / v vertical scroll / e editor / t tab / p paging / w word
void *macro_stuff(uint16_t keycode); // m records and plays macros
void *umlaut_stuff(uint16_t keycode); // german umlaut
void *xcase_stuff(uint16_t keycode); // snake case and caps
void *f_key_stuff(uint16_t keycode); // F1-F11
void *operator_stuff(uint16_t keycode); // operators
void *numbers_game(uint16_t keycode); // numbers
void  select_in_bracets(void);
void *vscode_markers(uint16_t keycode);
