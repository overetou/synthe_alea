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

    p_comp = p_vec->comps;
    while (p_vec->dim1)
    {
        desalloc(p_comp);
        p_comp = p_comp->next;
    }
}

void desalloc(
    t_mat           *p_mat)
{
    t_vec           *p_vec;

    p_vec = p_mat->vecs;
    while (p_mat->dim2)
    {
        desalloc(p_vec);
        p_vec = p_vec->next;
    }
}