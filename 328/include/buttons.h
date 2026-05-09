#ifndef BUTTONS_H_
#define BUTTONS_H_

#pragma once

#include <avr/io.h>

#define BUTTONS_DDR DDRD
#define BUTTONS_PORT PORTD
#define BUTTON_1_PIN PD5
#define BUTTON_2_PIN PD6

/**
 * @brief Makes PD5 and PD6 input pins and turns on pull-up resistors.
 */
void buttons_init(void);

#endif  // BUTTONS_H_
