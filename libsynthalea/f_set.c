#include <libsynthalea.h>

void set(
    t_comp          *p_comp,
    t_val           val)
{
    p_comp->val = val;
}

void set(
    t_vec           *p_vec,
    t_val           val,
    unsigned        i)
{
    t_comp			*p_comp;
    unsigned        idx;
    
    p_comp = p_vec->comps;
    for (idx = 0; idx < i; idx++)    
	{
		p_comp = p_comp->next;
	}
    set(p_comp, val);
}

void set(
    t_mat           *p_mat,    
    t_val           val,
    unsigned        i,
    unsigned        j)
{
    t_vec			*p_vec;
    unsigned        idx;
    
    p_vec = p_mat->vecs;
    for (idx = 0; idx < j; idx++)
	{
		p_vec = p_vec->next;
	}
    set(p_vec, val, i);
}