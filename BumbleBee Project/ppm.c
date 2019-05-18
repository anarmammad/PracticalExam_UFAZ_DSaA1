/*==========================================================*\
  Sunday March the 10th 2019
  Arash Habibi
  ppm.c
\*==========================================================*/

#include "ppm.h"

//----------------------------------------------------
// Allocates and initializes a ppm structure.
// The number of rows/columns + ppc (the number of pixels
// per cell) determine the width and the height of the
// image. snake_width_proportion is a number between
// 0 and 1.
// 0 : the snake has no thickness
// 1 : the snake is as wide as a whole cell.

struct ppm PPM_new(int nb_rows, int nb_cols, int ppc, float snake_width_proportion)
{
	struct ppm new;
	new.nb_rows = nb_rows;
	new.nb_cols = nb_cols;
	new.snake_width_proportion = snake_width_proportion;
	new.nb_pixels_per_cell = ppc;
	new.hauteur_img = nb_rows * ppc;
	new.largeur_img = nb_cols * ppc;
	new.pixels = (int*)calloc(3*new.largeur_img * new.hauteur_img, sizeof(int));

	// blue
	new.bg_color_r = 0;
	new.bg_color_g = 132;
	new.bg_color_b = 205;

	// orange
	new.ob_color_r = 255;
	new.ob_color_g = 123;
	new.ob_color_b = 50;

	// yellow
	new.fg_color_r = 255;
	new.fg_color_g = 200;
	new.fg_color_b = 20;

	return new;
}

//----------------------------------------------------
// This function draws one pixel (position (x,y)) in
// the ppm's pixel buffer. The color of this pixel is (r,g,b)

static struct ppm _drawPixel(struct ppm img, int y, int x, int r, int g, int b)
{
	if (x >= 0 && x < img.largeur_img && y >= 0 && y < img.hauteur_img)
	{
		int index = 3*(img.largeur_img * y + x);
		img.pixels[index] = r;
		img.pixels[index+1] = g;
		img.pixels[index+2] = b;
	}
	else
		;
		// printf("_drawPixel : pixel (y,x) is outside the image.\n");

	return img;
}

//----------------------------------------------------
// Fills the background with the background color and
// leaves a light grid so that the cells can be seen.

struct ppm PPM_drawBG(struct ppm img)
{
	int x,y;

	for(int y=0; y<img.hauteur_img; y++)
		for(int x=0; x<img.largeur_img; x++)
			if (x%img.nb_pixels_per_cell==0 || y%img.nb_pixels_per_cell==0)
				img = _drawPixel(img, y, x, img.bg_color_r/2, img.bg_color_g/2, img.bg_color_b/2);
			else
				img = _drawPixel(img, y, x, img.bg_color_r, img.bg_color_g, img.bg_color_b);
	return img;
}

//----------------------------------------------------
// Returns 1 if (row,col) is inside the image
// Returns 0 otherwise?

static int _isInside(struct ppm img, int row, int col)
{
	return row >= 0 && row < img.nb_rows && col >= 0 && col < img.nb_cols ;
}

//----------------------------------------------------
// Draws a whole square representing cell on row row
// and column col.

struct ppm PPM_drawCell(struct ppm img, int row, int col, int r, int g, int b)
{
	int largeur_serpent = (int)(img.snake_width_proportion * img.nb_pixels_per_cell);
	int marge = (img.nb_pixels_per_cell - largeur_serpent)/2;
	int x,y;

	if(_isInside(img,row,col))
	{
		for(y=row*img.nb_pixels_per_cell+marge; y<(row+1)*img.nb_pixels_per_cell-marge; y++)
			for(x=col*img.nb_pixels_per_cell+marge; x<(col+1)*img.nb_pixels_per_cell-marge; x++)
				img = _drawPixel(img, y, x, r, g, b);
	}
	else
		printf("PPM_drawCell : cell (%d,%d) is outside the image. max : (%d,%d)\n",row,col, img.nb_cols, img.nb_rows);

	return img;
}

//----------------------------------------------------
// Draws a rectangle that links the squares between
// cells (row1,col1) and (row2,col2). The cells must
// be 4-neighbors.

struct ppm PPM_drawLink(struct ppm img, int row1, int col1, int row2, int col2)
{
	int largeur_serpent = (int)(img.snake_width_proportion * img.nb_pixels_per_cell);
	int marge = (img.nb_pixels_per_cell - largeur_serpent)/2;

	if (row2==row1)
	{
		int colmin, colmax, row;

		row = row1;
		if(col2>col1)
		{
			colmin = col1;
			colmax = col2;
		}
		else
		{
			colmin = col2;
			colmax = col1;
		}

		if(colmax-colmin!=1)
		{
			printf("PPM_drawLink : (%d;%d) (%d;%d) : invalid.\n",row1,row2,col1,col2);
			printf("Each element in the cell array must be a neighbor of the following and previous cell.\n");
			exit(1);
		}
		else
		{
			for(int y=row*img.nb_pixels_per_cell+marge; y<(row+1)*img.nb_pixels_per_cell-marge; y++)
				for(int x=colmax*img.nb_pixels_per_cell-marge; x<colmax*img.nb_pixels_per_cell+marge; x++)
					img = _drawPixel(img, y, x, img.fg_color_r, img.fg_color_g, img.fg_color_b);
		}
	}
	else if (col2==col1)
	{
		int rowmin, rowmax, col;

		col = col1;
		if(row2>row1)
		{
			rowmin = row1;
			rowmax = row2;
		}
		else
		{
			rowmin = row2;
			rowmax = row1;
		}

		if(rowmax-rowmin!=1)
		{
			printf("PPM_drawLink : (%d;%d) (%d;%d) : invalid.\n",row1,row2,col1,col2);
			printf("Each element in the cell array must be a neighbor of the following and previous cell.\n");
			exit(1);
		}
		else
		{
			for(int y=rowmax*img.nb_pixels_per_cell-marge; y<rowmax*img.nb_pixels_per_cell+marge; y++)
				for(int x=col*img.nb_pixels_per_cell+marge; x<(col+1)*img.nb_pixels_per_cell-marge; x++)
					img = _drawPixel(img, y, x, img.fg_color_r, img.fg_color_g, img.fg_color_b);
		}
	}
	else
	{
		printf("PPM_drawLink : (%d;%d) (%d;%d) : invalid.\n",row1,row2,col1,col2);
		printf("Each element in the cell array must be a neighbor of the following and previous cell.\n");
		printf("You must have row1=row2 or col1=col2.\n");
		exit(1);
	}
	return img;
}

//----------------------------------------------------

static void _getMinMax(int row1, int col1, int row2, int col2, int *rowmin, int *colmin, int *rowmax, int *colmax)
{
	if (col1 <= col2)
	{
		*colmin = col1;
		*colmax = col2;
	}
	else
	{
		*colmin = col2;
		*colmax = col1;
	}
	if (row1 <= row2)
	{
		*rowmin = row1;
		*rowmax = row2;
	}
	else
	{
		*rowmin = row2;
		*rowmax = row1;
	}
}


//----------------------------------------------------
// This function draws a link between cell (row1,col1)
// and cell (row2,col2) event if the cells are not
// 4-neighbors.

struct ppm PPM_drawLink2(struct ppm img, int row1, int col1, int row2, int col2)
{
	if(row1==row2 && col1==col2)
		printf("PPM_drawLink2 : a link must be drawn between distinct points.\n");
	else
	{
		float ny, nx, l;
		nx = -(row2 - row1) * img.nb_pixels_per_cell;
		ny =  (col2 - col1) * img.nb_pixels_per_cell;
		l = sqrt(nx*nx+ny*ny);
		ny /= l;
		nx /= l;
		// (nx,ny) est unitaire

		int largeur_serpent = (int)(img.snake_width_proportion * img.nb_pixels_per_cell);

		int rowmin, rowmax, colmin, colmax;
		_getMinMax(row1, col1, row2, col2, &rowmin, &colmin, &rowmax, &colmax);

		int x1, y1;
		x1 = (col1+0.5)*img.nb_pixels_per_cell;
		y1 = (row1+0.5)*img.nb_pixels_per_cell;

		for(int y=(rowmin+0.5)*img.nb_pixels_per_cell-largeur_serpent/2; y<=(rowmax+0.5)*img.nb_pixels_per_cell+largeur_serpent/2; y++)
			for(int x=(colmin+0.5)*img.nb_pixels_per_cell-largeur_serpent/2; x<=(colmax+0.5)*img.nb_pixels_per_cell+largeur_serpent/2; x++)
			{
				float ps = (x-x1)*nx + (y-y1)*ny;
				if ( ps < largeur_serpent/2 && ps > -largeur_serpent/2 )
					img = _drawPixel(img, y, x, img.fg_color_r, img.fg_color_g, img.fg_color_b);
			}
	}
	return img;
}

//----------------------------------------------------
// Saves the buffer as it is in ppm format in
// filename.

void PPM_save(struct ppm img, char *filename)
{
	FILE *ppmfile;
	ppmfile = fopen(filename,"w");
	if(ppmfile==NULL)
	{
		perror(filename);
		exit(1);
	}
	else
	{
		fprintf(ppmfile,"P3\n%d %d\n255\n",img.largeur_img,img.hauteur_img);
		for(int i=0; i<3*img.largeur_img*img.hauteur_img; i++)
			fprintf(ppmfile,"%d ",img.pixels[i]);

		fclose(ppmfile);
	}
}

//----------------------------------------------------

void PPM_test(int nb_rows, int nb_cols)
{
	int pixels_per_cell = 20;
	float proportion_serpent = 0.7;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);
	/*
	img = PPM_drawCell(img, 0, 0);
	img = PPM_drawCell(img, 0, 1);
	img = PPM_drawLink(img, 0, 0, 0, 1);
	*/
	PPM_save(img, "toto.ppm");
}
