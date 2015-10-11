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

typedef struct {
  int begin, end;
  const filter_t *filter;
  const img_t *input;
  img_t *output;
} data_t;

void convolution (img_t *output, const img_t *input, const filter_t *filter , int NUM_THREADS);
void threads (void * argv);
#endif // CONVOLUTION_H
