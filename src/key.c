#include "key.h"

#include <stdlib.h>
#include "DEV_Config.h"
#include "LCD_2in.h"
#include "Infrared.h"
#include "Debug.h"
#include "log.h"

const uint8_t KEY_NEXT = 17;
const uint8_t KEY_BACK = 15;
const uint8_t KEY_POWER = 3;

bool key_init()
{
	LOG_TRACE("\n");
	return false;
}

bool key_setup()
{
	LOG_TRACE("\n");
	LOG_DEBUG("next key: %d\n", KEY_NEXT);
	LOG_DEBUG("back key: %d\n", KEY_BACK);
	LOG_DEBUG("power key: %d\n", KEY_POWER);
	SET_Infrared_PIN(KEY_NEXT);
	SET_Infrared_PIN(KEY_BACK);
	SET_Infrared_PIN(KEY_POWER);
	return false;
}

bool key_terminate()
{
	LOG_TRACE("\n");
	return false;
}

bool key_pressed(const uint8_t key)
{
	LOG_TRACE("%d\n", key);
	return !(DEV_Digital_Read(key));
}