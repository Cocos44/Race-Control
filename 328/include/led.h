#ifndef RGB_LED_H_
#define RGB_LED_H_

#pragma once

#include <avr/io.h>
#include <stdint.h>

#define LED_DDR DDRB
#define LED_PORT PORTB

#define LED_RED_PIN PB1
#define LED_GREEN_PIN PB2
#define LED_BLUE_PIN PB3

// Enum specifying available LED colors.
enum class LedColor { OFF, RED, GREEN, BLUE, YELLOW };

/**
 * @brief Inits LED pins as output.
 *
 * RGB LED pin mapping:
 *     - RED: PB1
 *     - GREEN: PB2
 *     - BLUE: PB3
 *
 * @note This implementation assumes a common cathode RGB LED.
 */
void LED_init(void);

/**
 * @brief Turns LED off.
 */
void LED_off(void);

/**
 * @brief Sets LED color.
 *
 * @param color - color to be displayed.
 */
void LED_set_color(LedColor color);

/**
 * @brief Gets current LED color.
 *
 * @return Current LED color.
 */
LedColor LED_get_current_color(void);

#endif  // RGB_LED_H_
