#include "arena.h"


struct arena A_new(int nb_rows, int nb_cols){
    struct arena new_arena;
    new_arena.nb_rows = nb_rows;
    new_arena.nb_cols = nb_cols;

    return new_arena;
}
int A_isInside(struct cell c, struct arena ar){
    if(c.row < ar.nb_rows && c.col < ar.nb_cols && c.row >= 0 && c.col >= 0) 
        return 1;
    return 0;    
}