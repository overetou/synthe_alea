#include <iostream>

#include "includes\AudioFile.h"
#include <cl_synthetiseur.h>

using namespace salib;

#define url_collection_spectres "c:/spectres.txt"
#define url_nouveau_spectre_brut "c:/spectre_brut.txt"
#define url_collection_oscillateurs "c:/oscillateurs.txt"

#define url_wav "c:/out.wav"

#define nombre_oscillateurs 100

synthetiseur synth;
synthetiseur *pSynth;

int	main()
{
	std::cout << "Programm lanched." << std::endl;
	pSynth = new synthetiseur(synth);

	// Charger la base de données de spectres analysés
	std::cout << "URL de la collection de spectres à utiliser" << std::endl;
	pSynth->charger_collection_spectres(url_collection_spectres);

	// Ajouter un nouveau spectre à la base de données
	char yesno;
	while (true)
	{
		std::cout << "Ajouter un nouveau spectre ? (Y/N)" << std::endl;
		std::cin >> yesno;
		if (yesno == 'Y') pSynth->ajouter_spectre_dans_la_collection(url_nouveau_spectre_brut);
		if (yesno == 'N') exit;
	}

	// Créer un son avec les paramètres de l'utilisateur
	std::vector<double> indices_temporels = {0.2, 0.5, 0.8};
	std::vector<double> evolution_puissance = {0.9, 0.9, 0.9};
	std::vector<double> evolution_dispersion = {0.9, 0.9, 0.9};
	pSynth->calcul_collection_oscillateurs(
		indices_temporels,
		evolution_puissance,
		evolution_dispersion,
		nombre_oscillateurs);
		
	// Charger son depuis le fichier
	//charger_collection_oscillateurs(url_collection_oscillateurs);

	// Crée le fichier wav pour quelques secondes à la fréquence 440Hz
	pSynth->modifier_frequence_echantillonnage(44100);
	pSynth->modifier_gain(1.0);

	sauvegarder_wav(url_wav);

	delete pSynth;

	std::cout << "Programm closed." << std::endl;
	return (0);
}

void sauvegarder_wav(const std::string &url_sortie_wav)
{
	AudioFile<double> outputAudioFile;
	std::vector<double> Y(1024);
	std::vector<std::vector<double>> YC(1);
	outputAudioFile.setNumChannels(1);
	outputAudioFile.setSampleRate(44100);
	outputAudioFile.setBitDepth(16);
	outputAudioFile.setAudioBufferSize(1, 1024);
	std::size_t ii_echantillon;
	for (
		std::size_t i_echantillon = 0, ii_echantillon = 0;
		i_echantillon < 44100 * 4;
		i_echantillon++, ii_echantillon++)
	{
		if (ii_echantillon >= 1024)
		{
			YC[0] = Y;
			outputAudioFile.setAudioBuffer(YC);
			std::fill(Y.begin(), Y.end(), 0);
			ii_echantillon = 0;
		}
		Y[ii_echantillon] = pSynth->synthese(i_echantillon, 440, 127);
	}

	outputAudioFile.save(url_sortie_wav);
}
