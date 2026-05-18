/**
 * @file hx1838.h
 * @brief HX1838 infrared receiver interface.
 *
 * This file defines the HX1838 pin mapping, car ID constants, detection
 * thresholds and public functions used for infrared pulse measurement and
 * car identification.
 */

#ifndef HX1838_SENSOR_H_
#define HX1838_SENSOR_H_

#pragma once

#define HX1838_NO_CAR 0

#define HX1838_CAR_1_ID 1
#define HX1838_CAR_2_ID 2

#define HX1838_CAR_1_MIN_US 650
#define HX1838_CAR_1_MAX_US 1450

#define HX1838_CAR_2_MIN_US 1600
#define HX1838_CAR_2_MAX_US 2400

#include <avr/interrupt.h>
#include <avr/io.h>

#define HX1838_DDR DDRD
#define HX1838_PORT PORTD
#define HX1838_PIN PD2

/**
 * @brief Inits HX1838, makes the pin input and enables internal pull-up
 * resistor.
 */
void HX1838_init(void);

/**
 * @brief Checks if a new pulse was measured.
 *
 * @return true if a new pulse is available, false otherwise.
 */
bool HX1838_pulse_available(void);

/**
 * @brief Gets last measured pulse duration in microseconds.
 *
 * @return Pulse duration in microseconds.
 */
uint16_t HX1838_get_last_pulse_us(void);

/**
 * @brief Gets the car ID based on it's pulse duration in microseconds.
 *
 * @returns ID of car.
 */
uint8_t HX1838_get_detected_car_id(void);

#endif  // HX1838_SENSOR_H_
