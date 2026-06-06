#include "words.h"

#include <stdio.h>
#include "content.h"
#include "persistent.h"
#include "log.h"

static uint32_t internal_counter;
static const char *start = NULL;
static const char *end = NULL;

static void get_content_line(const char **dest, size_t *length);
static void get_content_line_backwards(const char **dest, size_t *length);

bool words_init()
{
	LOG_TRACE("\n");
	return false;
}

bool words_setup(uint32_t *counter)
{
	LOG_TRACE("@%p\n", counter);
	get_word_count(counter);
	internal_counter = 0;
	start = content;
	return false;
}

bool words_terminate(uint32_t *counter)
{
	LOG_TRACE("@%p\n", counter);
	save_word_count(counter);
	return false;
}

bool words_get(const uint32_t counter, const char **dest, size_t *length)
{
	LOG_TRACE("%d, @%p, @%p\n", counter, dest, length);
	const int32_t diff = counter - internal_counter;
	const bool forwards = diff > 0;
	// https://stackoverflow.com/a/14612943/19116896
	const int8_t sign = (diff > 0) - (diff < 0);
	// skip next diff words either forwards or backwards
	for (int i = 0; i < abs(diff); i++)
	{
		if (forwards)
		{
			get_content_line(dest, length);
		}
		else
		{
			get_content_line_backwards(dest, length);
		}
		internal_counter += sign;
	}
	return false;
}

static void get_content_line(const char **dest, size_t *length)
{
	LOG_TRACE("@%p, @%p\n", dest, length);
	while (*start == '\n' && *start != '\0')
	{
		start++;
	}
	end = start;
	while (*end != '\n' && *end != '\0')
	{
		end++;
	}
	*dest = start;
	*length = end - start;
	while (*end == '\n' && *end != '\0')
	{
		end++;
	}
	start = end;
}

static void get_content_line_backwards(const char **dest, size_t *length)
{
	LOG_TRACE("@%p, @%p\n", dest, length);
	// move until current word start
	while (*start != '\n' && start != content - 1)
	{
		start--;
	}
	// move over line break
	while (*start == '\n' && start != content - 1)
	{
		start--;
	}
	// now, we are at the last character of the previous word
	end = start + 1;
	while (*start != '\n' && start != content - 1)
	{
		start--;
	}
	start++; // cut off the first character that we overshot
	*dest = start;
	*length = end - start;
	end = start;
}
