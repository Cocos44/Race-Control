/**
 * @file led.cpp
 * @brief RGB LED flag system implementation.
 *
 * This file implements the RGB LED control logic used to represent race flag
 * states.
 */

#include "led.h"

// Visible only in this file.
static LedColor current_color = LedColor::OFF;

void LED_clear_pins(void) {
    LED_PORT &=
        ~((1 << LED_RED_PIN) | (1 << LED_GREEN_PIN) | (1 << LED_BLUE_PIN));
}

void LED_init(void) {
    // Make RGB LED pins output.
    LED_DDR |= (1 << LED_RED_PIN);
    LED_DDR |= (1 << LED_GREEN_PIN);
    LED_DDR |= (1 << LED_BLUE_PIN);

    // Start with RGB LED turned off.
    LED_off();
}

void LED_off(void) {
    LED_clear_pins();

    current_color = LedColor::OFF;
}

void LED_set_color(LedColor color) {
    // Turn off all colors first.
    LED_clear_pins();

    switch (color) {
        case LedColor::RED:
            LED_PORT |= (1 << LED_RED_PIN);
            break;

        case LedColor::GREEN:
            LED_PORT |= (1 << LED_GREEN_PIN);
            break;

        case LedColor::BLUE:
            LED_PORT |= (1 << LED_BLUE_PIN);
            break;

        case LedColor::YELLOW:
            LED_PORT |= (1 << LED_RED_PIN);
            LED_PORT |= (1 << LED_GREEN_PIN);
            break;

        case LedColor::OFF:
        default:
            break;
    }

    current_color = color;
}

LedColor LED_get_current_color(void) { return current_color; }
