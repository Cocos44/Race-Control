#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Arduino.h"
#include "dht11.h"
#include "hx1838.h"
#include "lcd_display.h"
#include "usart.h"

#define DHT11_MAX_MESSAGE_LEN 64

// Global variables.
char dht11_message[DHT11_MAX_MESSAGE_LEN];

/**
 * @brief Initializes all dependencies and sensors.
 * This includes:
 *     - Arduino Framework: Used by some of the sensors.
 *     - USART: Used to output status and possible errors to PC display.
 *     - DHT11: Temperature and humidity sensor.
 *     - HX1838: IR sensor used to detect passing and identification of cars.
 */
void init_project() {
    // Init Arduino for components using it.
    init();

    // Init UART.
    USART0_init(MYUBRR);

    // Init DHT11 sensor.
    DHT11_init();

    // Init HX1838 sensor.
    HX1838_init();

    // Init LCD display.
    LCD_init();
}

int main() {
    init_project();

    USART0_print("Initialization complete......\r\n");
    USART0_print("Starting race control system......\r\n");

    LCD_print_line(0, "Race Control");
    LCD_print_line(1, "BTN1 to start!");

    while (true) {
    }

    return 0;
}
