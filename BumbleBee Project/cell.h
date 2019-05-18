#ifndef __CELL_H__

#include <stdio.h>
#include <stdlib.h> 

#include "ppm.h"

struct cell
{
    int row;
    int col;
};
struct cell C_new(int row, int col);
void C_print(struct cell c, char *label);
void C_printNeighbors(struct cell c);

#endif