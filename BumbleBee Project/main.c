#include "cellList.h"
// for getpid() for setting up the seed for random
#include <unistd.h>

int main(int argc, char const *argv[])
{
    srandom(getpid());

    int nb_rows, nb_cols, nb_obstacles, start_row, start_col, flightLength;

    printf("Enter number of rows for arena: ");
    scanf("%d", &nb_rows);
    printf("Enter number of columns for arena: ");
    scanf("%d", &nb_cols);
    printf("Enter number of obstacles for arena: ");
    scanf("%d", &nb_obstacles);
    printf("Enter starting row: ");
    scanf("%d", &start_row);
    printf("Enter starting column: ");
    scanf("%d", &start_col);
    printf("Enter flight length: ");
    scanf("%d", &flightLength);


    struct cellList obst = CL_randomFill2(nb_obstacles,nb_rows,nb_cols);
    CL_draw2(obst, nb_cols, nb_rows, "obstacles");

    CL_animate2(obst, CL_randomFlight(C_new(start_row, start_col), flightLength, A_new(nb_rows, nb_cols), obst), nb_rows, nb_cols, "./animation/bumblebee");

    return 0;
}
