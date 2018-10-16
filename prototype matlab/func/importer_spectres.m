function [spectres] = importer_spectres(url)
    %
    %
    %
    
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