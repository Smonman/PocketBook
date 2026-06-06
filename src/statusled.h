/**
 * @file statusled.h
 * @brief Status LED functionality
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#ifndef _STATUS_LED_H_
#define _STATUS_LED_H_

#define DELAY_MS 500
#define COOLDOWN_MS 200

/**
 * @brief Turns the status LED on.
 */
void led_on();

/**
 * @brief Turns the status LED off.
 */
void led_off();

/**
 * @brief Blinks the LED once.
 *
 * The blink duration is DELAY_MS, with the COOLDOWN_MS pause before and after.
 * The LED returns to the status prior to this call. The blinking will always be
 * in the on state, if the LED was on prior to this call it will turn off
 * briefly to make the blink visible.
 *
 * Please note the slight delay from calling this method and the actual blinking
 * of the LED!
 */
void led_blink_once();

#endif /* _STATUS_LED_H_ */
