/****************************************************************************\
 * @brief Convolution's computation and parallelization
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "convolution.h"

void *thread(void *args)
{
  data_t *data = (data_t *) args;
  const int begin = data->begin;
  const int end = data->end;
  const int width = data->input->width;
  const int height = data->input->height;
  const int half_dim = (data->filter->dim - 1) / 2;
  int address, neighbor;
  float coef, r, g, b;

  for(int y = begin; y < end; y++) {
    for (int x = 0; x < width; x++) {
      address = width * y + x;
      r = g = b = 0;

      for (int xk = -half_dim; xk <= half_dim; xk++) {
        for (int yk = -half_dim; yk <= half_dim; yk++) {
          coef = filter_get(data->filter, half_dim + xk, half_dim + yk);
          neighbor = width * clamp(y + yk, 0, height - 1) + clamp(x + xk, 0, width - 1);
          r += coef * data->input->data[neighbor].r;
          g += coef * data->input->data[neighbor].g;
          b += coef * data->input->data[neighbor].b;
        }
      }
      data->output->data[address].r = (uint8_t) clamp(r, 0, 255);
      data->output->data[address].g = (uint8_t) clamp(g, 0, 255);
      data->output->data[address].b = (uint8_t) clamp(b, 0, 255);
    }
  }
  return NULL;
}

void convolution(
  img_t *const output,
  const img_t *const input,
  const filter_t *const filter,
  const int num_threads
) {
  const int height = input->height;
  const int nb_lines = height / num_threads;
  const int rmning_lines = height % num_threads;

  // threads' arguments
  data_t thread_data[num_threads];
  // threads' references
  pthread_t threads[num_threads];

  int already_attr = 0;

  for (int i = 0; i < num_threads; i++) {
    thread_data[i].begin = already_attr;
    thread_data[i].end = already_attr + nb_lines;

    // dispatch remaining lines
    if (i < rmning_lines)
      thread_data[i].end++;

    already_attr = thread_data[i].end;

    thread_data[i].filter = filter;
    thread_data[i].input = input;
    thread_data[i].output = output;

    // create the thread
    if (pthread_create(&threads[i], NULL, thread, (void *) &thread_data[i]) != 0) {
      perror("Thread creation error");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i] , NULL) != 0) {
      perror("Thread join error");
      exit(EXIT_FAILURE);
    }
  }
}
