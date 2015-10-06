/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#include "convolution.h"
#include "../lib/ppm.h"
#include "filter.h"

void extend_3(img_t *input , img_t *ouput)
{

}

void extend_5(img_t *input , img_t *ouput)
{

}

void convolution (img_t *output, const img_t *input, const filter_t *filter, int threads = 0)
{
    int width = input->width;
    int height =  input->height;
    int dim = filter_t->dim;
    img_t extend_input;

    if (dim == 3) goto dim_3;
    else if (dim == 5) goto dim_5;

dim_3:

dim_5:

}
