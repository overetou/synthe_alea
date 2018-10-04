#ifndef LIBSYNTHALEA
#define LIBSYNTHALEA

#pragma region includes

#pragma endregion

#pragma region typedef struct
typedef struct oscillateur
{
	double					coefficients_amplitudes[];
	double					coefficients_frequences[];
};

typedef struct banque_oscillateurs
{
	oscillateur				collection_oscillateurs[];
};

typedef struct spectre
{
	double					hauteur_enregistrement;
	double					partiels_amplitudes[];
	double					partiels_frequences[];
};

typedef struct spectre_analyse
{
	spectre					*spectre_brut;
	double					puissance;
	double					dispersion;
};

typedef struct banque_spectres
{
	spectre_analyse			collection_spectres[];
};

typedef struct synthetiseur
{
	banque_oscillateurs		*oscillateurs;
	banque_spectres			*spectres;
	int						frequence_echantillonnage;
	double					gain;
};

#pragma endregion

#pragma region functions
void						analyser_spectre(const spectre sp_brut, spectre *sp_analyse);

void						charger_spectres(const char *url_collec, banque_spectres *bk_sp);
void						ajouter_spectre_dans_la_collection(const spectre_analyse nv_sp, banque_spectres *bk_sp);
void						sauvegarder_spectres(const char *url_collec, banque_spectres *bk_sp);

void						calcul_collection_oscillateurs(const double idx_temp[], const double evo_puissance[], const double evo_disp[], const size_t nb_osc, const banque_spectres *bk_sp, banque_oscillateurs *bk_osc);
void						charger_oscillateurs(const char *url_collec, banque_oscillateurs *bk_osc);
void						sauvegarder_oscillateurs(const char *url_collec, banque_oscillateurs *bk_osc);

void						modifier_frequence_echantillonnage(const size_t val, synthetiseur *synth);
void						modifier_gain(const double val, synthetiseur *synth);
double						synthese(const size_t idx_echantillon, const double frequence, const double velocite, synthetiseur *synth);
#pragma endregion

#endif