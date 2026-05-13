/**
 * @file dht11.cpp
 * @brief DHT11 temperature and humidity sensor implementation.
 *
 * This file implements the DHT11 sensor wrapper used by the race control
 * system. The sensor is connected to PD4 and is read using the SimpleDHT
 * library.
 */

#include "dht11.h"

// Visible only in this file.
static SimpleDHT11 dht11(DHT11_ARDUINO_PIN);

void DHT11_init() {
    // Make DHT11_PIN input.
    DHT11_DDR &= ~(1 << DHT11_PIN);

    // Enable pull up resistor.
    DHT11_PORT |= (1 << DHT11_PIN);
}

DHT11Status DHT11_read(uint8_t* temperature, uint8_t* humidity) {
    // Sanity check on parameters.
    if (!temperature || !humidity) return DHT11Status::INVALID_POINTER;

    // Re-enable internal pull-up before each read.
    DHT11_DDR &= ~(1 << DHT11_PIN);
    DHT11_PORT |= (1 << DHT11_PIN);

    // Read data from sensor.
    int err = dht11.read(temperature, humidity, NULL);

    // Return error code if error occured.
    if (err != SimpleDHTErrSuccess) return DHT11Status::READ_FAILED;

    return DHT11Status::OK;
}
