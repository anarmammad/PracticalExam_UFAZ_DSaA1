/*==========================================================*\
  Sunday March the 10th 2019
  Arash Habibi
  CL_draw and CL_animate
\*==========================================================*/

#include "cellList.h"

//--------------------------------------------------
// Returns an empty stack of cells

struct cellList CL_new()
{
	struct cellList new_cellList;
	new_cellList.size = 0;
	return new_cellList;
}

//----------------------------------------------------
// Adds cell (row,col) on top of the stack cell

struct cellList CL_add(struct cellList cl, struct cell c)
{
	cl.arr[cl.size++] = c;
	return cl;
}

//----------------------------------------------------
// Returns the value of cell index i.

struct cell CL_get(struct cellList cl, int i)
{
	if(i >= cl.size || i < 0){
		printf("The cell list does not contain cells of index %d!\n", i);
	}
	return cl.arr[i];
}

//----------------------------------------------------
// Prints the contents of the cell list.

void CL_print(struct cellList cl, char *label)
{
	printf("%s\n", label);
	for(int i = 0; i < cl.size; i++)
	{
		printf("%d\t: (%d;%d)\n", i, cl.arr[i].row, cl.arr[i].col);
	}
}

//----------------------------------------------------
// Returns an element at random in cl (unless cl is empty)

struct cell CL_random(struct cellList cl)
{
	struct cell random_cell;
	if(cl.size == 0){
		printf("The cell list is empty!\n");
	}
	else{
		random_cell = cl.arr[random() % cl.size];
	}
	return random_cell;
}

//----------------------------------------------------
// Draws a grid of nb_rows x nb_cols cells in blue,
// and, on this grid, draws the cells of cell list cl.
// The whole image is saved in ppm_name with a .ppm
// extension.

struct cellList CL_randomFill(int nb_cells, int nb_rows, int nb_cols){
	struct cellList newList = CL_new();
	for (int i = 0; i < nb_cells; i++){
		int randomRow = random() % nb_rows;
		int randomCol = random() % nb_cols;
		newList = CL_add(newList, C_new(randomRow, randomCol));
	}
	return newList;
}

int CL_isInList(struct cell c, struct cellList cl){
	for (int i = 0; i < cl.size; i++)
		if(cl.arr[i].col == c.col && cl.arr[i].row == c.row)
			return 1;

	return 0;
}

struct cell CL_randomCellNotInObst(int nb_rows, int nb_cols, struct cellList obst){
	if(obst.size == nb_rows*nb_cols){
		return C_new(-1, -1);
	}

	struct cell randomCell;
	do{
		int randomRow = random() % nb_rows;
		int randomCol = random() % nb_cols;
		randomCell = C_new(randomRow, randomCol);
	}
	while(CL_isInList(randomCell, obst));
	return randomCell;
}

struct cellList CL_randomFill2(int nb_obstacles, int nb_rows, int nb_cols){
	struct cellList newList = CL_new();
	for (int i = 0; i < nb_obstacles; i++)
		newList = CL_add(newList, CL_randomCellNotInObst(nb_rows, nb_cols, newList));
	
	return newList;
}

struct cellList CL_neighbors(struct cell c, struct arena ar){

	struct cellList neighbors_cellList = CL_new();
	struct cell temp = C_new(c.row - 1, c.col);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row + 1, c.col);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);

	temp = C_new(c.row, c.col - 1);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row, c.col + 1);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);

	// ------
	
	temp = C_new(c.row - 1, c.col - 1);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row - 1, c.col + 1);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row + 1, c.col - 1);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row + 1, c.col + 1);
	if(A_isInside(temp, ar))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	return neighbors_cellList;
}

struct cellList CL_neighborsObst(struct cell c, struct arena ar, struct cellList obst){
	struct cellList neighbors_cellList = CL_new();
	struct cell temp = C_new(c.row - 1, c.col);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row + 1, c.col);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);

	temp = C_new(c.row, c.col - 1);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row, c.col + 1);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);

	// ------
	
	temp = C_new(c.row - 1, c.col - 1);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row - 1, c.col + 1);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row + 1, c.col - 1);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	temp = C_new(c.row + 1, c.col + 1);
	if(A_isInside(temp, ar) && !CL_isInList(temp, obst))
		neighbors_cellList = CL_add(neighbors_cellList, temp);
	
	return neighbors_cellList;
}

struct cellList CL_randomFlight(struct cell start, int nb_steps, struct arena ar, struct cellList obstacles){
	struct cellList flight = CL_new();
	flight = CL_add(flight, start);

	for (int i = 0; i < nb_steps - 1; i++){
		struct cell neighb = CL_random(CL_neighborsObst(start, ar, obstacles)); 
		flight = CL_add(flight, neighb);
		start = neighb;
	}

	return flight;
}

void CL_draw2(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name)
{
	int pixels_per_cell = 20;
	char ppm_file_name[50];
	float proportion_serpent = 0.5;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);

	for(int i=0; i<cl.size;i++)
	{
		struct cell c = cl.arr[i];
		img = PPM_drawCell(img, c.row, c.col, img.ob_color_r, img.ob_color_g, img.ob_color_b);
	}
	sprintf(ppm_file_name,"%s.ppm",ppm_name);
	PPM_save(img,ppm_file_name);
}

//----------------------------------------------------
// Draws a series of ppm image files. All of them show
// in orange the cells of cell list fix. The first image
// also shows the first cell of cell list anim. The second
// image shows only the second cell of anim and so on.

void CL_animate2(struct cellList fix, struct cellList anim, int nb_rows, int nb_cols, char *ppm_name)
{
	int pixels_per_cell = 20;
	char ppm_file_name[50];
	float proportion_serpent = 0.5;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);

	// img = PPM_drawCell(img, c.row, c.col);

	for(int t=0; t<anim.size;t++)
	{
		img = PPM_drawBG(img);
		for(int i=0; i<fix.size;i++)
		{
			struct cell c = fix.arr[i];
			img = PPM_drawCell(img, c.row, c.col, img.ob_color_r, img.ob_color_g, img.ob_color_b);
		}
		struct cell c = anim.arr[t];
		img = PPM_drawCell(img, c.row, c.col, img.fg_color_r, img.fg_color_g, img.fg_color_b);

		sprintf(ppm_file_name,"%s_%02d.ppm",ppm_name,t);
		PPM_save(img,ppm_file_name);
	}
}
