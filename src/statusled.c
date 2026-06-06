#include "statusled.h"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "log.h"

#define STATUS_PIN CYW43_WL_GPIO_LED_PIN

static void led_blink_from_on();
static void led_blink_from_off();

void led_on()
{
	LOG_TRACE("\n");
	cyw43_arch_gpio_put(STATUS_PIN, 1);
}

void led_off()
{
	LOG_TRACE("\n");
	cyw43_arch_gpio_put(STATUS_PIN, 0);
}

void led_blink_once()
{
	LOG_TRACE("\n");
	bool current_status = cyw43_arch_gpio_get(STATUS_PIN);
	if (current_status)
	{
		led_blink_from_on();
	}
	else
	{
		led_blink_from_off();
	}
}

static void led_blink_from_on()
{
	LOG_TRACE("\n");
	led_off();
	led_blink_from_off();
	led_on();
}

static void led_blink_from_off()
{
	LOG_TRACE("\n");
	sleep_ms(COOLDOWN_MS);
	led_on();
	sleep_ms(DELAY_MS);
	led_off();
	sleep_ms(COOLDOWN_MS);
}
