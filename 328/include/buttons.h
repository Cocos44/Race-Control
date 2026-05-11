#ifndef BUTTONS_H_
#define BUTTONS_H_

#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>

#define BUTTONS_DDR DDRD
#define BUTTONS_PORT PORTD
#define BUTTON_1_PIN PD5
#define BUTTON_2_PIN PD6

/**
 * @brief Makes PD5 and PD6 input pins and turns on pull-up resistors.
 */
void BUTTONS_init(void);

/**
 * @brief Checks if BUTTON 1 was pressed.
 *
 * BUTTON_1 is used to cycle through LCD display information.
 *
 * @return true if BUTTON 1 was pressed, false otherwise.
 */
bool BUTTONS_button_1_pressed(void);

/**
 * @brief Checks if BUTTON_2 was pressed.
 *
 * BUTTON 2 is used to start the race countdown once.
 * After the race starts, it can be used to change the RGB LED color.
 *
 * @return true if BUTTON 2 was pressed, false otherwise.
 */
bool BUTTONS_button_2_pressed(void);

#endif  // BUTTONS_H_
