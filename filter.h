/**
 * Project name: Programation  Concurente
 * File name: ${FILE_NAME}
 * Created by: neyconsulting.
 * Created on: 01/10/2015 15:18
 * Author: Frederick NEY
 */

typedef struct filter {
    int size = 3;
    int array_filter[size][size] = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
} identity;

typedef struct filter {
    int size = 5;
    float array_filter[size][size] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
} sharpen;

typedef struct filter {
    int size = 3;
    float array_filter[size][size] = { [0 ... 2] =((float) 1)/((float)9)};
} blur;

typedef struct filter {
    int size = 3;
    int array_filter[size][size] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
} edge;

typedef struct filter {
    float div = 256;
    int size = 3;
    int array_filter[size][size] = {
    {((float) 1)/div, ((float) 4)/div, ((float) 6)/div, ((float) 4)/div, ((float) 1)/div},
    {((float) 4)/div, ((float) 16)/div, ((float) 24)/div, ((float) 16)/div, ((float) 4)/div},
    {((float) 16)/div, ((float) 24)/div, ((float) 36)/div, ((float) 24)/div, ((float) 16)/div},
    {((float) 4)/div, ((float) 16)/div, ((float) 24)/div, ((float) 16)/div, ((float) 4)/div},
    {((float) 1)/div, ((float) 4)/div, ((float) 6)/div, ((float) 4)/div, ((float) 1)/div}
    };
} gauss;
typedef struct filter {
    float div = -256;
    int size = 3;
    int array_filter[size][size] = {
    {((float) 1)/div, ((float) 4)/div, ((float) 6)/div, ((float) 4)/div, ((float) 1)/div},
    {((float) 4)/div, ((float) 16)/div, ((float) 24)/div, ((float) 16)/div, ((float) 4)/div},
    {((float) 16)/div, ((float) 24)/div, ((float) 36)/div, ((float) 24)/div, ((float) 16)/div},
    {((float) 4)/div, ((float) 16)/div, ((float) 24)/div, ((float) 16)/div, ((float) 4)/div},
    {((float) 1)/div, ((float) 4)/div, ((float) 6)/div, ((float) 4)/div, ((float) 1)/div}
    };
} unsharp;