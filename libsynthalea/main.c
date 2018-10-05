#include <libsynthalea.h>

#include <stdio.h>

#define URL_COLLEC_SP "c:/spectres.txt"
#define URL_NV_SP_BRUT "c:/spectre_brut.txt"
#define URL_COLLEC_OSC "c:/oscillateurs.txt"

double indices_temporels[] = { 0.2, 0.5, 0.8 };
double evolution_puissance[] = { 0.9, 0.9, 0.9 };
double evolution_dispersion[] = { 0.9, 0.9, 0.9 };
unsigned nombre_osc = 100;

#define URL_WAV "c:/out.wav"
#define OUT_SIZE 1000000



int main(int argc, char *argv[])
{
	// Charger une banque de spectres depuis un fichier
	struct banque_spectres *bk_sp;
	charger_spectres(URL_COLLEC_SP, bk_sp);

	// Ajouter un nouveau spectre a la banque de spectres
	char yesno;
	while (true)
	{
		cout << "Ajouter un nouveau spectre ? (Y/N)" << '\n';
		cin >> yesno;
		if (yesno == 'Y') importer_spectre(URL_NV_SP_BRUT, bk_sp);
		if (yesno == 'N') exit;
	}

	// Creer une banque d'oscillateurs avec les parametres de l'utilisateur et une banque de spectres
	struct banque_oscillateurs *bk_osc;
	construction_oscillateurs(indices_temporels, evolution_puissance, evolution_dispersion, nombre_osc, bk_sp, bk_osc);

	// Cree le fichier wav pour quelques secondes a la frequence 440Hz
	double output[OUT_SIZE];
	for (unsigned i = 0; i < OUT_SIZE; i++)
	{
		output[i] = synthese(i, 440, 1.0, 44100, bk_osc);
	}
}