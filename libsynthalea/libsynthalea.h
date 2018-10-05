#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

#pragma region includes
#include <stdbool.h>
#pragma endregion

#pragma region typedef struct

typedef struct banque_spectres // matrice (nb_sp * nb_par)
{
	double							**spectres_partiels_amplitudes;
	double							**spectres_partiels_frequences;
	unsigned						nombre_spectres;
	unsigned						nombre_partiels;
	bool							allocation;
};

typedef struct banque_oscillateurs // matrice (nb_osc * nb_coef)
{
	double							**oscillateurs_coefficients_amplitudes;
	double							**oscillateurs_coefficients_frequences;
	unsigned						nombre_oscillateurs;
	unsigned						nombre_coefficients;
	bool							allocation;
};
#pragma endregion

#pragma region functions

void						allocation_banque_spectres(struct banque_spectres *bk_sp);
void						allocation_banque_oscillateurs(struct banque_oscillateurs *bk_osc);

void						desallocation_banque_spectres(struct banque_spectres *bk_sp);
void						desallocation_banque_oscillateurs(struct banque_oscillateurs *bk_osc);








void						importer_spectre(const char *url_sp_brut, struct banque_spectres *bk_sp);
void						charger_spectres(const char *url_collec, struct banque_spectres *bk_sp);
void						sauvegarder_spectres(const char *url_collec, struct banque_spectres *bk_sp);

void						construction_oscillateurs(const double idx_temp[], const double evo_puissance[], const double evo_disp[], unsigned nb_osc, struct banque_spectres *synth, struct banque_oscillateurs *bk_osc);
void						charger_oscillateurs(const char *url_collec, struct banque_oscillateurs *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, struct banque_oscillateurs *bk_osc);

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, struct banque_oscillateurs *bk_osc);

#pragma endregion

#endif
