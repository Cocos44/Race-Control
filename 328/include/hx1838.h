#ifndef HX1838_SENSOR_H_
#define HX1838_SENSOR_H_

#pragma once

#include <avr/io.h>

#define HX1838_DDR DDRD
#define HX1838_PORT PORTD
#define HX1838_PIN PD2

/**
 * @brief Inits HX1838, makes the pin input and enables internal pull-up
 * resistor.
 */
void HX1838_init(void);

#endif  // HX1838_SENSOR_H_
