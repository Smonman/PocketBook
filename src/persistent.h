/**
 * @file persistent.h
 * @brief Persistent data functionality
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#ifndef _PERSISTENT_H_
#define _PERSISTENT_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes the persistent functionality.
 *
 * This function initializes the file system and should thus be called as early
 * after the program entry as possible. This has to be called before the setup
 * function.
 * @see persistent_setup()
 * @return true on any error, false otherwise
 */
bool persistent_init();

/**
 * @brief Sets up the persistent functionality.
 *
 * This must not be called prior to the init function.
 * @see persistent_init()
 * @return true on any error, false otherwise
 */
bool persistent_setup();

/**
 * @brief Terminates the persistent functionality.
 *
 * This function terminates and closes the file system and its resources. After
 * a call to this function, the persistent functionality is no longer usable.
 *
 * Must not be called prior to the init or setup functions. This function must
 * be called before exiting the program to persist.
 * @see persistent_init()
 * @see persistent_setup()
 * @return true on any error, false otherwise
 */
bool persistent_terminate();

/**
 * @brief Gets the word count.
 *
 * Puts the word count into the destination. This function must not be called
 * prior to the setup function.
 * @see persistent_setup()
 * @param dest pointer to a uint32_t, where the word count should be put
 */
void get_word_count(uint32_t *dest);

/**
 * @brief Saves the word count.
 *
 * Saves the word count from the source. This function must not be called
 * prior to the setup function.
 * @see persistent_setup()
 * @param source pointer to a uint32_t, where the word count is
 */
void save_word_count(uint32_t *source);

#endif /* _PERSISTENT_H_ */
