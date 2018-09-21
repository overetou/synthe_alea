#include <cl_synthetiseur.h>

bool salib::synthetiseur::modifier_frequence_echantillonnage(
  const std::size_t valeur)
{
    frequence_echantillonnage = valeur;
}

bool salib::synthetiseur::modifier_gain(
  const double valeur)
{
  gain = valeur;
}
