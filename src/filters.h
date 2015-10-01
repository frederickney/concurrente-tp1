#ifndef FILTERS_H
#define FILTERS_H

/**
 *
 */
typedef struct {
  const char *name;
  const short dim;
  const float *kernel; 
} filter_t;

#define filter_elem(filter, x, y) (filter->kernel[(x) + ((y) * filter->dim)])

const filter_t *get_filter(const char *name);
#endif // FILTERS_H

