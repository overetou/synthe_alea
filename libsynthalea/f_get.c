#include <libsynthalea.h>

t_val get(
	t_comp 			*p_comp)
{
	return p_comp->val;
}

t_val get(
	t_vec 			*p_vec, 
	unsigned 		i)
{
	t_comp			*p_comp;

	p_comp = p_vec->comps;
	while(i)
	{
		p_comp = p_comp->next;
	}
	return get(p_comp);
}

t_val get(
	t_mat 			*p_mat,
	unsigned 		i, 
	unsigned 		j)
{
	t_vec			*p_vec;

	p_vec = p_mat->vecs;
	while (j)
	{
		p_vec = p_vec->next;
	}
	return get(p_vec, i);
}