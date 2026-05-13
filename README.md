# Race Control System

- Author: **Grigoras Vlad Andrei**

## Overview

Circuit Race Control System is a simplified and miniaturized race control system for a racing circuit. The system **detects cars** passing the `start/finish line`, identifies **which car passed**, handles **lap timing**, displays **race information** on a `16x2 I2C LCD display`, and provides a **basic flag system using an RGB LED**.

The project is based on an `ATmega328P Xplained Mini` as the main controller. Each car contains an `Arduino Nano` and an **infrared LED** used to transmit a ***modulated IR identification signal***.

## Features

- Car detection at the start/finish line
- Car identification using infrared burst duration
- Lap time calculation
- Race countdown displayed on LCD
- Race information displayed on a 16x2 I2C LCD
- Track temperature and humidity monitoring using DHT11
- RGB LED flag system
- Button-based user interaction
- USART debugging
- Modular code structure

## Hardware Components

| Component | Purpose |
|---|---|
| `ATmega328P Xplained Mini` | Main race control unit |
| `Arduino Nano` | Car-mounted IR transmitter |
| `IR LED 940 nm` | Infrared transmitter mounted on each car |
| `HX1838 IR Receiver` | Detects the modulated IR signal |
| `LCD 16x2 I2C` | Displays race information |
| `DHT11` | Measures temperature and humidity |
| `RGB LED` | Flag system |
| `Buttons` | User input for LCD screen switching and race control |

## Project Structure

The repository is split into two PlatformIO projects:

```text
├── 328/
│   ├── include/
│   ├── src/
│   └── platformio.ini
│
└── nano/
    ├── src/
    └── platformio.ini
```

### `328/`

Code for the main race control unit.

Modules:

| Module | Description |
|---|---|
| `main` | Race state, countdown, LCD state, high-level logic |
| `usart` | Serial debug output |
| `dht11` | Temperature and humidity sensor wrapper |
| `hx1838` | IR receiver and car detection |
| `lcd_display` | LCD initialization and printing |
| `led` | RGB LED flag control |
| `buttons` | Button handling using PCINT |
| `uptime` | Timer2 millisecond counter |

### `nano/`

Code for the Arduino Nano mounted on each car.

The Nano uses `Timer1 in CTC mode` to generate a `38KHz` singal on **D9 / PB1 / OC1A**.

To set the car identity, change the `CAR_ID` macro:

```c
#define CAR_ID 1
```

or:

```c
#define CAR_ID 2
```

## Race Flow

When the system starts, the LCD shows:

```text
Race Control
BTN2 to start!
```

When Button 2 is pressed, the countdown starts:

```text
3..
3...2...
3...2...1...
START
```

After the countdown:

- race state becomes `RUNNING`
- RGB LED turns green
- LCD displays race information
- car detection becomes active

Button behavior:

| Button | Before Race Start | After Race Start |
|---|---|---|
| Button 1 | - | Switch LCD screen |
| Button 2 | Start countdown | Change RGB flag color |

## Build and Upload

This project uses PlatformIO.

### Main Controller

```bash
cd 328
pio run -t upload
```

Open the serial monitor:

```bash
pio device monitor
```

### Car Transmitter

```bash
cd nano
pio run -t upload
```

Before uploading, set the correct `CAR_ID` in the Nano code.

## Serial Monitor

The code uses USART for debug messages.

The serial monitor is useful for checking:

- initialization messages
- button presses
- DHT11 values
- measured IR pulse durations
- detected car ID

## Code Documentation

The project uses Doxygen to generate source code documentation from
the comments written in the source and header files.

To generate the documentation locally for the main controller firmware:

```bash
cd 328
doxygen Doxyfile
```

To view the documentation, go to the root of the project and run:

```bash
firefox docs/index.html
```
