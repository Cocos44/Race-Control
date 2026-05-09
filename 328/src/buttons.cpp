#include <buttons.h>

void buttons_init() {
    // Make button pins input.
    BUTTONS_DDR &= ~(1 << BUTTON_1_PIN);
    BUTTONS_DDR &= ~(1 << BUTTON_2_PIN);

    // Enable pull up-resistors.
    BUTTONS_PORT |= (1 << BUTTON_1_PIN);
    BUTTONS_PORT |= (1 << BUTTON_2_PIN);

    // Enable PCINT group for PORTD.
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT21) | (1 << PCINT22);
}
