#include <libsynthalea.h>

void set(
    t_vec           *p_vec, 
    unsigned        i, 
    t_val           val)
{
    t_comp			*p_comp;
    
    p_comp = p_vec->comps;
    while (i)
	{
		p_comp = p_comp->next;
	}
    p_comp->val = val;
}

void set(
    t_mat           *p_mat, 
    unsigned        i,
    unsigned        j,
    t_val           val)
{
    t_vec			*p_vec;
    
    p_vec = p_mat->vecs;
    while (j)
	{
		p_vec = p_vec->next;
	}
    set(p_vec, i, val);
}