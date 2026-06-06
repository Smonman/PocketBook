/**
 * @file content.h
 * @brief The content to be displayed
 * @author Simon Josef Kreuzpointner
 * @date 2026-06-06
 */

#ifndef _CONTENT_H_
#define _CONTENT_H_

#include <stdlib.h>

/**
 * @brief Raw content to be displayed.
 *
 * The content is an ASCII string where each word or token is terminated by a
 * new line character \\n.
 */
extern const char content[];

/**
 * @brief The size of the content string.
 */
extern const size_t content_length;

#endif /* _CONTENT_H_ */
