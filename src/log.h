/**
 * @file log.h
 * @brief simple logging macros
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 *
 * The logging is controlled by the definition DEBUG. It allows integer values
 * between 0 and 5, where 0 means no logging, and 5 means logging everything.
 *
 * The log-levels are:
 * 1. ERROR
 * 2. WARNING
 * 3. INFO
 * 4. DEBUG
 * 5. TRACE
 */

#ifndef _LOG_H_
#define _LOG_H_

#if defined(DEBUG) && DEBUG > 0
#include <stdio.h>
#define LOG(level, fmt, args...)                                                                    \
	do                                                                                              \
	{                                                                                               \
		(void)fprintf(stderr, "%s: %s:%d:%s(): " fmt, level, __FILE__, __LINE__, __func__, ##args); \
	} while (0)
#if DEBUG >= 5
#define LOG_TRACE(fmt, args...) LOG("TRACE  ", fmt, ##args)
#else
#define LOG_TRACE(fmt, args...)
#endif
#if DEBUG >= 4
#define LOG_DEBUG(fmt, args...) LOG("DEBUG  ", fmt, ##args)
#else
#define LOG_DEBUG(fmt, args...)
#endif
#if DEBUG >= 3
#define LOG_INFO(fmt, args...) LOG("INFO   ", fmt, ##args)
#else
#define LOG_INFO(fmt, args...)
#endif
#if DEBUG >= 2
#define LOG_WARN(fmt, args...) LOG("WARNING", fmt, ##args)
#else
#define LOG_WARN(fmt, args...)
#endif
#if DEBUG >= 1
#define LOG_ERROR(fmt, args...) LOG("ERROR  ", fmt, ##args)
#else
#define LOG_ERROR(fmt, args...)
#endif
#else
#define LOG_ERROR(fmt, args...)
#define LOG_WARN(fmt, args...)
#define LOG_INFO(fmt, args...)
#define LOG_DEBUG(fmt, args...)
#define LOG_TRACE(fmt, args...)
#endif

#endif /* _LOG_H_ */
