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
	bool ajouter_spectre_dans_la_collection(
		const std::vector<double> &amplitudes_brutes, 
		const std::vector<double> &frequences_brutes, 
		const double hauteur_enregistrement)
	{
		if (amplitudes_brutes.size() != frequences_brutes.size()) return false; // Pas le même nombre de points
		if (hauteur_enregistrement < 0) return false; // Fréquence négative

		std::vector<std::pair<double, double>> partiels;
		for (std::size_t i_partiel = 0; i_partiel < amplitudes_brutes.size(); i_partiel++)
		{
			partiels.push_back({ amplitudes_brutes[i_partiel], frequences_brutes[i_partiel] });
		}
		
		// Etalonnage des amplitudes
		double max_amplitude = 0;
		for (std::size_t i_amplitude = 0; i_amplitude < partiels.size(); i_amplitude++)
		{
			max_amplitude = std::fmax(max_amplitude, partiels[i_amplitude].first);
		}
		std::transform(
			partiels.begin(),
			partiels.end(),
			partiels.begin(),
			std::bind(diviser_amplitudes, std::placeholders::_1, max_amplitude));

		// Transformation des fréquences en ratios par rapport à la hauteur d'enregistrement
		std::transform(
			partiels.begin(),
			partiels.end(),
			partiels.begin(),
			std::bind(diviser_frequences, std::placeholders::_1, hauteur_enregistrement));

		// Calcul de la puissance du spectre

		// Calcul de la dispersion du spectre

		//... autres paramètres ?
		double ecart_inharmonique;
		double somme_ecarts = 0;
		for (std::size_t i_partiel; i_partiel < partiels.size(); i_partiel++)
		{			
			ecart_inharmonique = std::fmin(std::fmod(partiels[i_partiel].second, hauteur_enregistrement), std::fabs(hauteur_enregistrement - std::fmod(partiels[i_partiel].second, hauteur_enregistrement))) / hauteur_enregistrement;
			somme_ecarts += ecart_inharmonique * partiels[i_partiel].first;
		}
		double somme_amplitudes = 0;
		for (std::size_t i_partiel; i_partiel < partiels.size(); i_partiel++)
		{
			somme_amplitudes += partiels[i_partiel].first;
		}
		somme_ecarts /= somme_amplitudes;

		// Théorème de Rolle pour nettoyer le spectre
		for (std::size_t i_partiel = 1; i_partiel < partiels.size(); i_partiel++)
		{
			if (!(partiels.at(i_partiel++).first - partiels.at(i_partiel).first < 0 && 0 < partiels.at(i_partiel).first - partiels.at(i_partiel--).first))
			{
				partiels.at(i_partiel).first = 0;
			}
		}

		// Tri par amplitude décroissante des partiels du spectre
		std::sort(
			partiels.begin(),
			partiels.end(),
			trier_partiels_amplitudes_descendant);

		// Ajout du nouveau spectre à la collection
		spectre nouveau_spectre;
		nouveau_spectre.partiels = partiels;
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
			//ajouter_spectre();
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
			const std::vector<double> &evolution_dispersion,
			const std::size_t nombre_oscillateurs)
	{
	// Tests

	//
		std::size_t nombre_spectres = indices_temporels.size();

	// Trouver pour chaque point temporel le spectre le plus approprié en fonction des paramètres de l'utilisateur à ce point
	
	//

		std::vector<std::vector<std::pair<double, double>>> spectres_selectionnes(indices_temporels.size());
		
		for (std::size_t i_spectre = 0; i_spectre < spectres_selectionnes.size(); i_spectre++)
		{
			
			// On commence par ne garder que le bon nombre d'oscillateurs
			spectres_selectionnes[i_spectre].resize(nombre_oscillateurs);

			// Suivi des oscillateurs
			if (i_spectre > 0)
			{
				// Parcourt le spectre précédent
				for (std::size_t i_partiel = 0; i_partiel < nombre_oscillateurs; i_partiel++)
				{
					double min_ecart = 10000;
					std::size_t indice_min_ecart;

					// Trouve le partiel le plus proche dans le spectre actuel
					for (std::size_t ii_partiel = i_partiel; ii_partiel < nombre_oscillateurs; ii_partiel++)
					{
						double ecart = std::fabs(spectres_selectionnes[i_spectre][ii_partiel].second - spectres_selectionnes[i_spectre - 1][i_partiel].second);
						if (ecart < min_ecart)
						{
							min_ecart = ecart;
							indice_min_ecart = ii_partiel;
						}
					}
					// Modifier le spectre actuel pour replacer le partiel le plus proche sur la meme ligne que dans le spectre précédent
					// retirer le trouvé du vecteur à		spectres_selectionnes[i_spectre][indice_min_ecart]
					// le rajouter à la position voulue		spectres_selectionnes[i_spectre][i_partiel]
				}
			}
		}

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
	bool modifier_parametre_synthese(const std::size_t parametre, const double valeur)
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
			// et les indices aux puissances
			
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
	double synthese(const std::size_t indice_echantillon, const double frequence, const double velocite)
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

		double diviser_amplitudes(
			const std::pair<double, double> &a,
			const double b)
		{
			return (a.first / b);
		}

		double diviser_frequences(
			const std::pair<double, double> &a,
			const double b)
		{
			return (a.second / b);
		}

		// Trier les partiels par ordre décroissant d'amplitude
		bool trier_partiels_amplitudes_descendant(
			const std::pair<double, double> &partiel_a,
			const std::pair<double, double> &partiel_b)
		{
			return (partiel_a.first > partiel_b.first);
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
