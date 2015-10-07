#include <criterion/criterion.h>

#include "utils.h"
#include "filters.h"
#include "convolution.h"

Test(conv_filter, filter_get) {
  float kernel[] = {
    0.0, 1.0, 2.0,
    3.0, 4.0, 5.0,
    6.0, 7.0, 8.0
  };
  filter_t filter = {
    .name = "test",
    .dim = 3,
    .kernel = kernel
  };

  cr_assert_eq(filter_get(&filter, 0, 1), 1.0,
      "Get element row=0, column=1, expected to be 1.0.");

  cr_assert_eq(filter_get(&filter, 2, 0), 6.0,
      "Get element row=2, column=0, expected to be 6.0.");
}

Test(conv_utils, parse_int) {
  int value;
  bool state;

  state = parse_int(&value, "");
  cr_assert_not(state,
      "Parsing empty string must fail.");

  state = parse_int(&value, "12ss");
  cr_assert_not(state,
      "Parsing string containing non-digit char must fail. (case 1)");

  state = parse_int(&value, "a12");
  cr_assert_not(state,
      "Parsing string containing non-digit char must fail. (case 2)");

  state = parse_int(&value, "12");
  cr_assert(state);
  cr_assert_eq(value, 12);
}

Test(con_convolution, clamp) {
  int result;

  result = clamp(12, 0, 100);
  cr_assert_eq(result, 12);

  result = clamp(-1, 0, 100);
  cr_assert_eq(result, 0);

  result = clamp(104, 0, 100);
  cr_assert_eq(result, 100);

}