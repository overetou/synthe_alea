function [spectres] = importer_spectres(url)
    %   IMPORTER_SPECTRES
    % - Charge en memoire chaque .wav du dossier 
    % - Demande a l'utilisateur de specifier la plage de valeurs a 
    %   conserver pour garder un nombre entier de periodes
    % - Effectue une FFT pour passer dans le domaine spectral
    % - [A FAIRE] Analyse les differentes caracteristiques
    
    liste_fichiers = dir([url, '/*.wav']);
    for i_spectre = 1 : length(liste_fichiers)
        [echantillons, freq_echantillonnage] = audioread(liste_fichiers(i_spectre).name);
        echantillons = placer_limites(echantillons);
        N = max(size(echantillons));
        if N < freq_echantillonnage
            i = 1;
            while (i + 1) * N - 1 < freq_echantillonnage
                echantillons(i * N + 1 : (i + 1) * N) = echantillons(1 : N);
                i = i + 1;
            end
            echantillons(size(echantillons, 1) + 1 : freq_echantillonnage) = 0;
        end
        if N > freq_echantillonnage
            error('Signal trop long, sélectionner moins de périodes');
        end
        spectre = fft(echantillons, freq_echantillonnage);
        spectres(:, i_spectre) = spectre(1 : freq_echantillonnage / 2);
    end
end