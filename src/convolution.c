/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#include "convolution.h"
#include "../lib/ppm.h"

void convolution(img_t *output, const img_t *input, const filter_t *filter, int threads)
{
  int width = input->width;
  int height =  input->height;
  int address;
  int half_dim = (filter->dim-1)/2;
  int neighbor;
  float coef;
  float r, g, b;

  for(int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      address = width * y + x;
      r = g = b = 0;

      for (int xk = -half_dim; xk <= half_dim; xk++){
        for (int yk = -half_dim; yk <= half_dim; yk++)
        {
          coef = filter_get(filter, half_dim + xk, half_dim + yk);
          neighbor = width * clamp(y + yk, 0 , height) +clamp(x + xk, 0, width);
          g += coef * input->data[neighbor].g;
          r += coef * input->data[neighbor].r;
          b += coef * input->data[neighbor].b;
        }
      }

      output->data[address].r = (uint8_t) clamp(r, 0, 255);
      output->data[address].g = (uint8_t) clamp(g, 0, 255);
      output->data[address].b = (uint8_t) clamp(b, 0, 255);
    }
  }
}