/****************************************************************************\
 * @brief Main function and CLI utilities
\****************************************************************************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/ppm.h"

#include "utils.h"
#include "filters.h"
#include "convolution.h"

/**
 * @brief Usage message.
 *
 * Must be used as an printf format string with the program
 * name 
 */
const char *USAGE =
  "usage:\n"
  "%s <filter> <thread number> <input file> <output file>\n";

/**
 * @brief Display the usage header and the list of available filters
 *
 * @param cmd_name  The executable name
 */
void display_usage (char *cmd_name)
{
  printf(USAGE, cmd_name);
  printf("  Available filters:\n");
  filters_display("   - %s\n");
}

/**
 * @brief Program entry point.
 */
int main (int argc, char **argv)
{
  // Arguments 
  char *cmd_name = argv[0];
  char *filter_name;
  char *threads_arg;
  char *input_filename;
  char *output_filename;

  const filter_t *filter;

  int threads;

  // Images
  img_t *input_img;
  img_t *output_img;

  // Timing vars
  struct timespec start, finish;
  double elapsed_ms;

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
    filters_display("   - %s\n");
    return EXIT_FAILURE;
  }

  // If the thread argument is "auto" use the number of available CPUs as number
  // of threads
  if (strcmp(threads_arg, "auto") == 0) {
    threads = sys_get_cpu_count();
  // Otherwise try to parse the string to get a positive integer
  } else if (!parse_int(&threads, threads_arg) || threads < 1) {
    printf("ERROR: <thread number> must be a strictly positive integer "
           "or 'auto'.\n");
    return EXIT_FAILURE;
  }
  printf("info: %d threads\n", threads);

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
  if (input_img == NULL) {
    printf("ERROR: The input file is not a valid PPM P3 file.\n");
    return EXIT_FAILURE;
  }

  // Allocate memory for the output file
  output_img = alloc_img(input_img->width, input_img->height);

  // Get start time
  clock_gettime(CLOCK_MONOTONIC, &start);

  // Produce the output image by applying the specified filter on the input image
  convolution(output_img, input_img, filter, threads);

  // Get end time
  clock_gettime(CLOCK_MONOTONIC, &finish);

  // Computed elapsed time in ms
  elapsed_ms = 1000 * (finish.tv_sec - start.tv_sec);
  elapsed_ms += (finish.tv_nsec - start.tv_nsec) / 1000000.0;

  // Display elapsed time
  printf("convolution time: %fms\n", elapsed_ms);

  // Write the output file to the file system
  write_ppm(output_filename, output_img);

  // Free memory
  free_img(input_img);
  free_img(output_img);
}
