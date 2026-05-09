#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

#pragma once

#include <stdint.h>

#include "LiquidCrystal_I2C.h"

#define LCD_I2C_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// Enum specifying LCD status.
enum class LCDStatus { OK, INVALID_POINTER, INVALID_LINE };

/**
 * @brief Inits LCD display.
 *
 * The LCD uses I2C communication:
 *     - SDA: PC4
 *     - SCL: PC5
 */
void LCD_init(void);

/**
 * @brief Clears LCD display.
 */
void LCD_clear(void);

/**
 * @brief Turns LCD backlight on.
 */
void LCD_backlight_on(void);

/**
 * @brief Turns LCD backlight off.
 */
void LCD_backlight_off(void);

/**
 * @brief Sets LCD cursor position.
 *
 * @param col - column index.
 * @param row - row index.
 * @return LCD status.
 */
LCDStatus LCD_set_cursor(uint8_t col, uint8_t row);

/**
 * @brief Prints text at current cursor position.
 *
 * @param text - text to print.
 * @return LCD status.
 */
LCDStatus LCD_print(const char* text);

/**
 * @brief Prints text on a specific LCD line.
 *
 * @param line - LCD line index. Valid values: 0 or 1.
 * @param text - text to print.
 * @return LCD status.
 */
LCDStatus LCD_print_line(uint8_t line, const char* text);

#endif  // LCD_DISPLAY_H_
