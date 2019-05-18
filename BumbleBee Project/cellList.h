/*==========================================================*\
  Sunday March the 10th 2019
  Arash Habibi
  cellList.h
\*==========================================================*/

#ifndef __CELLLIST_H__
#define __CELLLIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "arena.h"

#define CL_MAX 1000

struct cellList
{
	int size;
	struct cell arr[CL_MAX];
};

//----------------------------------------------------
// Returns an empty stack of cells

struct cellList CL_new();

//----------------------------------------------------
// Pushes cell (row,col) on top of the list cell

struct cellList CL_add(struct cellList cl, struct cell c);

//----------------------------------------------------
// Prints the contents of the cell list

void CL_print(struct cellList cl, char *label);

//----------------------------------------------------
// Returns an element at random in cl (unless cl is empty)

struct cell CL_random(struct cellList cl);

//----------------------------------------------------
// Returns a list of cells corresponding to the neighbors
// of c (Each neighbor has c neighbors)

struct cellList CL_neighbors(struct cell c, struct arena ar);

//----------------------------------------------------
// Returns a list filled with the neighbors of cell c
// Each cell has 4 neighbors except those who are on the
// border of the arena.

// struct cellList CL_randomPath(struct cell start, struct arena ar, struct cellList obstacles);
struct cellList CL_randomFlight(struct cell start, int nb_steps, struct arena ar, struct cellList obstacles);

//----------------------------------------------------
// Draws a series of ppm image files. In the first file
// can be seen the first cell of cl, in the second file,
// the first and the second. In the last file, all of
// the elements can be seen.

void CL_draw(struct cellList cl, int nb_rows, int nb_cols, int with_links, char *ppm_name);


void CL_draw2(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name);

//----------------------------------------------------
// 15h38 16h34

struct cellList CL_randomFill(int nb_iterations, int nb_rows, int nb_cols);

struct cell CL_randomCellNotInCL(int nb_rows, int nb_cols, struct cellList cl);

struct cell CL_randomCellNotInAr(int nb_rows, int nb_cols, struct arena ar);

struct cellList CL_randomFill2(int nb_obstacles, int nb_rows, int nb_cols);

int CL_isInList(struct cell c, struct cellList cl);

struct cellList CL_neighborsObst(struct cell c, struct arena ar, struct cellList obstacles);


//----------------------------------------------------
// Tests the behaviour of a cell list.

void CL_test(int nb_rows, int nb_cols);

void CL_animate2(struct cellList fix, struct cellList anim, int nb_rows, int nb_cols, char *ppm_name);


#endif // __CELLLIST_H__
