#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

typedef struct				s_compAF
{
    double					ampl;
    double					freq;
	struct s_compAF			*next;
}							t_compAF;

typedef struct				s_vecAF
{
    t_compAF				*comps;    
	unsigned				dim1;
	struct s_vecAF			*next;
}							t_vecAF;

typedef struct				s_matAF
{
	t_vecAF					*vecs;
	unsigned				dim1;
	unsigned				dim2;
	//struct s_matAF		*next; Maybe later
} 							t_matAF;

void						alloc_matAF(unsigned dim1, unsigned dim2, t_matAF *mat);
void						desalloc_matAF(t_matAF *mat);

void						importer_spectre(const char *url_sp_brut, t_matAF *bk_sp);
void						charger_spectres(const char *url_collec, t_matAF *bk_sp);
void						sauvegarder_spectres(const char *url_collec, t_matAF *bk_sp);

void						construction_oscillateurs(const double *idx_temps, const double *evo_puissance, const double *evo_dispersion, unsigned nb_osc, t_matAF *bk_sp, t_matAF *bk_osc);
void						charger_oscillateurs(const char *url_collec, struct matAF *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, struct matAF *bk_osc);

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, t_matAF *bk_osc);
#endif