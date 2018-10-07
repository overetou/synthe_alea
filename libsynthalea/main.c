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

t_matAF				bk_sp;
t_matAF 			bk_osc;
t_matAF 			*p_bk_sp;
t_matAF 			*p_bk_osc;

int main(int argc, char *argv[])
{
	// Charger une banque de spectres depuis un fichier	
	*p_bk_sp = bk_sp;
	charger_spectres(URL_COLLEC_SP, p_bk_sp);

	// Ajouter un nouveau spectre a la banque de spectres
	/*char yesno;
	while (1)
	{
		cout << "Ajouter un nouveau spectre ? (Y/N)" << '\n';
		cin >> yesno;
		if (yesno == 'Y') importer_spectre(URL_NV_SP_BRUT, *bk_sp);
		if (yesno == 'N') exit;
	}*/

	// Creer une banque d'oscillateurs avec les parametres de l'utilisateur et une banque de spectres
	*p_bk_osc = bk_osc;
	construction_oscillateurs(indices_temporels, evolution_puissance, evolution_dispersion, nombre_osc, p_bk_sp, p_bk_osc);

	// Cree le fichier wav pour quelques secondes a la frequence 440Hz
	double output[OUT_SIZE];
	for (unsigned i = 0; i < OUT_SIZE; i++)
	{
		output[i] = synthese(i, 440, 1.0, 44100, p_bk_osc);
	}
}