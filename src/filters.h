#ifndef FILTERS_H
#define FILTERS_H

/**
 *
 */
typedef struct {
  const short dim;
  const float *kernel; 
} filter_t;

extern const filter_t IDENTITY_FILTER;

#define filter_elem(filter, x, y) (filter.kernel[(x) + ((y) * filter.dim)])

filter_t *get_filter(const char*name);
#endif // FILTERS_H

