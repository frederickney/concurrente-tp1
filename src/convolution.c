/****************************************************************************\
 * @brief
 *
 *
\****************************************************************************/

#include "convolution.h"
#include "../lib/ppm.h"
#include "filter.h"

img_t *extend(img_t *input)
{
    img_t *extend = alloc_img(input->width + 2 , input->height + 2);
    int w_ext = input->width + 1;
    int h_ext = input->height + 1;
    int height = input->height;
    int width = input->width;
    for (int i = 0; i < extend->width * extend->height; i++)
    {
        if (i == 0)
            extend->data[i] = input->data[i];   //building the left corner extension pixel
        else if (i == w_ext)
            extend->data[i] = input->data[i-2]; //building the right corner extension pixel
        else if ( i > 0 && i < width)
            extend->data[i] = input->data[i - 1];   //building the rest of the 1st pixel line extension
        else if (i % w_ext == 1 && i / w_ext > 0 && i / w_ext < h_ext)  // detecting the begin of a pixel line
            extend->data[i] = input->data[(i / w_ext - 1) * (width - 1) + 1];   //left extension of input picture
        else if (i % w_ext == 0 && i / w_ext > 0 && i / w_ext < h_ext)  //detecting the end of a pixel line
            extend->data[i] = input->data[(i / w_ext - 1) * (width - 1)];    //right extension of input picture
        else if (i%w_ext > 0 && i%w_ext < w_ext && i/w_ext > 0 && i/w_ext < h_ext) //place to insert input picture
            extend->data[i] = input->data[(i / w_ext - 1) * (width - 1) + i % w_ext];   //inserting the picture
        else if (i > height * w_ext)    //building the last pixel line of extend
            extend->data[i] = extend->data[i - w_ext];  //copy of previous pixel line into last pixel line
    }
    return extend;
}
/*
img_t *extend_5(img_t *input)
{
    img_t *extend = alloc_img(input->width + 4 , input->height + 4);
    int w_ext = input->width + 1;
    int h_ext = input->height + 1;
    int height = input->height;
    int width = input->width;
    return extend;
}
*/
void convolution (img_t *output, const img_t *input, const filter_t *filter, int threads = 0)
{
    int width = input->width;
    int height =  input->height;
    int dim = filter_t->dim;
    img_t extend_input;

    if (dim == 3) goto dim_3;
    else if (dim == 5) goto dim_5;

dim_3:
    img_t *input_ext3 = extend(input);
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
    img_t *input_ext5 = extend(extend(input));

}
