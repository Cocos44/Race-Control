#include "lcd_display.h"

// Visible only in this file.
static LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_COLS, LCD_ROWS);

void LCD_init(void) {
    // Init LCD display.
    lcd.begin();

    // Turn backlight ON.
    lcd.backlight();

    // Clear display.
    lcd.clear();
}

void LCD_clear(void) { lcd.clear(); }

void LCD_backlight_on(void) { lcd.backlight(); }

void LCD_backlight_off(void) { lcd.noBacklight(); }

LCDStatus LCD_set_cursor(uint8_t col, uint8_t row) {
    // Sanity check on parameters.
    if (row >= LCD_ROWS) return LCDStatus::INVALID_LINE;
    if (col >= LCD_COLS) return LCDStatus::INVALID_LINE;

    lcd.setCursor(col, row);

    return LCDStatus::OK;
}

LCDStatus LCD_print(const char* text) {
    // Sanity check on parameters.
    if (!text) return LCDStatus::INVALID_POINTER;

    lcd.print(text);

    return LCDStatus::OK;
}

LCDStatus LCD_print_line(uint8_t line, const char* text) {
    // Sanity check on parameters.
    if (!text) return LCDStatus::INVALID_POINTER;
    if (line >= LCD_ROWS) return LCDStatus::INVALID_LINE;

    // Clear selected line.
    lcd.setCursor(0, line);
    lcd.print("                ");

    // Print new text.
    lcd.setCursor(0, line);
    lcd.print(text);

    return LCDStatus::OK;
}
