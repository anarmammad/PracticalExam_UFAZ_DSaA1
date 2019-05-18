/*==========================================================*\
  Sunday March the 10th 2019
  Arash Habibi
  ppm.h
\*==========================================================*/

#ifndef __PPM_H__
#define __PPM_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ppm
{
	int nb_rows, nb_cols, nb_pixels_per_cell;
	int largeur_img, hauteur_img;
	float snake_width_proportion;
	int *pixels;
	int bg_color_r, bg_color_g, bg_color_b;
	int fg_color_r, fg_color_g, fg_color_b;
	int ob_color_r, ob_color_g, ob_color_b;
};


//----------------------------------------------------
// Allocates and initializes a ppm structure.
// The number of rows/columns + ppc (the number of pixels
// per cell) determine the width and the height of the
// image. snake_width_proportion is a number between
// 0 and 1.
// 0 : the snake has no thickness
// 1 : the snake is as wide as a whole cell.

struct ppm PPM_new(int nb_rows, int nb_cols, int ppc, float snake_width_proportion);

//----------------------------------------------------
// Fills the background with the background color and
// leaves a light grid so that the cells can be seen.

struct ppm PPM_drawBG(struct ppm img);

//----------------------------------------------------
// Draws a whole square representing cell on row row
// and column col.

struct ppm PPM_drawCell(struct ppm img, int row, int col, int r, int g, int b);

//----------------------------------------------------
// Draws a rectangle that links the squares between
// cells (row1,col1) and (row2,col2).

struct ppm PPM_drawLink(struct ppm img, int row1, int col1, int row2, int col2);

struct ppm PPM_drawLink2(struct ppm img, int row1, int col1, int row2, int col2);

//----------------------------------------------------
// Saves the buffer as it is in ppm format in
// filename.

void PPM_save(struct ppm img, char *filename);

//----------------------------------------------------

void PPM_test(int nb_rows, int nb_cols);

#endif // __PPM_H__
