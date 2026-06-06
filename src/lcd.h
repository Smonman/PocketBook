/**
 * @file lcd.h
 * @brief LCD screen control functionality
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#ifndef _LCD_H_
#define _LCD_H_

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Initializes the LCD functionality.
 *
 * This function initializes the LCD screen. After a call to this function, the
 * screen is accessible.
 *
 * This function has to be called before the setup function.
 * @see lcd_setup()
 * @return true on any error, false otherwise
 */
bool lcd_init();

/**
 * @brief Sets up the LCD functionality.
 *
 * This function must not be called prior to the init function.
 * @see lcd_init()
 * @return true on any error, false otherwise
 */
bool lcd_setup();

/**
 * @brief Terminates the LCD functionality.
 *
 * This function must not be called prior to the init or setup functions.
 * @see lcd_init()
 * @see lcd_setup()
 * @return true on any error, false otherwise
 */
bool lcd_terminate();

/**
 * @brief Draws the main word screen.
 *
 * This function draws the main word screen on the LCD. The word screen consists
 * of a box with a crosshair where the word will be placed, as well as button
 * labels. This does not include the word in the box!
 *
 * This function must not be called prior to the setup function.
 * @see lcd_setup()
 * @return true on any error, false otherwise
 */
bool lcd_draw_word_screen();

/**
 * @brief Draws the word.
 *
 * This function draws the actual word to the screen. This function should be
 * called after a call to lcd_draw_word_screen() to draw the word into the box.
 * This function can be called with different words without having to call
 * lcd_draw_word_screen() again, if just the word should change. Prior to
 * drawing the word, the affected region will be cleared.
 *
 * If the word length is larger than the size of the box, the word will be
 * drawn on top of the box and not cleared afterward. If that happends, call
 * lcd_draw_word_screen() again, to reset the background.
 *
 * @param word a pointer to the begining of the word to be drawn. The string
 * does not have to be NUL-terminated
 * @param length the length of the string. Must not be negative
 * @return true on any error, false otherwise
 */
bool lcd_draw_word(const char *word, const size_t length);

/**
 * @brief Draws the debug screen.
 *
 * The debug screen consists of 5 anchor points, one for each corner, as well as
 * the center. Also, a red rectangle shows the bounds of the screen.
 *
 * @return true on any error, false otherwise
 */
bool lcd_draw_debug_screen();

#endif /* _LCD_H_ */
