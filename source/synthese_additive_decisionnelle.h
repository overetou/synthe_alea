#pragma once

#include <vector>
#include <algorithm>
#include <functional>

#include <iostream>
#include <fstream>

#define PI 3.1427


namespace synthese_additive_decisionnelle
{	

#pragma region Base de données
// A FAIRE : 
// - paramètres pour caractériser les spectres
// - organisation du fichier texte

	// Ajoute un nouveau spectre à la collection et en calcule les paramètres
	bool ajouter_spectre(
		const std::vector<double> &amplitudes_brutes, 
		const std::vector<double> &frequences_brutes, 
		const double hauteur_enregistrement)
	{
		if (amplitudes_brutes.size() != frequences_brutes.size()) return false; // Pas le même nombre de points
		if (hauteur_enregistrement < 0) return false; // Fréquence négative

		spectre nouveau_spectre;
		nouveau_spectre.partiels.first = amplitudes_brutes;
		nouveau_spectre.partiels.second = frequences_brutes;

		// Etalonnage des amplitudes
		double max_amplitude = 0;
		for (std::size_t i_amplitude = 0; i_amplitude < amplitudes_brutes.size(); i_amplitude++)
		{
			max_amplitude = std::fmax(max_amplitude, amplitudes_brutes[i_amplitude]);
		}
		std::transform(
			nouveau_spectre.partiels.first.begin(),
			nouveau_spectre.partiels.first.end(),
			nouveau_spectre.partiels.first.begin(),
			std::bind(std::divides<double>(), std::placeholders::_1, max_amplitude));

		// Transformation des fréquences en ratios par rapport à la hauteur d'enregistrement
		std::transform(
			nouveau_spectre.partiels.second.begin(),
			nouveau_spectre.partiels.second.end(),
			nouveau_spectre.partiels.second.begin(),
			std::bind(std::divides<double>(), std::placeholders::_1, hauteur_enregistrement));

		// Calcul de la puissance du spectre

		// Calcul de la dispersion du spectre

		//... autres paramètres ?

		// Nettoyage et tri par fréquence décroissante des partiels du spectre
		std::sort(
			nouveau_spectre.partiels.begin(),
			nouveau_spectre.partiels.end(),
			trier_partiels_frequences_descendant);

		// Ajout du nouveau spectre à la collection
		collection_spectres.push_back(nouveau_spectre);
		return true;
	}
	
	// Charge la collection depuis un fichier sérialisé
	bool charger_collection_spectres(const std::string &url_collection)
	{
		std::ifstream lecture_fichier;
		lecture_fichier.open(url_collection, std::ios::in);
		if (!lecture_fichier.is_open()) return false;
		else
		{
			// charge le contenu du fichier dans collection_spectres
		}
		lecture_fichier.close();
		return true;
	}

	// Sauvegarde la collection vers un fichier sérialisé
	bool sauvegarder_collection_spectres(const std::string &url_collection)
	{
		std::ofstream ecriture_fichier;
		ecriture_fichier.open(url_collection, std::ios::out);
		if (!ecriture_fichier.is_open()) return false;
		else
		{
			// ecrit le contenu de collection_spectres dans le fichier 
		}
		ecriture_fichier.close();
		return true;
	}
#pragma endregion

#pragma region IA décisionnelle
	// Construire le spectre évolutif dans le temps avec les spectres les plus appropriés
	bool calcul_collection_oscillateurs(
			const std::vector<double> &indices_temporels,
			const std::vector<double> &evolution_puissance,
			const std::vector<double> &evolution_dispersion)
	{
	// Tests

	//
		std::size_t nombre_spectres = indices_temporels.size();

	// Trouver pour chaque point temporel le spectre le plus approprié en fonction des paramètres de l'utilisateur à ce point
	/*
	// Discrete Rolle theorem
		std::fill(XBufferStems.begin(), XBufferStems.end(), 0);
		for (iComponent = 1; iComponent < nHalfComponents - 1; iComponent++)
		{
			if (XBuffer.at(iComponent++) - XBuffer.at(iComponent) < 0 && 0 < XBuffer.at(iComponent) - XBuffer.at(iComponent--))
			{
				XBufferStems.at(iComponent) = XBuffer.at(iComponent);
			}
		}

		// Frequency compression
		sortedAmplitudes.resize(nHalfComponents);
		sortedFrequencies.resize(nHalfComponents);
		sort2(XBufferStems, sortedAmplitudes, sortedFrequencies);
		std::reverse(sortedAmplitudes.begin(), sortedAmplitudes.end());
		std::reverse(sortedFrequencies.begin(), sortedFrequencies.end());
		sortedAmplitudes.resize(nComponents);
		sortedFrequencies.resize(nComponents);

		// Oscillators following
		if (iBuffer == 1)
		{
			outFrequencies = sortedFrequencies;
			outAmplitudes = sortedAmplitudes;
		}
		else
		{
			std::fill(bDidCandidatesMatch.begin(), bDidCandidatesMatch.end(), 0);
			sortedFrequenciesMemory = sortedFrequencies;
			for (iComponent = 0; iComponent < nComponents; iComponent++)
			{
				for (iCandidate = 0; iCandidate < nComponents; iCandidate++)
				{
					frequencyDistances.at(iCandidate) = abs((int)sortedFrequencies.at(iComponent) - (int)sortedFrequenciesMemory.at(iCandidate));
				}

				sort2(frequencyDistances, frequencyDistances, iFrequencyDistancesSorted);

				for (iCandidate = 0; iCandidate < nComponents; iCandidate++)
				{
					if (bDidCandidatesMatch.at(iFrequencyDistancesSorted[iCandidate]) == false)
					{
						outFrequencies[iFrequencyDistancesSorted[iCandidate]] = sortedFrequencies[iComponent];
						outAmplitudes[iFrequencyDistancesSorted[iCandidate]] = sortedAmplitudes[iComponent];
						bDidCandidatesMatch[iFrequencyDistancesSorted[iCandidate]] = true;
						break;
					}
				}
			}
			sortedFrequencies = outFrequencies;
		}*/
	// Construction de la matrice d'interpolation de Vandermonde avec les indices temporels
		// Initialisation
		std::vector<std::vector<std::size_t>> matrice_interpolation(2 * nombre_spectres);
		for (std::size_t i_rang = 0; i_rang < 2 * nombre_spectres; i_rang++) matrice_interpolation[i_rang].resize(nombre_spectres);

		// Remplissage
		for (std::size_t i_rang = 0; i_rang < 2 * nombre_spectres; i_rang++)
		{
			for (std::size_t i_colonne = 0; i_colonne < nombre_spectres; i_colonne++)
			{
				// Augmentation de la matrice
				if (i_rang < nombre_spectres)
				{
					if (i_rang == i_colonne) matrice_interpolation[i_rang][i_colonne] = 1;
					else matrice_interpolation[i_rang][i_colonne] = 0;
				}

				// Matrice de Vandermonde
				else
				{
					matrice_interpolation[nombre_spectres + i_rang][i_colonne] = 0;
				}
			}
		}

	// Inversion de la matrice d'interpolation
	// Algorithme de gauss


	// Calcul pour chaque oscillateur des coefficients du polynôme d'interpolation
		for (std::size_t i_oscillateur = 0; i_oscillateur < nombre_oscillateurs; i_oscillateur++)
		{
			// Pour les amplitudes
				// A^-1 * a
			// Pour les fréquences
				// A^-1 * f
		}
	}
#pragma endregion

#pragma region Synthèse additive
	enum parmetres_synthese
	{
		parametre_frequence_echantillonnage,
		parametre_gain
	};

	// Modifie un paramètre de la synthèse
	bool modifier_parametre_synthese(const std::size_t &parametre, const double &valeur)
	{
		switch (parametre)
		{
		case parametre_frequence_echantillonnage: frequence_echantillonnage = (int)valeur;
		case parametre_gain: gain = (double)valeur;
		}
		return true;
	}

	// Charge la collection depuis un fichier sérialisé
	bool charger_collection_oscillateurs(const std::string &url_collection)
	{
		std::ifstream lecture_fichier;
		lecture_fichier.open(url_collection, std::ios::in);
		if (!lecture_fichier.is_open()) return false;
		else
		{
			// std::vector<oscillateur> collection_oscillateurs
			
		}
		lecture_fichier.close();
		return true;
	}

	// Sauvegarde la collection vers un fichier sérialisé
	bool sauvegarder_collection_oscillateurs(const std::string &url_collection) // faire les 3 autres comme celui-là
	{
		std::ofstream ecriture_fichier;
		ecriture_fichier.open(url_collection, std::ios::out);
		if (!ecriture_fichier.is_open()) return false;
		for (std::size_t i_oscillateur = 0; i_oscillateur < collection_oscillateurs.size(); i_oscillateur++)
		{
			//ecriture_fichier << std::string(collection_oscillateurs[i_oscillateur]);
		}
		ecriture_fichier.close();
		return true;
	}

	// Synthétise le son en temps réel depuis les polynômes d'interpolation
	double synthese(const std::size_t &indice_echantillon, const double &frequence, const double &velocite)
	{
		if (collection_oscillateurs.size() == 0) return false; // Collection d'oscillateurs pas encore chargée


		double indice_temporel; // f de indice_echantillon, frequence_echantillonnage

		double indice_puissance;
		double oscillateur_amplitude;
		double oscillateur_frequence;

		double somme_oscillateurs = 0;
		for (std::size_t i_oscillateur = 0; i_oscillateur < collection_oscillateurs.size(); i_oscillateur++)
		{
			oscillateur_amplitude = 0;
			oscillateur_frequence = 0;
			for (std::size_t i_coefficient = 0; i_coefficient < collection_oscillateurs[i_oscillateur].size(); i_coefficient++)
			{
				indice_puissance = std::pow(indice_temporel, i_coefficient);
				oscillateur_amplitude += collection_oscillateurs[i_oscillateur][i_coefficient].first * velocite * indice_puissance;
				oscillateur_frequence += collection_oscillateurs[i_oscillateur][i_coefficient].second * frequence * indice_puissance;
			}
			somme_oscillateurs += oscillateur_amplitude * std::sin(2 * PI * oscillateur_frequence * indice_temporel);
		}

		if (std::abs(somme_oscillateurs) > 1) gain = 1 / std::abs(somme_oscillateurs);
		return somme_oscillateurs * gain;
	}
#pragma endregion

#pragma region Private scope
	namespace
	{
		// Spectres
		struct spectre
		{
			std::vector<std::pair<double, double>> partiels; // On utilise .first : amplitudes et .second : fréquences

			// Paramètres caractérisant le spectre
			double puissance;
			double dispersion;
		};		
		std::vector<spectre> collection_spectres;

		// Trier les partiels par ordre décroissant de fréquence
		bool trier_partiels_frequences_descendant(
			const std::pair<double, double> &partiel_a,
			const std::pair<double, double> &partiel_b)
		{
			return (partiel_a.second > partiel_b.second);
		}

		// Oscillateurs [i_oscillateur][i_coefficient_lagrange].first / .second
		std::vector<std::vector<std::pair<double, double>>> collection_oscillateurs;

		// Paramètres de la synthèse
		std::size_t frequence_echantillonnage = 44100;
		double gain = 1;

		struct note
		{
			std::size_t midi_note;
			std::size_t midi_velocity;
		};
	}
#pragma endregion

}




// Si on veut sauvegarder dans un .wav vite fait en utilisant audioFile.h :
/*
void save(std::string outputFileName)
{
	outputAudioFile.setNumChannels(1);
	outputAudioFile.setSampleRate(sampleRate);
	outputAudioFile.setBitDepth(16);
	outputAudioFile.setAudioBufferSize(1, 1024);

	std::vector<double> time(nBuffers);
	for (iBuffer = 0; iBuffer < nBuffers; iBuffer++)
	{
		time.at(iBuffer) = (int)iBuffer / (double)sampleRate;
	}

	std::vector<double> Y(1024);
	std::vector<std::vector<double>> YC(1);
	std::size_t iiBuffer = 0;
	for (iBuffer = 0, iiBuffer = 0; iBuffer < nBuffers; iBuffer++, iiBuffer++)
	{
		if (iiBuffer >= 1024)
		{
			YC.at(0) = Y;
			outputAudioFile.setAudioBuffer(YC);
			std::fill(Y.begin(), Y.end(), 0);
			iiBuffer = 0;
		}
		for (iComponent = 0; iComponent < nComponents; iComponent++)
		{
			Y.at(iBuffer) = Y.at(iBuffer) + 0.0001 * std::abs(outAmplitudesTable.at(iBuffer).at(iComponent)) * std::sin(2 * cPI * (double)outFrequenciesTable.at(iBuffer).at(iComponent) * time.at(iBuffer));
		}
	}
	outputAudioFile.save(outputFileName);
}
*/
