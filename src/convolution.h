/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "../lib/ppm.h"

#include "filters.h"

/**
 *
 */
void convolution (img_t *output, const img_t *input, const filter_t *filter);

#endif // CONVOLUTION_H
