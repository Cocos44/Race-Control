#ifndef DHT11_SENSOR_H_
#define DHT11_SENSOR_H_

#pragma once

#include <avr/io.h>
#include <stdint.h>

#include "SimpleDHT.h"

#define DHT11_DDR DDRD
#define DHT11_PORT PORTD
#define DHT11_PIN PD4

#define DHT11_ARDUINO_PIN 4

// Enum specifying read status.
enum class DHT11Status { OK, INVALID_POINTER, READ_FAILED };

/**
 * @brief Inits DHT11, makes the pin input and enables internal pull-up
 * resistor.
 */
void DHT11_init(void);

/**
 * @brief Reads data from sensor.
 * @param temperature - temperature read from sensor.
 * @param humidity - humidity read from sensor.
 * @return DHT11 status (INVALID_POINTER, READ_FAILED, OK).
 * @note For best use of the sensor, wait for 2 seconds between every read!
 */
DHT11Status DHT11_read(uint8_t* temperature, uint8_t* humidity);

#endif  // DHT11_SENSOR_H_
