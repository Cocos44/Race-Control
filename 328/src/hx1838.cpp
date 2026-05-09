#include <hx1838.h>

void HX1838_init(void) {
    // Make pin input.
    HX1838_DDR &= ~(1 << HX1838_PIN);

    // Enable pull-up resistor.
    HX1838_PORT |= (1 << HX1838_PIN);
}
