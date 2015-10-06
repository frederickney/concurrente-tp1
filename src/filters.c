/****************************************************************************\
 * @brief Filters definitions
\****************************************************************************/

#include "filters.h"

#include <string.h>

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
  0, -1, 0,
  -1, 5, -1,
  0, -1, 0
};
/*
 * Global constant for the blur filter
 */
const float BLUR_KERNEL[] = { [0 ... 8] = 1.0 / 9.0 };
/*
 * Global constant for the edge filter
 */
const float EDGE_KERNEL[]] = {
  -1, -1, -1,
  -1, 8, -1,
  -1, -1, -1
};
/*
 * Global constant for the gauss filter
 */
const float UNDIV = 256.0; // unsigned dividend value
const float GAUSS_KERNEL[] = {
  1.0 / UNDIV, 4.0 / UNDIV, 6.0 / UNDIV, 4.0 / UNDIV, 1.0 / UNDIV,
  4.0 / UNDIV, 16.0 / UNDIV, 24.0 / UNDIV, 16.0 / UNDIV, 4.0 / UNDIV,
  16.0 / UNDIV, 24.0 / UNDIV, 36.0 / UNDIV, 24.0 / UNDIV, 16.0 / UNDIV,
  4.0 / UNDIV, 16.0 / UNDIV, 24.0 / UNDIV, 16.0 / UNDIV, 4.0 / UNDIV,
  1.0 / UNDIV, 4.0 / UNDIV, 6.0 / UNDIV, 4.0 / UNDIV, 1.0 / UNDIV
};
/*
 * Global constant for the unsharp filter
 */
float DIV = -256.0;
int UNSHARP_KERNEL[] = {
  1.0 / DIV, 4.0 / DIV, 6.0 / DIV, 4.0 / DIV, 1.0 / DIV,
  4.0 / DIV, 16.0 / DIV, 24.0 / DIV, 16.0 / DIV, 4.0 / DIV,
  16.0 / DIV, 24.0 / DIV, 36.0 / DIV, 24.0 / DIV, 16.0 / DIV,
  4.0 / DIV, 16.0 / DIV, 24.0 / DIV, 16.0 / DIV, 4.0 / DIV,
  1.0 / DIV, 4.0 / DIV, 6.0 / DIV, 4.0 / DIV, 1.0 / DIV
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
}

const filter_t BLUR_FILTER = {
  .name = "blur",
  .dim = 3,
  .kernel = BLUR_KERNEL
}

const filter_t EDGE_FILTER = {
  .name = "edge",
  .dim = 3,
  .kernel = EDGE_KERNEL
}

const filter_t GAUSS_FILTER = {
  .name = "gauss",
  .dim = 5,
  .kernel = GAUSS_KERNEL
}

const filter_t UNSHARP_FILTER = {
  .name = "unsharp",
  .dim = 5,
  .kernel = UNSHARP_KERNEL
}

const filter_t *filters_get_by_name(const char *name)
{
  if (strcmp(name, IDENTITY_FILTER->name) == 0)
      return &IDENTITY_FILTER;
  else if (strcmp(name, SHARPEN_FILTER->name) == 0)
    return &SHARPEN_FILTER;
  else if (strcmp(name, BLUR_FILTER->name) == 0)
    return &BLUR_FILTER;
  else if (strcmp(name, EDGE_FILTER->name) == 0)
    return &EDGE_FILTER;
  else if (strcmp(name, GAUSS_FILTER->name) == 0)
    return &GAUSS_FILTER;
  else if (strcmp(name, UNSHARP_FILTER->name) == 0)
    return &UNSHARP_FILTER;
  else
    return NULL;
}
