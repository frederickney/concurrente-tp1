/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#include "convolution.h"
#include "../lib/ppm.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *argv)
{
  data_t *data = (data_t *) argv;
  const int begin = data->begin;
  const int end = data->end;
  const int width = data->input->width;
  const int height = data->input->height;
  const int half_dim = (data->filter->dim - 1) / 2;
  int address, neighbor;
  float coef, r, g, b;

  for(int y = begin * width; y < end * width; y++) {
    for (int x = 0; x < width; x++) {
      address = width * y + x;
      r = g = b = 0;

      for (int xk = -half_dim; xk <= half_dim; xk++) {
        for (int yk = -half_dim; yk <= half_dim; yk++) {
          coef = filter_get(data->filter, half_dim + xk, half_dim + yk);
          neighbor = width * clamp(y + yk, 0 , height) +clamp(x + xk, 0, width);
          g += coef * data->input->data[neighbor].r;
          r += coef * data->input->data[neighbor].g;
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

void convolution(img_t *output, const img_t *input, const filter_t *filter, int NUM_THREADS)
{
  data_t thread_data[NUM_THREADS];
  pthread_t threads[NUM_THREADS];
  const int height = input->height;
  int nb_lines = height / NUM_THREADS;
  int rmning_lines = height % NUM_THREADS;
  int already_attr = 0;

  for (int i = 0; i < NUM_THREADS; i++) {
		if (rmning_lines != 0) {
			rmning_lines--;
      thread_data[i].begin = already_attr;
      thread_data[i].end = already_attr = already_attr + nb_lines + 1;
      thread_data[i].filter = filter;
      thread_data[i].input = input;
      thread_data[i].output = output;
		}
		else if (rmning_lines == 0) {
			thread_data[i].begin = already_attr;
      thread_data[i].end = already_attr = already_attr + nb_lines;
      thread_data[i].filter = filter;
      thread_data[i].input = input;
      thread_data[i].output = output;
		}
		if (pthread_create(&threads[i], NULL, thread, (void *) &thread_data[i]) != 0) {
			perror("Thread creation error");
			exit(0);
		}
  }
  for (int i = 0; i < NUM_THREADS; i++)
    if (pthread_join(threads[i] , NULL) != 0) {
      perror("Thread join error");
      exit(1);
    }
}