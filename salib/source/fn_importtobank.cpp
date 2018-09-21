#include <includes/cl_bank>

#include <algorithm>
#include <functional>

bool salib::banque_spectres::ajouter_spectre_dans_la_collection(
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
