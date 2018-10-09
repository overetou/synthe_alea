#include <libsynthalea.h>

void desalloc(
    t_comp          *p_comp)
{
    free(p_comp);
}

void desalloc(
    t_vec           *p_vec)
{
    t_comp          *p_comp;
    unsigned        idx;

    p_comp = p_vec->comps;
    for (idx = 0; idx < p_vec->dim1; idx++)
    {
        desalloc(p_comp);
        p_comp = p_comp->next;
    }
}

void desalloc(
    t_mat           *p_mat)
{
    t_vec           *p_vec;
    unsigned        idx;

    p_vec = p_mat->vecs;
    for (idx = 0; idx < p_mat->dim2; idx++)
    {
        desalloc(p_vec);
        p_vec = p_vec->next;
    }
}