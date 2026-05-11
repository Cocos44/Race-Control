#include "main.h"

#include "usart.h"

// Global variables.
char dht11_message[DHT11_MAX_MESSAGE_LEN];
char lcd_line[LCD_LINE_LEN];

RaceState race_state = RaceState::WAITING_START;
LCDScreenState lcd_screen_state = LCDScreenState::LAP_TIMES;

uint32_t car_1_lap_time = 0;
uint32_t car_2_lap_time = 0;

uint8_t temperature = 0;
uint8_t humidity = 0;

uint32_t last_pass_car_1 = 0;
uint32_t last_pass_car_2 = 0;

uint32_t last_pass_detected = 0;

void init_project() {
    // Init Arduino for components using it.
    init();

    // Init UART.
    USART0_init(MYUBRR);

    // Init DHT11 sensor.
    DHT11_init();

    // Init HX1838 sensor.
    HX1838_init();

    // Init LCD display.
    LCD_init();

    // Init buttons.
    BUTTONS_init();

    // Init LED.
    LED_init();

    UPTIME_init();

    USART0_print("Initialization complete......\r\n");
    USART0_print("Starting race control system......\r\n");

    // Print start phase.
    LCD_print_line(0, "Race Control");
    LCD_print_line(1, "BTN2 to start!");

    LED_set_color(LedColor::YELLOW);

    // Enable interrupts;
    sei();
}

void display_start_countdown(void) {
    race_state = RaceState::COUNTDOWN;

    LCD_clear();

    LCD_print_line(0, "3..");
    LCD_print_line(1, "");
    _delay_ms(1000);

    LCD_print_line(0, "3...2...");
    LCD_print_line(1, "");
    _delay_ms(1000);

    LCD_print_line(0, "3...2...1...");
    LCD_print_line(1, "");
    _delay_ms(1000);

    LCD_clear();
    LCD_print_line(0, "START");
    LCD_print_line(1, "");
    _delay_ms(2000);

    LCD_clear();
}

void display_lap_times(void) {
    // Display first car lap times on first line.
    snprintf(lcd_line, sizeof(lcd_line), "Car 1: %lu.%03lus",
             car_1_lap_time / 1000, car_1_lap_time % 1000);
    LCD_print_line(0, lcd_line);

    // Display second car lap times on second line.
    snprintf(lcd_line, sizeof(lcd_line), "Car 2: %lu.%03lus",
             car_2_lap_time / 1000, car_2_lap_time % 1000);
    LCD_print_line(1, lcd_line);
}

void display_track_info(void) {
    // Display temperature on first line.
    snprintf(lcd_line, sizeof(lcd_line), "Temperature: %d", temperature);
    LCD_print_line(0, lcd_line);

    // Display humidity on second line.
    snprintf(lcd_line, sizeof(lcd_line), "Humidity: %d", humidity);
    LCD_print_line(1, lcd_line);
}

void update_lcd_screen(void) {
    switch (lcd_screen_state) {
        case LCDScreenState::LAP_TIMES:
            display_lap_times();
            break;

        case LCDScreenState::TRACK_INFO:
            display_track_info();
            break;
    }
}

int main() {
    init_project();

    uint32_t dht11_last_measurement = UPTIME_get_ms();

    while (true) {
        if (BUTTONS_button_1_pressed()) {
            USART0_print("Button 1 was pressed!\r\n");

            switch (lcd_screen_state) {
                case LCDScreenState::LAP_TIMES:
                    lcd_screen_state = LCDScreenState::TRACK_INFO;
                    break;
                case LCDScreenState::TRACK_INFO:
                    lcd_screen_state = LCDScreenState::LAP_TIMES;
                    break;
                default:
                    lcd_screen_state = LCDScreenState::LAP_TIMES;
                    break;
            }
        }

        if (BUTTONS_button_2_pressed()) {
            USART0_print("Button 2 was pressed!\r\n");
            if (race_state == RaceState::WAITING_START) {
                display_start_countdown();

                UPTIME_reset();

                car_1_lap_time = 0;
                car_2_lap_time = 0;

                race_state = RaceState::RUNNING;
                lcd_screen_state = LCDScreenState::LAP_TIMES;

                LED_set_color(LedColor::GREEN);

                update_lcd_screen();
            } else {
                LedColor current_led_color = LED_get_current_color();

                switch (current_led_color) {
                    case LedColor::GREEN:
                        LED_set_color(LedColor::YELLOW);
                        break;
                    case LedColor::YELLOW:
                        LED_set_color(LedColor::GREEN);
                        break;
                    default:
                        LED_set_color(LedColor::GREEN);
                        break;
                }
            }
        }

        if (race_state == RaceState::RUNNING) {
            uint32_t now = UPTIME_get_ms();

            if (now - dht11_last_measurement >= 2000) {
                DHT11_read(&temperature, &humidity);
                dht11_last_measurement = now;
            }

            if (HX1838_pulse_available()) {
                if (now - last_pass_detected > CAR_DETECTION_DEBOUNCE) {
                    last_pass_detected = now;

                    uint8_t car_id = HX1838_get_detected_car_id();

                    if (car_id == HX1838_CAR_1_ID) {
                        last_pass_car_1 = now;

                        USART0_print("Car with ID 1 detected!\r\n");
                    }

                    if (car_id == HX1838_CAR_2_ID) {
                        last_pass_car_2 = now;

                        USART0_print("Car with ID 2 detected!\r\n");
                    }
                }
            }

            car_1_lap_time = now - last_pass_car_1;
            car_2_lap_time = now - last_pass_car_2;

            update_lcd_screen();
        }
    }

    cli();

    return 0;
}
