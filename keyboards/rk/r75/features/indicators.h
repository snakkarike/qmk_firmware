#pragma once

#include QMK_KEYBOARD_H

// Row 4 and bottom row LED indices >= 64 are shifted by +1 on ISO (81 LEDs) due to extra key [4, 12]
#define R75_LED(idx) ((uint8_t)((idx) >= 64 && RGB_MATRIX_LED_COUNT > 80 ? ((idx) + 1) : (idx)))

void blink_arrows(void);
void blink_space(bool);
void blink_NKRO(bool);
void blink_SOCD(bool);
void blink_numbers(bool);
void highlight_fn_keys(uint8_t led_min, uint8_t led_max);
