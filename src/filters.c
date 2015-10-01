/****************************************************************************\
 * @brief Filters definitions
\****************************************************************************/

#include "filters.h"

#include <string.h>

const float IDENTITY_KERNEL[] = {
  0, 0, 0,
  0, 1, 0,
  0, 0, 0
};
const filter_t IDENTITY_FILTER = {
  .name = "identity",
  .dim = 3,
  .kernel = IDENTITY_KERNEL
};

const filter_t *get_filter(const char *name)
{
  if (strcmp(name, "identity") == 0)
    return &IDENTITY_FILTER;
  else
    return NULL;
}
