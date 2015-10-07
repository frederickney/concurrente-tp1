/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#include "convolution.h"
#include "../lib/ppm.h"
#include "filter.h"

img_t *extend_3(img_t *input)
{
    img_t *extend = alloc_img(input->width + 2 , input->height + 2);
    for (int i = 0; i < extend->width * extend->height; i++)
    {
        if (i == 0)
            extend->data[i] = input->data[i];
        else if (i == input->width + 1)
            extend->data[i] = input->data[i-2];
        else if ( i > 0 && i < input->width)
            extend->data[i] = input->data[i - 1];
        else if (i % (input->width + 1) == 1 && i / (input->width+1) > 0 && i / (input->width+1) < input->height+1)
            extend->data[i] = input->data[(i / (input->width+1) - 1) * (input->width - 1) + 1];
        else if (i % (input->width + 1) == 0 && i / (input->width+1) > 0 && i / (input->width+1) < input->height+1)
            extend->data[i] = (i / (input->width+1) - 1) * (input->width - 1);
        else if (i > input->height * (input->width+1))
            extend->data[i] = extend->data[i - input->width + 1];
    }
    return extend;
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
    for (int i = 0; i < width * height; i++)
    {
        if ((i % height) == 0)
            if ((i - height) < 0){}
            else if (i / height != 0 && i / height < width){}
            else if (i / height = width){}
        else if (i % height != 0 && i % width < height - 1){}
        else if (i % width = height - 1){}
    }
dim_5:

}
