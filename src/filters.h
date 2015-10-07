#ifndef FILTERS_H
#define FILTERS_H

/*
 * type define for the structure which will contain filter
 */
typedef struct {
  const char *name;
  const short dim;
  const float *kernel;
} filter_t;

#define filter_get(filter, x, y) ((filter)->kernel[((x) * (filter)->dim) + (y)])

const filter_t *filters_get_by_name(const char *name);
#endif // FILTERS_H

