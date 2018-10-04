#include <libsynthalea.h>

void				analyser_spectre(
						const spectre sp_brut, 
						spectre *sp_analyse)
{
// cast
partiels = spectre_brut.partiels;
hauteur_enregistrement = spectre_brut.hauteur_enregistrement;


if (spectre_brut.hauteur_enregistrement < 0) return false; // Fr�quence n�gative





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

// Transformation des fr�quences en ratios par rapport � la hauteur d'enregistrement
std::transform(
	partiels.begin(),
	partiels.end(),
	partiels.begin(),
	std::bind(diviser_frequences, std::placeholders::_1, hauteur_enregistrement));

// Calcul de la puissance du spectre

// Calcul de la dispersion du spectre

//... autres param�tres ?
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

// Th�or�me de Rolle pour nettoyer le spectre
for (std::size_t i_partiel = 1; i_partiel < partiels.size(); i_partiel++)
{
	if (!(partiels.at(i_partiel++).first - partiels.at(i_partiel).first < 0 && 0 < partiels.at(i_partiel).first - partiels.at(i_partiel--).first))
	{
		partiels.at(i_partiel).first = 0;
	}
}

// Tri par amplitude d�croissante des partiels du spectre
std::sort(
	partiels.begin(),
	partiels.end(),
	trier_partiels_amplitudes_descendant);

return true;
}







double				diviser_amplitudes(
						const std::pair<double, double> &a,
						const double b)
{
	return (a.first / b);
}

double				diviser_frequences(
						const std::pair<double, double> &a,
						const double b)
{
	return (a.second / b);
}

// Trier les partiels par ordre d�croissant d'amplitude
bool				trier_partiels_amplitudes_descendant(
						const std::pair<double, double> &partiel_a,
						const std::pair<double, double> &partiel_b)
{
	return (partiel_a.first > partiel_b.first);
}