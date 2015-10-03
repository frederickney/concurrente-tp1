/****************************************************************************\
 * @brief System and CLI utilities
\****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "utils.h"

bool parse_int (int *value, const char *str)
{
  const char *c = str;
  // move `c` to the first non-digit char
  for (c = str; '0' <= *c && *c <= '9'; c++)
    ;

  // if `*c` is non-null (then not the last) or `c` is the first char then the
  // string is not positive integer
  if (*c || c == str)
    return false;

  // then parse the string
  *value = atoi(str);
  return true;
}

int sys_get_cpu_count (void)
{
  return sysconf(_SC_NPROCESSORS_ONLN);
}

bool file_exists (const char *filename) {
  struct stat buffer;
  return (stat(filename, &buffer) == 0);
}
