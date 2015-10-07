/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "../lib/ppm.h"

#include "filters.h"

#define clamp(x , min , max) (((min) < (x)) ? (((x) < (max)) ? (x) : (max)) : (min))

/**
 *
 */
void convolution (img_t *output, const img_t *input, const filter_t *filter , int threads);
#endif // CONVOLUTION_H
