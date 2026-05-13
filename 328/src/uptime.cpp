/**
 * @file uptime.cpp
 * @brief Timer2 millisecond uptime counter implementation.
 *
 * This file implements a millisecond uptime counter using Timer2 in CTC mode.
 * The counter is used for race timing, periodic sensor reads and timing logic.
 */

#include "uptime.h"

#include <avr/interrupt.h>
#include <avr/io.h>

// Visible only in this file.
static volatile uint32_t ms_uptime = 0;

void UPTIME_init(void) {
    // CTC mode.
    TCCR2A = (1 << WGM21);

    // Prescaler 64.
    TCCR2B = (1 << CS22);

    // Compare value for 1 ms.
    OCR2A = 249;

    // Reset counter.
    TCNT2 = 0;

    // Enable Timer2 Compare Match A interrupt.
    TIMSK2 |= (1 << OCIE2A);
}

uint32_t UPTIME_get_ms(void) {
    uint32_t uptime;

    // Reading it is not atomic, so interrupts must be disabled.
    cli();
    uptime = ms_uptime;
    sei();

    return uptime;
}

void UPTIME_reset(void) {
    cli();
    ms_uptime = 0;
    sei();
}

ISR(TIMER2_COMPA_vect) { ms_uptime++; }
