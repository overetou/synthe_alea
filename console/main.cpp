#include <iostream>

#include <AudioFile.h>
#include <synthese_additive_decisionnelle.h>

using namespace synthese_additive_decisionnelle;

int	main()
{
	std::cout << "Programm lanched." << std::endl;

	// Charger la base de données de spectres analysés
	std::cout << "URL de la collection de spectres à utiliser" << std::endl;
	std::string url_collection_spectres;
	charger_collection_spectres(url_collection_spectres);

	// Charger les paramètres de l'utilisateur
	std::vector<double> indices_temporels = {0.2, 0.5, 0.8};
	std::vector<double> evolution_puissance = {0.9, 0.9, 0.9};
	std::vector<double> evolution_dispersion = {0.9, 0.9, 0.9};
	calcul_collection_oscillateurs(
		indices_temporels,
		evolution_puissance,
		evolution_dispersion);

	// Crée le fichier wav pour quelques secondes à la fréquence 440Hz
	modifier_parametre_synthese(parmetres_synthese::parametre_frequence_echantillonnage, 44100);
	modifier_parametre_synthese(parmetres_synthese::parametre_gain, 1.0);
	std::vector<double> sortie;

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
		Y[ii_echantillon] = synthese(i_echantillon, 440, 127);
	}
	
	outputAudioFile.save("C:/test/file.wav");

	std::cout << "Programm closed." << std::endl;
	return (0);
}
