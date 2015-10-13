/****************************************************************************\
 * @brief Convolution's computation and parallelization - header
\****************************************************************************/
#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "../lib/ppm.h"

#include "filters.h"

/**
 * @brief Restrict the `x` value to the given range `[min:max]`
 */
#define clamp(x, min, max) (((min) < (x)) ? (((x) < (max)) ? (x) : (max)) : (min))

/**
 * Thread's computation arguments
 */
typedef struct {
  int begin;              // First row to compute
  int end;                // Last row to compute
  const filter_t *filter; // Filter to apply
  const img_t *input;     // Input image
  img_t *output;          // Output image
} data_t;

/**
 * @brief Parallelize convolution's omputation.
 *
 * @param output Output image
 * @param input Input image
 * @param filter Fitler to apply
 * @param num_threads Number of threads to use
 */
void convolution (
  img_t *const output,
  const img_t *const input,
  const filter_t *const filter,
  const int num_threads
);

/**
 * @brief Compute the convolution on the specified image tile.
 *
 * @param args Computation arguments
 */
void *thread (void *args);
#endif // CONVOLUTION_H
