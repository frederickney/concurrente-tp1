#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * Try to parse an integer from string.
 *
 * @param value Room for the parsed integer
 * @param str String to parse
 *
 * @return Whether the string was successfuly parsed or not
 */
bool parse_int (int *value, const char *str);


/**
 * Get the number of available CPUs.
 *
 * @return The number of avalaible CPUs.
 */
int sys_get_cpu_count (void);

#endif // UTILS
