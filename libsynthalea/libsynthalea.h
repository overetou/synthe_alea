#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

typedef double				(**matAF)[2];
#define                     _ampl 0
#define                     _freq 1

void						alloc_matAF(unsigned dim1, unsigned dim2, matAF *mat);
void						desalloc_matAF(matAF *mat);

void						importer_spectre(const char *url_sp_brut, matAF *bk_sp);
void						charger_spectres(const char *url_collec, matAF *bk_sp);
void						sauvegarder_spectres(const char *url_collec, matAF *bk_sp);

void						construction_oscillateurs(const double *idx_temps, const double *evo_puissance, const double *evo_dispersion, unsigned nb_osc, matAF *bk_sp, matAF *bk_osc);
void						charger_oscillateurs(const char *url_collec, matAF *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, matAF *bk_osc);

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, matAF *bk_osc);
#endif