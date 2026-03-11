<<<<<<<< HEAD:keyboards/jankycaps/janky9/keymaps/default/keymap.c
/* Copyright 2025
========
/* Copyright 2022 Vladislav Kucheriavykh
 * Copyright 2025 Google LLC
>>>>>>>> master:tests/tap_hold_configurations/speculative_hold/flow_tap/config.h
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
 
#include QMK_KEYBOARD_H

<<<<<<<< HEAD:keyboards/jankycaps/janky9/keymaps/default/keymap.c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_1,  KC_2, KC_3,
        KC_4,  KC_5, KC_6,
        KC_7,  KC_8, KC_9
    ),
};
========
#pragma once

#include "test_common.h"

#define SPECULATIVE_HOLD
#define FLOW_TAP_TERM 150
#define PERMISSIVE_HOLD
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F24
>>>>>>>> master:tests/tap_hold_configurations/speculative_hold/flow_tap/config.h
