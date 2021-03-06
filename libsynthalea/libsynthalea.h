#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

#include <stdbool.h>


typedef struct				s_AF
{
    double					ampl;
    double					freq;
}							t_AF;

typedef union 				s_val
{
	t_AF					valAF;
	double					valDOUBLE;
	bool					valBOOL;
}							t_val;

typedef struct				s_comp
{
    t_val					val;
	struct s_comp			*next;
}							t_comp;

typedef struct				s_vec
{
    t_comp					*comps;   
	unsigned				dim1;
	struct s_vec			*next;
}							t_vec;

typedef struct				s_mat
{
	t_vec					*vecs;
	unsigned				dim1;
	unsigned				dim2;
} 							t_mat;

t_val 						get(const t_comp *p_comp);
t_val 						get(const t_vec *p_vec, unsigned i);
t_val 						get(const t_mat *p_mat, unsigned i, unsigned j);

void 						set(t_comp *p_comp, const t_val val);
void 						set(t_vec *p_vec, const t_val val, unsigned i);
void 						set(t_mat *p_mat, const t_val val, unsigned i, unsigned j);

void 						alloc(t_comp *p_comp);
void 						alloc(t_vec *p_vec, unsigned i);
void 						alloc(t_mat *p_mat, unsigned i, unsigned j);

void 						desalloc(t_comp *p_comp);
void 						desalloc(t_vec *p_vec);
void 						desalloc(t_mat *p_mat);





/*
void						importer_spectre(const char *url_sp_brut, t_mat *bk_sp);
void						charger_spectres(const char *url_collec, t_mat *bk_sp);
void						sauvegarder_spectres(const char *url_collec, t_mat *bk_sp);

void						construction_oscillateurs(const double *idx_temps, const double *evo_puissance, const double *evo_dispersion, unsigned nb_osc, const t_mat *bk_sp, t_mat *bk_osc);
void						charger_oscillateurs(const char *url_collec, t_mat *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, t_mat *bk_osc);
*/

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, t_mat *bk_osc);
#endif