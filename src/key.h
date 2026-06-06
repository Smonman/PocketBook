/**
 * @file key.h
 * @brief key functionality
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#ifndef _KEY_H_
#define _KEY_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Next key
 */
extern const uint8_t KEY_NEXT;

/**
 * @brief Back key
 */
extern const uint8_t KEY_BACK;

/**
 * @brief Power key
 */
extern const uint8_t KEY_POWER;

/**
 * @brief Initializes the key functionality.
 *
 * This function has to be called before the setup function.
 *
 * @see key_setup()
 * @return true on any error, false otherwise
 */
bool key_init();

/**
 * @brief Sets up the key functionality.
 *
 * This function must not be called prior to the init function.
 *
 * @see key_init()
 * @return true on any error, false otherwise
 */
bool key_setup();

/**
 * @brief Terminates the key functionality.
 *
 * Must not be called prior to the init or setup functions.
 * @see key_init()
 * @see key_setup()
 * @return true on any error, false otherwise
 */
bool key_terminate();

/**
 * @brief Returns whether the given key is currently pressed.
 *
 * @param key the key to query for. Is undefined behavior if the key is not one
 * of the KEY_* constents defined in the header file.
 * @return true, if the given key is currently pressed, false otherwise.
 */
bool key_pressed(const uint8_t key);

#endif /* _KEY_H_ */
