function [spectres] = importer_spectres(url)
    %   IMPORTER_SPECTRES
    % - Charge en m�moire chaque .wav du dossier 
    % - Demande � l'utilisateur de sp�cifier la plage de valeurs � 
    %   conserver pour garder un nombre entier de p�riodes
    % - Effectue une FFT pour passer dans le domaine spectral
    % - [A FAIRE] Analyse les diff�rentes caract�ristiques
    
    liste_fichiers = dir([url, '/*.wav']);
    for i_spectre = 1 : length(liste_fichiers)
        [echantillons, freq_echantillonnage] = audioread(liste_fichiers(i_spectre).name);
        echantillons = placer_limites(echantillons);
        N = max(size(echantillons));
        if N < freq_echantillonnage
            echantillons(N + 1 : freq_echantillonnage) = 0;
        end
        spectres(:, i_spectre) = fft(echantillons, freq_echantillonnage);
        if N > freq_echantillonnage
            spectres(:, i_spectre) = interp1(spectre, freq_echantillonnage);
        end
    end
end