/****************************************************************************\
 * @brief Main function and CLI utilities
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/ppm.h"

#include "utils.h"
#include "filters.h"
#include "convolution.h"


const char *USAGE =
  "usage:\n"
  "%s <filter> <thread number> <input file> <output file>\n";

const char *AVAILABLE_FILTERS =
  "  Available filters:\n"
  "   - identity\n";

/**
 * Display the usage header and the list of available filters
 *
 * @param cmd_name  The executable name
 */
void display_usage (char *cmd_name)
{
  printf(USAGE, cmd_name);
  printf("\n%s", AVAILABLE_FILTERS);
}

/**
 *
 */
int main (int argc, char **argv)
{
  char *cmd_name = argv[0];
  char *filter_name;
  char *threads_arg;
  char *input_filename;
  char *output_filename;

  const filter_t *filter;

  int threads;

  img_t *input_img;
  img_t *output_img;

  // Check the number of arguments
  if (argc != 5) {
    display_usage(cmd_name);
    return EXIT_FAILURE;
  }

  // Bind arguments to meaningful variables
  filter_name = argv[1];
  threads_arg = argv[2];
  input_filename = argv[3];
  output_filename = argv[4];

  // Try to retrieve the specified filter
  filter = filters_get_by_name(filter_name);
  if (filter == NULL) {
    printf("ERROR: Filter '%s' is not available.\n", filter_name);
    printf("\n%s", AVAILABLE_FILTERS);
    return EXIT_FAILURE;
  }

  // If the thread argument is "auto" use the number of available CPUs as number
  // of threads
  if (strcmp(threads_arg, "auto") == 0) {
    threads = sys_get_cpu_count();
    printf("info: %d threads\n", threads);
  // Otherwise try to parse the string to get a positive integer
  } else if (!parse_int(&threads, threads_arg) || threads < 1) {
    printf("ERROR: <thread number> must be a strictly positive integer "
           "or 'auto'.\n");
    return EXIT_FAILURE;
  }

  // Ensure that the input file and the output file are separate files
  if (strcmp(input_filename, output_filename) == 0) {
    printf("ERROR: The ouput file is the same as the input file.\n"
           "       Data loss could occur.\n");
    return EXIT_FAILURE;
  }

  // Check whether the input file exists
  if (!file_exists(input_filename)) {
    printf("ERROR: File '%s' not found.\n", input_filename);
    return EXIT_FAILURE;
  }

  // Load the input PPM file into memory
  input_img = load_ppm(input_filename);

  // Allocate memory for the output file
  output_img = alloc_img(input_img->width, input_img->height);

  // Produce the output file by applying the specified filter on the input file
  convolution(output_img, input_img, filter, threads);

  // Write the output file to the file system
  write_ppm(output_filename, output_img);

  // Free memory
  free_img(input_img);
  free_img(output_img);
}
