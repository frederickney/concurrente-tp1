/****************************************************************************\
 * @brief Filters definitions
\****************************************************************************/

#include "filters.h"

#include <string.h>

/*
 * Global constant for the identity filter
 */
const int IDENTITY_SIZE = 3;
const float IDENTITY_KERNEL[IDENTITY_SIZE][IDENTITY_SIZE] = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0} };
/*
 * Global constant for the sharpen filter
 */
const int SHARPEN_SIZE = 3;
const float SHARPEN_KERNEL[SHARPEN_SIZE][SHARPEN_SIZE] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };
/*
 * Global constant for the blur filter
 */
const int BLUR_SIZE = 3;
const float BLUR_KERNEL[BLUR_SIZE][BLUR_SIZE] = { [0 ... 2][0 ... 2] = ((float) 1) / ((float) 9) };
/*
 * Global constant for the edge filter
 */
const int EDGE_SIZE = 3;
const float EDGE_KERNEL[EDGE_SIZE][EDGE_SIZE] = { {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1} };
/*
 * Global constant for the gauss filter
 */
const float UNDIV = 256; // unsigned dividend value
const int GAUSS_SIZE = 5;
const float GAUSS_KERNEL[gauss_size][gauss_size] = {
  {((float) 1) / UNDIV, ((float) 4) / UNDIV, ((float) 6) / UNDIV, ((float) 4) / UNDIV, ((float) 1) / UNDIV},
  {((float) 4) / UNDIV, ((float) 16) / UNDIV, ((float) 24) / UNDIV, ((float) 16) / UNDIV, ((float) 4) / UNDIV},
  {((float) 16) / UNDIV, ((float) 24) / UNDIV, ((float) 36) / UNDIV, ((float) 24) / UNDIV, ((float) 16) / UNDIV},
  {((float) 4) / UNDIV, ((float) 16) / UNDIV, ((float) 24) / UNDIV, ((float) 16) / UNDIV, ((float) 4) / UNDIV},
  {((float) 1) / UNDIV, ((float) 4) / UNDIV, ((float) 6) / UNDIV, ((float) 4) / UNDIV, ((float) 1) / UNDIV}
};
/*
 * Global constant for the unsharp filter
 */
float DIV = -256;
int UNSHARP_SIZE = 5;
int UNSHARP_KERNEL[UNSHARP_SIZE][UNSHARP_SIZE] = {
  {((float) 1) / DIV, ((float) 4) / DIV, ((float) 6) / DIV, ((float) 4) / DIV, ((float) 1) / DIV},
  {((float) 4) / DIV, ((float) 16) / DIV, ((float) 24) / DIV, ((float) 16) / DIV, ((float) 4) / DIV},
  {((float) 16) / DIV, ((float) 24) / DIV, ((float) 36) / DIV, ((float) 24) / DIV, ((float) 16) / DIV},
  {((float) 4) / DIV, ((float) 16) / DIV, ((float) 24) / DIV, ((float) 16) / DIV, ((float) 4) / DIV},
  {((float) 1) / DIV, ((float) 4) / DIV, ((float) 6) / DIV, ((float) 4) / DIV, ((float) 1) / DIV}
};
/*
const float IDENTITY_KERNEL[] = {
  0, 0, 0,
  0, 1, 0,
  0, 0, 0
};
const filter_t IDENTITY_FILTER = {
  .name = "identity",
  .dim = 3,
  .kernel = IDENTITY_KERNEL
};*/

const filter_t *filters_get_by_name(const char *name)
{
  if (strcmp(name, "identity") == 0)
    {
      filter_t IDENTITY_FILTER;
      IDENTITY_FILTER->name = name;
      IDENTITY_FILTER->dim = IDENTITY_SIZE;
      IDENTITY_FILTER->kernel = &IDENTITY_KERNEL;
      return &IDENTITY_FILTER;
    }
    else if (strcmp(name, "sharpen") == 0)
    {
      filter_t SHARPEN_FILTER;
      SHARPEN_FILTER->name = name;
      SHARPEN_FILTER->dim = SHARPEN_SIZE;
      SHARPEN_FILTER->kernel = &SHARPEN_KERNEL;
      return &SHARPEN_FILTER;
    }
    else if (strcmp(name, "blur") == 0)
    {
      filter_t BLUR_FILTER;
      BLUR_FILTER->name = name;
      BLUR_FILTER->dim = BLUR_SIZE;
      BLUR_FILTER->kernel = &BLUR_KERNEL;
      return &BLUR_FILTER;
    }
    else if (strcmp(name, "edge") == 0)
    {
      filter_t EDGE_FILTER;
      EDGE_FILTER->name = name;
      EDGE_FILTER->dim = EDGE_SIZE;
      EDGE_FILTER->kernel = &EDGE_KERNEL;
      return &EDGE_FILTER;
    }
    else if (strcmp(name, "gauss") == 0)
    {
      filter_t GAUSS_FILTER;
      GAUSS_FILTER->name = name;
      GAUSS_FILTER->dim = GAUSS_SIZE;
      GAUSS_FILTER->kernel = &GAUSS_KERNEL;
      return &GAUSS_FILTER;
    }
    else if (strcmp(name, "unsharp") == 0)
    {
      filter_t UNSHARP_FILTER;
      UNSHARP_FILTER->name = name;
      UNSHARP_FILTER->dim = UNSHARP_SIZE;
      UNSHARP_FILTER->kernel = &UNSHARP_KERNEL;
      return &UNSHARP_FILTER;
    }
  else
    return NULL;
}
