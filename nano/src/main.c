/**
 * @file main.c
 * @brief IR transmitter for a car.
 *
 * The IR sensor we use on the main controller detects
 * IR emitted signal at 38KHz.
 *
 * In order for the race control system to detect what car
 * has passed, each one will emit IR light at different bursts.
 *
 * For example:
 *     - Car Nr.1 will emit the pulse for 1ms, then stop for 1ms.
 *     - Car Nr.2 will emit the pulse for 2ms, then stop for 1ms.
 *
 * @note This program needs to be changed for every car!
 */
#define F_CPU 16000000UL

#define CAR_ID 2

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

/**
 * @brief Starts Timer1 on CTC mode and emits a 38KHz pulse on PB1.
 *
 * We use this formula to get the values needed for a 38KHz pulse:
 * f_out = F_CPU / (2 * prescaler * (1 + OCR1A))
 */
void start_pulse(void) {
    // Reset timer counter in case it had a non-zero value when
    // it stopped emitting light.
    TCNT1 = 0;

    // Make PB1 (Arduino pin D9) output for IR LED.
    DDRB |= (1 << PB1);

    // Toggle OC1A on compare match.
    TCCR1A = (1 << COM1A0);

    // Enable CTC mode.
    // Use 8 as prescaler.
    TCCR1B = (1 << WGM12) | (1 << CS11);

    // Compare value to approximate 38KHz.
    OCR1A = 25;
}

/**
 * @brief Stops the 38 kHz pulse.
 *
 * Disconnects OC1A from Timer1 and forces PB1 LOW, making sure the IR LED
 * is turned off between bursts.
 */
void stop_pulse(void) {
    // Disconnect OC1A from the timer output.
    TCCR1A &= ~(1 << COM1A0);

    // Force PB1 LOW so the IR LED is OFF.
    PORTB &= ~(1 << PB1);
}

/**
 * @brief Sends burst specific to the car ID.
 *
 * Send a pulse of 38KHz IR light for a specific amount of
 * time, stop for 1ms and start all over again.
 */
void send_burst(void) {
    start_pulse();
    _delay_ms(CAR_ID);

    stop_pulse();
    _delay_ms(1);
}

int main(void) {
    while (true) send_burst();

    return 0;
}
