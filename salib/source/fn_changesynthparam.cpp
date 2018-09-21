#include <includes/cl_synth>

bool salib::synthetiseur::modifier_parametre_synthese(
  const std::size_t parametre,
  const double valeur)
{
  switch (parametre)
  {
  case frequence_echantillonnage: frequence_echantillonnage = (int)valeur;
  case gain: gain = (double)valeur;
  }
  return true;
}
