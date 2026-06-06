/**
 * @file PocketBook.h
 * @brief Displays a large string word by word on an LCD screen.
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "statusled.h"
#include "lcd.h"
#include "key.h"
#include "persistent.h"
#include "words.h"
#include "log.h"

#define PAUSE_MS 64

static uint32_t word_counter = 0;
static const char *word = NULL;
static size_t length = 0;

bool init();
bool setup();
bool update();
bool terminate();

/**
 * @brief Main entry point.
 *
 * @return EXIT_FAILURE on any error, EXIT_SUCCESS otherwise.
 */
int main()
{
    LOG_TRACE("");
    if (init())
    {
        return EXIT_FAILURE;
    }
    led_blink_once();
    if (setup())
    {
        return EXIT_FAILURE;
    }
    led_on();
    while (true)
    {
        if (update())
        {
            break;
        }
    }
    led_off();
    if (terminate())
    {
        return EXIT_FAILURE;
    }
    led_blink_once();
    LOG_INFO("shutting down...");
    return EXIT_SUCCESS;
}

/**
 * @brief Main initialization function.
 *
 * All required modules are initialized here.
 *
 * @return true on any error, false otherwise.
 */
bool init()
{
    LOG_TRACE("\n");
    stdio_init_all();
    // initialize the Wi-Fi chip
    if (cyw43_arch_init())
    {
        return true;
    }
    if (persistent_init())
    {
        return true;
    }
    // Must be after persistent_init, as the words functionality requires the fs
    if (words_init())
    {
        return true;
    }
    if (lcd_init())
    {
        return true;
    }
    // Must be after lcd_init, as the keys are on the same module as the LCD
    // screen
    if (key_init())
    {
        return true;
    }
    return false;
}

/**
 * @brief Main set up function.
 *
 * All required modules are set up here.
 *
 * @return true on any error, false otherwise.
 */
bool setup()
{
    LOG_TRACE("\n");
    if (persistent_setup())
    {
        return true;
    }
    if (words_setup(&word_counter))
    {
        return true;
    }
    if (lcd_setup())
    {
        return true;
    }
    if (key_setup())
    {
        return true;
    }
    lcd_draw_word_screen();
    return false;
}

/**
 * @brief One update cycle of the main loop.
 *
 * @return true if the loop should be escaped, false otherwise.
 */
bool update()
{
    LOG_TRACE("\n");
    bool isDirty = false;
    if (key_pressed(KEY_POWER))
    {
        LOG_INFO("power key pressed\n");
        return true;
    }
    if (key_pressed(KEY_NEXT))
    {
        LOG_INFO("next key pressed\n");
        word_counter++;
        isDirty = true;
    }
    else if (key_pressed(KEY_BACK))
    {
        LOG_INFO("back key pressed\n");
        word_counter--;
        isDirty = true;
    }

    if (isDirty)
    {
        // get word
        words_get(word_counter, &word, &length);
        // display word
        lcd_draw_word(word, length);
    }

    sleep_ms(PAUSE_MS);
    return false;
}

/**
 * @brief Main termination function.
 *
 * All required modules are terminated up here.
 *
 * @return true on any error, false otherwise.
 */
bool terminate()
{
    LOG_TRACE("\n");
    bool error = false;
    if (key_terminate())
    {
        LOG_ERROR("could not terminate key");
        error = true;
    }
    if (lcd_terminate())
    {
        LOG_ERROR("could not terminate lcd");
        error = true;
    }
    if (words_terminate(&word_counter))
    {
        LOG_ERROR("could not terminate words");
        error = true;
    }
    if (persistent_terminate())
    {
        LOG_ERROR("could not terminate persistent");
        error = true;
    }
    return error;
}
