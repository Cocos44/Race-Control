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
    }

    return 0;
}
