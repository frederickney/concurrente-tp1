#include <criterion/criterion.h>

#include <pthread.h>

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

Test(conv_convolution, clamp) {
  int result;

  result = clamp(12, 0, 100);
  cr_assert_eq(result, 12);

  result = clamp(-1, 0, 100);
  cr_assert_eq(result, 0);

  result = clamp(104, 0, 100);
  cr_assert_eq(result, 100);
}

Test(conv_convolution, thread) {
  const int WIDTH = 10, HEIGHT = 10;
  const filter_t *filter;
  img_t *input, *output;
  pthread_t mythread;

  data_t payload;

  int address;

  input = alloc_img(WIDTH, HEIGHT);
  output = alloc_img(WIDTH, HEIGHT);

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      address = x * WIDTH + y;
      input->data[address].r = address;
      input->data[address].g = address;
      input->data[address].b = address;
    }
  }

  filter = filters_get_by_name("identity");

  payload.begin = 0;
  payload.end = HEIGHT;
  payload.filter = filter;
  payload.input = input;
  payload.output = output;

  pthread_create(&mythread, NULL, thread, (void *) &payload);
  pthread_join(mythread, NULL);

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      address = x * WIDTH + y;
      cr_assert_eq(output->data[address].r, input->data[address].r);
      cr_assert_eq(output->data[address].g, input->data[address].g);
      cr_assert_eq(output->data[address].b, input->data[address].b);
    }
  }

  free_img(input);
  free_img(output);
}
