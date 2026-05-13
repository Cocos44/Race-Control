# Circuit Race Control System

This documentation was generated using Doxygen.

## Project Structure

The project contains two targets:

- `328/` - main race control unit based on ATmega328P Xplained Mini
- `nano/` - Arduino Nano car transmitter firmware

## Main Modules

- `main` - race logic, countdown, LCD state
- `usart` - serial debugging
- `dht11` - temperature and humidity readings
- `hx1838` - IR receiver and car detection
- `lcd_display` - LCD control
- `led` - RGB flag LED
- `buttons` - button handling using PCINT
- `uptime` - Timer2 millisecond counter
