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

    // Read data from sensor.
    int err = dht11.read(temperature, humidity, NULL);

    // Return error code if error occured.
    if (err != SimpleDHTErrSuccess) return DHT11Status::READ_FAILED;

    return DHT11Status::OK;
}
