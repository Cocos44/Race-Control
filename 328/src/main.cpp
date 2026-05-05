#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Arduino.h"
#include "dht11.h"
#include "usart.h"

#define DHT11_MAX_MESSAGE_LEN 64

// Global variables.
char dht11_message[DHT11_MAX_MESSAGE_LEN];

void init_project() {
    // Init Arduino for components using it.
    init();

    // Init UART.
    USART0_init(MYUBRR);

    // Init DHT11 sensor.
    DHT11_init();
}

int main() {
    init_project();

    while (true) {
        byte temperature = 0;
        byte humidity = 0;

        DHT11Status dht11_status = DHT11_read(&temperature, &humidity);

        switch (dht11_status) {
            case DHT11Status::OK:
                snprintf(dht11_message, sizeof(dht11_message),
                         "Temperature: %d\r\nHumidity: %d\r\n", temperature,
                         humidity);
                USART0_print(dht11_message);
                break;
            case DHT11Status::INVALID_POINTER:
                USART0_print(
                    "DHT11 READ FAILED: received invalid pointer as "
                    "parameter!\r\n");
                break;
            case DHT11Status::READ_FAILED:
                USART0_print("DHT11 READ FAILED: sensor failed to read!\r\n");
                break;
        }

        _delay_ms(3000);
    }

    return 0;
}
