#include <libsynthalea.h>

t_val get(
	const t_comp 	*p_comp)
{
	return p_comp->val;
}

t_val get(
	const t_vec 	*p_vec,
	unsigned 		i)
{
	t_comp			*p_comp;
	unsigned        idx;

	p_comp = p_vec->comps;
	for (idx = 0; idx < i; idx++)
	{
		p_comp = p_comp->next;
	}
	return get(p_comp);
}

t_val get(
	const t_mat 	*p_mat,
	unsigned 		i,
	unsigned 		j)
{
	t_vec			*p_vec;
	unsigned        idx;

	p_vec = p_mat->vecs;
	for (idx = 0; idx < j; idx++)
	{
		p_vec = p_vec->next;
	}
	return get(p_vec, i);
}