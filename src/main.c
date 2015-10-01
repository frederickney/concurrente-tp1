/****************************************************************************\
 * @brief Main function and CLI utilities
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../lib/ppm.h"

#include "filters.h"
#include "convolution.h"


const char *USAGE =
  "%s <filter> <thread number> <input file> <outputfile>\n"
  "\n"
  "Available filters:\n";

/**
 *
 */
void show_usage (char *cmd_name)
{
  printf(USAGE, cmd_name);
}

/**
 *
 */
int main (int argc, char **argv)
{
  img_t *input_img;
  img_t *output_img;

  if (argc != 5) {
    show_usage(argv[0]);
    return EXIT_FAILURE;
  }

  input_img = load_ppm(argv[3]);
  output_img = alloc_img(input_img->width, input_img->height);

  for (int i = 0; i < IDENTITY_FILTER.dim; i++) {
    for (int j = 0; j < IDENTITY_FILTER.dim; j++)
      printf("%f ", filter_elem(IDENTITY_FILTER, i, j));
    putchar('\n');
  }

  convolution(output_img, input_img, IDENTITY_FILTER);

  write_ppm(argv[4], output_img);
  free_img(input_img);
  free_img(output_img);
}
