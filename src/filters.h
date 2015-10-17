/****************************************************************************\
 * @brief Filters definitions and utilities
\****************************************************************************/
#ifndef FILTERS_H
#define FILTERS_H

/**
 * type define for the structure which will contain filter
 */
typedef struct {
  const char *name;    // Filter's name
  const short dim;     // Filter's dimension
  const float *kernel; // Filter's kernel as an array of dim×dim floats
} filter_t;

/**
 * @brief Retrieve the coefficient of the kernel of the specfied filter
 *
 * @param filter Pointer to filter structure
 * @param x X-coordinate of the coefficient
 * @param y Y-coordinate of the coefficient
 *
 * @return Requested coefficient
 */
#define filter_get(filter, x, y) ((filter)->kernel[((x) * (filter)->dim) + (y)])

/**
 * @brief Get the filter by the specified name.
 *
 * @param name Filter's name
 *
 * @return The requested filter if exists, or NULL
 */
const filter_t *filters_get_by_name(const char *name);

/**
 * @brief Display the list of the available filter with the specified format.
 *
 * @param format A formating string containing a `%s` placeholder.
 */
void filters_display (const char *format);
#endif // FILTERS_H
