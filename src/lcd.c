#include "lcd.h"

#include <stdint.h>
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_2in.h"
#include "Debug.h"
#include "log.h"

#define PADDING_SCREEN 8

static UWORD *canvas;
static const uint8_t padding_box = 16;
static const uint8_t crosshair_length = padding_box / 2;
static const uint8_t font_height = 24;
static const uint8_t font_width = 17;

static void draw_button_names(const uint8_t padding_screen);
static void draw_word_box(const uint8_t padding_screen);
static void lcd_draw_string_view(UWORD Xstart, UWORD Ystart, const char *pString, const size_t length, sFONT *Font, UWORD Color_Foreground, UWORD Color_Background);

bool lcd_init()
{
	LOG_TRACE("\n");
	DEV_Delay_ms(100);
	if (DEV_Module_Init() != 0)
	{
		return true;
	}
	DEV_SET_PWM(25);
	LCD_2IN_Init(HORIZONTAL);
	LCD_2IN_Clear(BLACK);
	return false;
}

bool lcd_setup()
{
	LOG_TRACE("\n");
	if ((canvas = malloc(LCD_2IN_WIDTH * LCD_2IN_HEIGHT * 2)) == NULL)
	{
		return true;
	}
	Paint_NewImage((UBYTE *)canvas, LCD_2IN.WIDTH, LCD_2IN.HEIGHT, 90, BLACK);
	Paint_SetScale(65);
	Paint_Clear(BLACK);
}

bool lcd_terminate()
{
	LOG_TRACE("\n");
	DEV_SET_PWM(0);
	LCD_2IN_Clear(BLACK);
	free(canvas);
	canvas = NULL;
	DEV_Module_Exit();
	return false;
}

bool lcd_draw_word_screen()
{
	LOG_TRACE("\n");
	draw_button_names(PADDING_SCREEN);
	draw_word_box(PADDING_SCREEN);
	LCD_2IN_Display((UBYTE *)canvas);
	return false;
}

bool lcd_draw_word(const char *word, const size_t length)
{
	LOG_TRACE("@%p, %d\n", word, length);
	Paint_ClearWindows(
		PADDING_SCREEN + padding_box,
		LCD_2IN.WIDTH / 2 - (font_height / 2),
		LCD_2IN.HEIGHT - PADDING_SCREEN - padding_box,
		LCD_2IN.WIDTH / 2 + (font_height / 2),
		BLACK);
	lcd_draw_string_view(
		PADDING_SCREEN + padding_box,
		LCD_2IN.WIDTH / 2 - (font_height / 2),
		word,
		length,
		&Font24,
		WHITE,
		BLACK);
	LCD_2IN_Display((UBYTE *)canvas);
	return false;
}

static void draw_button_names(const uint8_t padding_screen)
{
	LOG_TRACE("%d", padding_screen);
	const uint8_t font_height = 12;
	const uint8_t font_width = 7;
	const uint16_t color = 0xb58a;

	// key 0
	Paint_DrawString_EN(
		padding_screen,
		padding_screen,
		"Previous",
		&Font12,
		color,
		BLACK);

	// key 1
	Paint_DrawString_EN(
		LCD_2IN.HEIGHT - 4 * font_width - padding_screen,
		padding_screen,
		"Next",
		&Font12,
		color,
		BLACK);

	// key 2
	Paint_DrawString_EN(
		padding_screen,
		LCD_2IN.WIDTH - font_height - padding_screen,
		"Power",
		&Font12,
		color,
		BLACK);

	// key 3
	Paint_DrawString_EN(
		LCD_2IN.HEIGHT - 0 * font_width - padding_screen,
		LCD_2IN.WIDTH - font_height - padding_screen,
		"",
		&Font12,
		color,
		BLACK);
}

static void draw_word_box(const uint8_t padding_screen)
{
	LOG_TRACE("%d\n", padding_screen);
	// word box
	Paint_DrawRectangle(
		padding_screen,
		LCD_2IN.WIDTH / 2 - (font_height / 2) - padding_box,
		LCD_2IN.HEIGHT - padding_screen,
		LCD_2IN.WIDTH / 2 + (font_height / 2) + padding_box,
		GRAY,
		1,
		LINE_STYLE_SOLID);
	// crosshair left
	Paint_DrawLine(
		padding_screen,
		LCD_2IN.WIDTH / 2,
		padding_screen + crosshair_length,
		LCD_2IN.WIDTH / 2,
		GRAY,
		1,
		LINE_STYLE_SOLID);
	// crosshair right
	Paint_DrawLine(
		LCD_2IN.HEIGHT - padding_screen,
		LCD_2IN.WIDTH / 2,
		LCD_2IN.HEIGHT - padding_screen - crosshair_length,
		LCD_2IN.WIDTH / 2,
		GRAY,
		1,
		LINE_STYLE_SOLID);
	// crosshair top
	Paint_DrawLine(
		padding_screen + padding_box + font_width + (font_width / 2),
		LCD_2IN.WIDTH / 2 - (font_height / 2) - padding_box,
		padding_screen + padding_box + font_width + (font_width / 2),
		LCD_2IN.WIDTH / 2 - (font_height / 2) - padding_box + crosshair_length,
		GRAY,
		1,
		LINE_STYLE_SOLID);
	// crosshair bottom
	Paint_DrawLine(
		padding_screen + padding_box + font_width + (font_width / 2),
		LCD_2IN.WIDTH / 2 + (font_height / 2) + padding_box,
		padding_screen + padding_box + font_width + (font_width / 2),
		LCD_2IN.WIDTH / 2 + (font_height / 2) + padding_box - crosshair_length,
		GRAY,
		1,
		LINE_STYLE_SOLID);
}

bool lcd_draw_debug_screen()
{
	LOG_TRACE("\n");
	Paint_Clear(BLACK);
	Paint_DrawString_EN(0, 0, "0, 0", &Font12, WHITE, BLACK);
	Paint_DrawString_EN(0, LCD_2IN.WIDTH, "0, W", &Font12, WHITE, BLACK);
	Paint_DrawString_EN(LCD_2IN.HEIGHT, 0, "H, 0", &Font12, WHITE, BLACK);
	Paint_DrawString_EN(LCD_2IN.HEIGHT, LCD_2IN.WIDTH, "H, W", &Font12, WHITE, BLACK);

	Paint_DrawString_EN(LCD_2IN.HEIGHT / 2, LCD_2IN.WIDTH / 2, "center", &Font12, WHITE, BLACK);
	Paint_DrawRectangle(1, 1, LCD_2IN.HEIGHT - 1, LCD_2IN.WIDTH - 1, RED, 1, DRAW_FILL_EMPTY);
	LCD_2IN_Display((UBYTE *)canvas);
}

static void lcd_draw_string_view(UWORD Xstart, UWORD Ystart, const char *pString, const size_t length, sFONT *Font, UWORD Color_Foreground, UWORD Color_Background)
{
	LOG_TRACE("%d, %d, @%p, %d, @%p, %d, %d\n", Xstart, Ystart, pString, length, Font, Color_Foreground, Color_Background);
	UWORD Xpoint = Xstart;
	UWORD Ypoint = Ystart;

	if (Xstart > Paint.Width || Ystart > Paint.Height)
	{
		return;
	}

	for (uint32_t i = 0; i < length; i++)
	{
		LOG_DEBUG("%c\n", *(pString + i));
		// if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the Height of the character
		if ((Xpoint + Font->Width) > Paint.Width)
		{
			Xpoint = Xstart;
			Ypoint += Font->Height;
		}

		// If the Y direction is full, reposition to(Xstart, Ystart)
		if ((Ypoint + Font->Height) > Paint.Height)
		{
			Xpoint = Xstart;
			Ypoint = Ystart;
		}
		Paint_DrawChar(Xpoint, Ypoint, *(pString + i), Font, Color_Background, Color_Foreground);

		// The next word of the abscissa increases the font of the broadband
		Xpoint += Font->Width;
	}
}