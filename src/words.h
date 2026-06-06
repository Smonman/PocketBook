/**
 * @file words.h
 * @brief Words functionality
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#ifndef _WORDS_H_
#define _WORDS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes the words functionality.
 *
 * This function has to be called before the setup function.
 * @see words_setup
 * @return true on any error, false otherwise
 */
bool words_init();

/**
 * @brief Sets up the words functionality.
 *
 * This function must not be called prior to the init function. The word counter
 * stored on the flash memory will be loaded into the given location.
 * @see words_init()
 * @param counter a pointer to the word counter
 * @return true on any error, false otherwise
 */
bool words_setup(uint32_t *counter);

/**
 * @brief Terminates the words functionality.
 *
 * This function persists the given word counter's value.
 *
 * This function must not be called prior to the init or setup function.
 * @see words_init()
 * @see words_setup()
 * @param counter a pointer to the word counter
 * @return true on any error, false otherwise
 */
bool words_terminate(uint32_t *counter);

/**
 * @brief Gets the word at the given index.
 *
 * Gets the word from the content at the index given by the counter.
 *
 * @see content.h
 * @param counter the word counter that acts as an index in this case
 * @param dest a pointer that points to the start of the queried word
 * @param length a pointer that is filled with the length of the new word
 * @return true on any error, false otherwise
 */
bool words_get(const uint32_t counter, const char **dest, size_t *length);

#endif /* _WORDS_H_ */
