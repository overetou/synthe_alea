banque = 'bank1';

%% Creer et sauvegarder banque de spectres
banque_spectres = importer_spectres(strcat('./audio/input/', banque));
save(strcat('./spectres/', banque), 'banque_spectres');

%% Charger banque de spectres
load(strcat('./spectres/', banque), 'banque_spectres');

%% Parametres utilisateur
instants = placer_instants(10);

%% Calcul et sauvegarde des oscillateurs
spectres = choisir_spectres(banque_spectres);
oscillateurs = interpolation(spectres, instants);
%oscillateurs = optimisation(oscillateurs);
save(strcat('./oscillateurs/', banque), 'oscillateurs');

%% Charger oscillateurs
load(strcat('./oscillateurs/', banque), 'oscillateurs');

%% Export wav
exporter_wav(oscillateurs, 1, 44100, './audio/output/test.wav', 4);