#include <libsynthalea.h>

void alloc(
    t_comp          *p_comp)
{
    p_comp = malloc(sizeof(t_comp));
}

void alloc(
    t_vec           *p_vec, 
    unsigned         i)
{
    t_comp          *p_comp;

    p_vec = malloc(i * sizeof(t_comp));
    p_comp = p_vec->comps;
    while (i)
	{
		alloc(p_comp);
        p_comp = p_comp->next;
	}
}

void alloc(
    t_mat           *p_mat, 
    unsigned        i, 
    unsigned        j)
{
    t_vec          *p_vec;

    p_mat = malloc(i * sizeof(t_vec));
    p_vec = p_mat->vecs;
    while (j)
	{
		alloc(p_vec, i);
        p_vec = p_vec->next;
	}
}