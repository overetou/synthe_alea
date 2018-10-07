#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

#include <stdbool.h>


typedef struct				s_compAF
{
    double					ampl;
    double					freq;
	struct s_compAF			*next;
}							t_compAF;

typedef struct				s_compDOUBLE
{
	double					val;
	struct s_compDOUBLE		*next;
}							t_compDOUBLE;

typedef struct				s_compBOOL
{
	bool					val;
	struct s_compBOOL		*next;
}							t_compBOOL;

typedef union 				s_comp
{
	t_compAF				compAF;
	t_compDOUBLE			compDOUBLE;
	t_compBOOL				compBOOL;
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


void						alloc_vec(unsigned dim1, t_vec *vec);
void						alloc_mat(unsigned dim1, unsigned dim2, t_mat *mat);
void						desalloc_vec(t_vec *vec);
void						desalloc_mat(t_mat *mat);

void						importer_spectre(const char *url_sp_brut, t_mat *bk_sp);
void						charger_spectres(const char *url_collec, t_mat *bk_sp);
void						sauvegarder_spectres(const char *url_collec, t_mat *bk_sp);

void						construction_oscillateurs(const double *idx_temps, const double *evo_puissance, const double *evo_dispersion, unsigned nb_osc, const t_mat *bk_sp, t_mat *bk_osc);
void						charger_oscillateurs(const char *url_collec, t_mat *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, t_mat *bk_osc);

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, t_mat *bk_osc);
#endif