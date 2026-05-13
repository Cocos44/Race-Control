/**
 * @file uptime.h
 * @brief Timer2 millisecond uptime counter interface.
 *
 * This file exposes functions used to initialize, read and reset the global
 * millisecond uptime counter.
 */

#ifndef UPTIME_H_
#define UPTIME_H_

#pragma once

#include <stdint.h>

/**
 * @brief Initializes Timer2 to generate an interrupt every 1ms.
 *
 * Timer2 is used to maintain a global millisecond uptime counter.
 *
 * @note Global interrupts still need to be enabled using sei().
 */
void UPTIME_init(void);

/**
 * @brief Returns the number of milliseconds since startup.
 *
 * @return System uptime in milliseconds.
 */
uint32_t UPTIME_get_ms(void);

/**
 * @brief Resets uptime counter to 0.
 */
void UPTIME_reset(void);

#endif  // UPTIME_H_
