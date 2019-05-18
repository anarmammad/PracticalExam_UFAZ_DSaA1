#include "cell.h"

struct cell C_new(int row, int col){
    struct cell newCell;
    newCell.row = row;
    newCell.col = col;
    return newCell;
}
void C_print(struct cell c, char *label){
    printf("%s\t: (%d,%d)\n", label, c.row, c.col);
}


void C_printNeighbors(struct cell c){
    printf("Upper\t: (%d,%d)\n", c.row - 1, c.col);
    printf("Lower\t: (%d,%d)\n", c.row + 1, c.col);
    printf("Left\t: (%d,%d)\n", c.row, c.col - 1);
    printf("Right\t: (%d,%d)\n", c.row, c.col + 1);
}

