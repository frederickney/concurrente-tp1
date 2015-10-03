#include <criterion/criterion.h>

#include "filters.h"

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

    cr_expect(filter_get(&filter, 0, 1) == 1.0,
              "Get element row=0, column=1, expected to be 1.0.");

    cr_expect(filter_get(&filter, 2, 0) == 6.0,
              "Get element row=2, column=0, expected to be 2.0.");
}
