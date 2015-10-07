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

  for(int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      address = width * y + x;
      output->data[address].g = input->data[address].g;
      output->data[address].r = input->data[address].r;
      output->data[address].b = input->data[address].b;
    }
  }
}

