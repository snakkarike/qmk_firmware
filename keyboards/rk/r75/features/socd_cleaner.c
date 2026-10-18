// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file socd_cleaner.c
 * @brief SOCD Cleaner implementation
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/socd-cleaner>
 */

#include "socd_cleaner.h"
#include "eeconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

bool socd_cleaner_enabled = true;

#ifdef OPENRGB_ENABLE
extern uint8_t is_orgb_mode;
#endif

#ifdef SIGNALRGB_SUPPORT_ENABLE
extern uint8_t is_srgb_mode;
#endif

typedef union {
    uint8_t raw;
    struct {
        bool socd_enabled : 1;
        bool is_orgb_mode  : 1;
        bool is_srgb_mode  : 1;
    };
} rk_config_t;

#if (EECONFIG_KB_DATA_SIZE) > 0
void rk_load_config(void) {
    if (eeconfig_is_kb_datablock_valid()) {
        rk_config_t cfg;
        eeconfig_read_kb_datablock(&cfg.raw, 0, 1);
        socd_cleaner_enabled = cfg.socd_enabled;
#ifdef OPENRGB_ENABLE
        is_orgb_mode = cfg.is_orgb_mode ? 1 : 0;
#endif
#ifdef SIGNALRGB_SUPPORT_ENABLE
        is_srgb_mode = cfg.is_srgb_mode ? 1 : 0;
#endif
    } else {
        eeconfig_init_kb_datablock();
    }
}

void rk_save_config(void) {
    rk_config_t cfg = {0};
    cfg.socd_enabled = socd_cleaner_enabled;
#ifdef OPENRGB_ENABLE
    cfg.is_orgb_mode = is_orgb_mode ? 1 : 0;
#endif
#ifdef SIGNALRGB_SUPPORT_ENABLE
    cfg.is_srgb_mode = is_srgb_mode ? 1 : 0;
#endif
    eeconfig_update_kb_datablock(&cfg.raw, 0, 1);
}

void eeconfig_init_kb_datablock(void) {
    rk_config_t cfg = {0};
    cfg.socd_enabled = 1;
#ifdef OPENRGB_ENABLE
    cfg.is_orgb_mode = 0;
#endif
#ifdef SIGNALRGB_SUPPORT_ENABLE
    cfg.is_srgb_mode = 0;
#endif
    socd_cleaner_enabled = cfg.socd_enabled;
#ifdef OPENRGB_ENABLE
    is_orgb_mode = cfg.is_orgb_mode;
#endif
#ifdef SIGNALRGB_SUPPORT_ENABLE
    is_srgb_mode = cfg.is_srgb_mode;
#endif
    eeconfig_update_kb_datablock(&cfg.raw, 0, 1);
}

void socd_cleaner_init(void) {
    rk_load_config();
}

void socd_cleaner_set(bool enabled) {
    socd_cleaner_enabled = enabled;
    rk_save_config();
}

void socd_cleaner_toggle(void) {
    socd_cleaner_set(!socd_cleaner_enabled);
}
#else
void rk_load_config(void) {}
void rk_save_config(void) {}
void socd_cleaner_init(void) {}
void socd_cleaner_set(bool enabled) {
    socd_cleaner_enabled = enabled;
}
void socd_cleaner_toggle(void) {
    socd_cleaner_enabled = !socd_cleaner_enabled;
}
#endif

static void update_key(uint8_t keycode, bool press) {
  if (press) {
    add_key(keycode);
  } else {
    del_key(keycode);
  }
}

bool process_socd_cleaner(uint16_t keycode, keyrecord_t* record,
                          socd_cleaner_t* state) {
  if (!socd_cleaner_enabled || !state->resolution ||
      (keycode != state->keys[0] && keycode != state->keys[1])) {
    return true;  // Quick return when disabled or on unrelated events.
  }
  // The current event corresponds to index `i`, 0 or 1, in the SOCD key pair.
  const uint8_t i = (keycode == state->keys[1]);
  const uint8_t opposing = i ^ 1;  // Index of the opposing key.

  // Track which keys are physically held (vs. keys in the report).
  state->held[i] = record->event.pressed;

  // Perform SOCD resolution for events where the opposing key is held.
  if (state->held[opposing]) {
    switch (state->resolution) {
      case SOCD_CLEANER_LAST:  // Last input priority with reactivation.
        // If the current event is a press, then release the opposing key.
        // Otherwise if this is a release, then press the opposing key.
        update_key(state->keys[opposing], !state->held[i]);
        break;

      case SOCD_CLEANER_NEUTRAL:  // Neutral resolution.
        // Same logic as SOCD_CLEANER_LAST, but skip default handling so that
        // the current key has no effect while the opposing key is held.
        update_key(state->keys[opposing], !state->held[i]);
        // Send updated report (normally, default handling would do this).
        send_keyboard_report();
        return false;  // Skip default handling.

      case SOCD_CLEANER_0_WINS:  // Key 0 wins.
      case SOCD_CLEANER_1_WINS:  // Key 1 wins.
        if (opposing == (state->resolution - SOCD_CLEANER_0_WINS)) {
          // The opposing key is the winner. The current key has no effect.
          return false;  // Skip default handling.
        } else {
          // The current key is the winner. Update logic is same as above.
          update_key(state->keys[opposing], !state->held[i]);
        }
        break;
    }
  }
  return true;  // Continue default handling to press/release current key.
}
