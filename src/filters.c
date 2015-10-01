/****************************************************************************\
 * @brief Filters definitions
\****************************************************************************/

#include "filters.h"

const float IDENTITY_KERNEL[] = {
  0, 0, 0,
  0, 1, 0,
  0, 0, 0
};
const filter_t IDENTITY_FILTER = { 3, IDENTITY_KERNEL };

