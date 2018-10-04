#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

#pragma region includes

#pragma endregion

#pragma region typedef struct
typedef struct oscillateur
{
	double							*coefficients_amplitudes;
	double							*coefficients_frequences;
	unsigned						nombre_coefficients;
};

typedef struct banque_oscillateurs
{
	struct oscillateur				*collection_oscillateurs;
	unsigned						nombre_oscillateurs;
};

typedef struct spectre
{
	double							hauteur_enregistrement;
	double							*partiels_amplitudes;
	double							*partiels_frequences;
	unsigned						nombre_partiels;
};

typedef struct spectre_analyse
{
	struct spectre					*spectre_brut;
	double							puissance;
	double							dispersion;
};

typedef struct banque_spectres
{
	struct spectre_analyse			*collection_spectres;
	unsigned						nombre_spectres;
};

typedef struct synthetiseur
{
	struct banque_oscillateurs		*oscillateurs;
	struct banque_spectres			*spectres;
	int								frequence_echantillonnage;
	double							gain;
};

#pragma endregion

#pragma region functions
void						analyser_spectre(struct spectre *sp_brut, struct spectre_analyse *sp_analyse);

void						charger_spectres(const char *url_collec, struct banque_spectres *bk_sp);
void						ajouter_spectre_dans_la_collection(struct spectre_analyse *nv_sp, struct banque_spectres *bk_sp);
void						sauvegarder_spectres(const char *url_collec, struct banque_spectres *bk_sp);

void						calcul_collection_oscillateurs(const double idx_temp[], const double evo_puissance[], const double evo_disp[], struct banque_spectres *bk_sp, struct banque_oscillateurs *bk_osc);
void						charger_oscillateurs(const char *url_collec, struct banque_oscillateurs *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, struct banque_oscillateurs *bk_osc);

void						modifier_frequence_echantillonnage(unsigned val, struct synthetiseur *synth);
void						modifier_gain(double val, struct synthetiseur *synth);
double						synthese(unsigned idx_echantillon, double frequence, double velocite, struct synthetiseur *synth);
#pragma endregion

#endif
