#ifndef MAIN_H_
#define MAIN_H_

#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Arduino.h"
#include "buttons.h"
#include "dht11.h"
#include "hx1838.h"
#include "lcd_display.h"
#include "led.h"
#include "uptime.h"
#include "usart.h"

#define DHT11_MAX_MESSAGE_LEN 64
#define LCD_LINE_LEN 17
#define CAR_DETECTION_DEBOUNCE 2000

/**
 * @brief Enum specifying race state.
 */
enum class RaceState { WAITING_START, COUNTDOWN, RUNNING };

/**
 * @brief Enum specifying what information is currently displayed on LCD.
 *
 * Current LCD screens:
 *     - LAP_TIMES: displays lap times for both cars.
 *     - TRACK_INFO: displays track temperature and humidity.
 */
enum class LCDScreenState { LAP_TIMES, TRACK_INFO };

/**
 * @brief Initializes all dependencies and sensors.
 * This includes:
 *     - Arduino Framework: Used by some of the sensors.
 *     - USART: Used to output status and possible errors to PC display.
 *     - DHT11: Temperature and humidity sensor.
 *     - HX1838: IR sensor used to detect passing and identification of cars.
 *     - LCD Dispay: Displays track information and timings.
 *     - Buttons: Change display output, change colour of flag.
 *     - LED: Flag.
 */
void init_project(void);

/**
 * @brief Displays race start countdown on LCD.
 */
void display_start_countdown(void);

/**
 * @brief Displays lap times for both cars.
 */
void display_lap_times(void);

/**
 * @brief Displays track information (temperature and humidity).
 */
void display_track_info(void);

/**
 * @brief Updates LCD based on current LCD screen state.
 */
void update_lcd_screen(void);

#endif  // MAIN_H_
