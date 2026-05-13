/**
 * @file buttons.cpp
 * @brief Button handling implementation using Pin Change Interrupts.
 *
 * This file implements button detection for BUTTON_1 and BUTTON_2. The buttons
 * are connected to PD5 and PD6 and use internal pull-up resistors. Pin Change
 * Interrupts are used to detect button press events.
 */

#include <buttons.h>

// Visible only in this file.
static volatile bool button_1_pressed = false;
static volatile bool button_2_pressed = false;

// Stores previous PORTD state.
static volatile uint8_t last_pind_state = 0;

void BUTTONS_init() {
    // Make button pins input.
    BUTTONS_DDR &= ~(1 << BUTTON_1_PIN);
    BUTTONS_DDR &= ~(1 << BUTTON_2_PIN);

    // Enable pull up-resistors.
    BUTTONS_PORT |= (1 << BUTTON_1_PIN);
    BUTTONS_PORT |= (1 << BUTTON_2_PIN);

    // Save initial state of PORTD.
    last_pind_state = PIND;

    // Enable PCINT group for PORTD.
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT21) | (1 << PCINT22);
}

bool BUTTONS_button_1_pressed(void) {
    /**
     * Note that we change the state of button_1_pressed.
     * Why?
     *
     * Because if I hold down the button, the program will think
     * that I am pressing it multiple times instead of holding it.
     */
    if (button_1_pressed) {
        button_1_pressed = false;
        return true;
    }

    return false;
}

bool BUTTONS_button_2_pressed(void) {
    /**
     * Note that we change the state of button_1_pressed.
     * Why?
     *
     * Because if I hold down the button, the program will think
     * that I am pressing it multiple times instead of holding it.
     */
    if (button_2_pressed) {
        button_2_pressed = false;
        return true;
    }

    return false;
}

ISR(PCINT2_vect) {
    // Check if BUTTON_1 pin changed.
    bool button_1_changed =
        (PIND & (1 << BUTTON_1_PIN)) != (last_pind_state & (1 << BUTTON_1_PIN));

    // Check if BUTTON_2 pin changed.
    bool button_2_changed =
        (PIND & (1 << BUTTON_2_PIN)) != (last_pind_state & (1 << BUTTON_2_PIN));

    /**
     * We only care about the press event, so we check if the pin
     * is currently LOW after it changed.
     */
    if (button_1_changed)
        if (!(PIND & (1 << BUTTON_1_PIN))) button_1_pressed = true;

    if (button_2_changed)
        if (!(PIND & (1 << BUTTON_2_PIN))) button_2_pressed = true;

    // Save current state for the next interrupt.
    last_pind_state = PIND;
}
