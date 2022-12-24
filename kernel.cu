#include "kernel.h"
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void Kernel()
{
    return;
}

void hostFE()
{
    Kernel<<<1, 1>>>();
}
