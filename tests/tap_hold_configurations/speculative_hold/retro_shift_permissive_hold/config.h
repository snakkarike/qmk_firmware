<<<<<<<< HEAD:keyboards/keychron/c2_pro_v2/ansi/white/config.h
/* Copyright 2025 @ Keychron (https://www.keychron.com)
========
/* Copyright 2022 Isaac Elenbaas
 * Copyright 2025 Google LLC
>>>>>>>> master:tests/tap_hold_configurations/speculative_hold/retro_shift_permissive_hold/config.h
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

<<<<<<<< HEAD:keyboards/keychron/c2_pro_v2/ansi/white/config.h
/* LED Matrix Driver Configuration */
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_GND

/* Use the first 8 channels of led driver */
#define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_8_CHANNEL

/* Set LED driver current */
#define SNLED27351_CURRENT_TUNE { 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50 }
========
#include "test_common.h"

#define SPECULATIVE_HOLD
#define PERMISSIVE_HOLD

#define RETRO_SHIFT 2 * TAPPING_TERM
// releases between AUTO_SHIFT_TIMEOUT and TAPPING_TERM are not tested
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_MODIFIERS

#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F24
>>>>>>>> master:tests/tap_hold_configurations/speculative_hold/retro_shift_permissive_hold/config.h
