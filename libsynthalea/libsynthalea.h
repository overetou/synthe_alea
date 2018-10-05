#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

#pragma region includes
#include <stdbool.h>
#pragma endregion

#pragma region typedef struct
typedef struct spectre_brut
{
	double							hauteur_enregistrement;
	double							*partiels_amplitudes;
	double							*partiels_frequences;
	unsigned						nombre_partiels;
	bool							allocation;
};
typedef struct spectre
{
	double							puissance;
	double							dispersion;
	double							*partiels_amplitudes;
	double							*partiels_frequences;
	unsigned						nombre_partiels;
	bool							allocation;
};
typedef struct banque_spectres
{
	struct spectre					*collection_spectres;
	unsigned						nombre_spectres;
	bool							allocation;
};

typedef struct oscillateur
{
	double							*coefficients_amplitudes;
	double							*coefficients_frequences;
	unsigned						nombre_coefficients;
	bool							allocation;
};
typedef struct banque_oscillateurs
{
	struct oscillateur				*collection_oscillateurs;
	unsigned						nombre_oscillateurs;
	bool							allocation;
};
#pragma endregion

#pragma region functions

void						allocation_spectre(struct spectre *sp);
void						allocation_oscillateur(struct oscillateur *osc);
void						allocation_banque_spectres(struct banque_spectres *bk_sp);
void						allocation_banque_oscillateurs(struct banque_oscillateurs *bk_osc);

void						desallocation_spectre(struct spectre *sp);
void						desallocation_oscillateur(struct oscillateur *osc);
void						desallocation_banque_spectres(struct banque_spectres *bk_sp);
void						desallocation_banque_oscillateurs(struct banque_oscillateurs *bk_osc);

void						analyser_spectre(struct spectre_brut *sp_brut, struct spectre *sp);





void						ajouter_spectre_dans_la_collection(struct spectre *sp, struct banque_spectres *bk_sp);
void						ajouter_spectre_dans_la_collection(struct spectre_brut *sp_brut, struct banque_spectres *bk_sp);
void						ajouter_spectre_dans_la_collection(const char *url_sp_brut, struct banque_spectres *bk_sp);
void						charger_spectres(const char *url_collec, struct banque_spectres *bk_sp);
void						sauvegarder_spectres(const char *url_collec, struct banque_spectres *bk_sp);

void						ia(const double idx_temp[], const double evo_puissance[], const double evo_disp[], unsigned nb_osc, struct banque_spectres *synth, struct banque_oscillateurs *bk_osc);
void						charger_oscillateurs(const char *url_collec, struct banque_oscillateurs *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, struct banque_oscillateurs *bk_osc);

double						synthese(unsigned idx_echantillon, double frequence, double velocite, unsigned frequence_echantillonnage, struct banque_oscillateurs *bk_osc);

#pragma endregion

#endif
