/**
 * @file hx1838.cpp
 * @brief HX1838 infrared receiver implementation.
 *
 * This file implements the infrared receiver logic used for car detection.
 * The HX1838 receiver is connected to PD2 / INT0. INT0 detects pulse edges,
 * while Timer1 measures pulse duration in order to identify the car that
 * emitted the IR burst.
 */

#include <hx1838.h>

// Check if car passed start/finish.
static volatile bool pulse_available = false;
//
// Number of ticks from IR LED of passing car.
static volatile uint16_t last_pulse_us = 0;

// ID of car that last passed.
static volatile uint8_t detected_car_id = HX1838_NO_CAR;

/**
 * @brief Initializes Timer1 for HX1838 pulse width measurement.
 *
 * Timer1 is configured in normal mode with a prescaler of 8.
 * With F_CPU = 16 MHz, this gives a timer frequency of:
 *     - 16 MHz / 8 = 2 MHz
 *
 * Therefore, one Timer1 tick represents:
 *     - 1 / 2 MHz = 0.5 us
 *
 * @note This function only configures Timer1. The counter is reset when a new
 * HX1838 pulse starts.
 */
static void HX1838_timer1_init(void) {
    // Timer1 normal mode.
    TCCR1A = 0;

    // Start Timer1 with prescaler 8.
    TCCR1B = (1 << CS11);

    // Reset Timer1 counter.
    TCNT1 = 0;
}

/**
 * @brief Initializes INT0 to intrerrupt on any logical change.
 *
 * Falling edge: HX1838 OUT goes LOW, pulse starts.
 * Rising edge:  HX1838 OUT goes HIGH, pulse ends.
 */
static void HX1838_int0_init(void) {
    // Any logical change.
    EICRA |= (1 << ISC00);

    // Activate INT0.
    EIMSK |= (1 << INT0);
}

void HX1838_init(void) {
    // Make pin input.
    HX1838_DDR &= ~(1 << HX1838_PIN);

    // Enable pull-up resistor.
    HX1838_PORT |= (1 << HX1838_PIN);

    HX1838_timer1_init();
    HX1838_int0_init();
}

bool HX1838_pulse_available(void) {
    if (pulse_available) {
        pulse_available = false;
        return true;
    }

    return false;
}

uint16_t HX1838_get_last_pulse_us(void) { return last_pulse_us; }

/**
 * @brief Classifies measured pulse duration.
 *
 * @param pulse_us - measured pulse duration in microseconds.
 * @return detected car ID or HX1838_NO_CAR.
 */
static uint8_t HX1838_classify_pulse(uint16_t pulse_us) {
    if (pulse_us >= HX1838_CAR_2_MIN_US && pulse_us <= HX1838_CAR_2_MAX_US)
        return HX1838_CAR_2_ID;

    if (pulse_us >= HX1838_CAR_1_MIN_US && pulse_us <= HX1838_CAR_1_MAX_US)
        return HX1838_CAR_1_ID;

    return HX1838_NO_CAR;
}

uint8_t HX1838_get_detected_car_id(void) {
    if (detected_car_id != HX1838_NO_CAR) {
        uint8_t car_id = detected_car_id;
        detected_car_id = HX1838_NO_CAR;
        return car_id;
    }

    return HX1838_NO_CAR;
}

ISR(INT0_vect) {
    bool pin_is_high = (PIND & (1 << HX1838_PIN)) != 0;

    if (!pin_is_high) {
        // Falling edge: pulse starts.
        TCNT1 = 0;
    } else {
        // Rising edge: pulse ends.
        uint16_t timer_ticks = TCNT1;

        // Timer1 tick = 0.5 us, so pulse_us = ticks / 2.
        last_pulse_us = timer_ticks / 2;

        uint8_t car_id = HX1838_classify_pulse(last_pulse_us);

        if (car_id != HX1838_NO_CAR) detected_car_id = car_id;

        pulse_available = true;
    }
}
