/**
 * @file usart.cpp
 * @brief USART0 implementation.
 *
 * This file implements basic USART0 functionality used for serial debugging.
 * It provides functions for initializing USART0, transmitting characters,
 * receiving characters and printing null-terminated strings.
 */

#include "usart.h"

#include <avr/io.h>

void USART0_init(unsigned int ubrr) {
    /* seteaza baud rate-ul */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* porneste transmitatorul */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /* seteaza formatul frame-ului: 8 biti de date, 2 biti de stop, fara
     * paritate */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART0_transmit(char data) {
    /* asteapta pana bufferul e gol */
    while (!(UCSR0A & (1 << UDRE0)));

    /* pune datele in buffer; transmisia va porni automat in urma scrierii */
    UDR0 = data;
}

char USART0_receive() {
    /* asteapta cat timp bufferul e gol */
    while (!(UCSR0A & (1 << RXC0)));

    /* returneaza datele din buffer */
    return UDR0;
}

void USART0_print(const char* data) {
    while (*data != '\0') USART0_transmit(*data++);
}
