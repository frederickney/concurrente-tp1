/****************************************************************************\
 * @brief Filters definitions and utilities
\****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "filters.h"

/*
 * Global constant for the identity filter
 */
const float IDENTITY_KERNEL[] = {
  0, 0, 0,
  0, 1, 0,
  0, 0, 0
};

/*
 * Global constant for the sharpen filter
 */
const float SHARPEN_KERNEL[] = {
   0, -1,  0,
  -1,  5, -1,
   0, -1,  0
};

/*
 * Global constant for the blur filter
 */
const float BLUR_KERNEL[] = {
  1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
  1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
  1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0
};

/*
 * Global constant for the edge filter
 */
const float EDGE_KERNEL[] = {
  -1, -1, -1,
  -1,  8, -1,
  -1, -1, -1
};

/*
 * Global constant for the gauss filter
 */
const float GAUSS_KERNEL[] = {
   1.0 / 256.0,  4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0,
   4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0,  4.0 / 256.0,
  16.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0,
   4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0,  4.0 / 256.0,
   1.0 / 256.0,  4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0,  1.0 / 256.0
};

/*
 * Global constant for the unsharp filter
 */
const float UNSHARP_KERNEL[] = {
   1.0 / -256.0,  4.0 / -256.0,   6.0 / -256.0,  4.0 / -256.0,  1.0 / -256.0,
   4.0 / -256.0, 16.0 / -256.0,  24.0 / -256.0, 16.0 / -256.0,  4.0 / -256.0,
  16.0 / -256.0, 24.0 / -256.0, 476.0 /  256.0, 24.0 / -256.0, 16.0 / -256.0,
   4.0 / -256.0, 16.0 / -256.0,  24.0 / -256.0, 16.0 / -256.0,  4.0 / -256.0,
   1.0 / -256.0,  4.0 / -256.0,   6.0 / -256.0,  4.0 / -256.0,  1.0 / -256.0
};

const filter_t IDENTITY_FILTER = {
  .name = "identity",
  .dim = 3,
  .kernel = IDENTITY_KERNEL
};

const filter_t SHARPEN_FILTER = {
  .name = "sharpen",
  .dim = 3,
  .kernel = SHARPEN_KERNEL
};

const filter_t BLUR_FILTER = {
  .name = "blur",
  .dim = 3,
  .kernel = BLUR_KERNEL
};

const filter_t EDGE_FILTER = {
  .name = "edge",
  .dim = 3,
  .kernel = EDGE_KERNEL
};

const filter_t GAUSS_FILTER = {
  .name = "gauss",
  .dim = 5,
  .kernel = GAUSS_KERNEL
};

const filter_t UNSHARP_FILTER = {
  .name = "unsharp",
  .dim = 5,
  .kernel = UNSHARP_KERNEL
};

const filter_t *FILTERS[] = {
  &IDENTITY_FILTER,
  &SHARPEN_FILTER,
  &BLUR_FILTER,
  &EDGE_FILTER,
  &GAUSS_FILTER,
  &UNSHARP_FILTER,
  NULL // sentinel value
};

const filter_t *filters_get_by_name(const char *name)
{
  for (const filter_t **filter = FILTERS; *filter; filter++)
    if (strcmp(name, (*filter)->name) == 0)
      return *filter;

  return NULL;
}

void filters_display (const char *format)
{
  for (const filter_t **filter = FILTERS; *filter; filter++)
    printf(format, (*filter)->name);
}
