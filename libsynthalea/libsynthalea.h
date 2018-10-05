#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

typedef struct				compAF
{
    double ampl;
    double freq;
};
typedef struct				vecAF
{
    struct compAF           *comps;    
	unsigned				dim1;
};
typedef struct				matAF
{
	struct compAF			**comps;
	unsigned				dim1;
	unsigned				dim2;
};

void						alloc_matAF(unsigned dim1, unsigned dim2, struct matAF *mat);
void						desalloc_matAF(struct matAF *mat);

void						importer_spectre(const char *url_sp_brut, struct matAF *bk_sp);
void						charger_spectres(const char *url_collec, struct matAF *bk_sp);
void						sauvegarder_spectres(const char *url_collec, struct matAF *bk_sp);

void						construction_oscillateurs(const double *idx_temps, const double *evo_puissance, const double *evo_dispersion, unsigned nb_osc, struct matAF *bk_sp, struct matAF *bk_osc);
void						charger_oscillateurs(const char *url_collec, struct matAF *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, struct matAF *bk_osc);

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, struct matAF *bk_osc);
#endif