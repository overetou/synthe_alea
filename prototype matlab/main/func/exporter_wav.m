function [] = exporter_wav(oscillateurs, nombre_oscillateurs, freq_echantillonnage, url, duree)
    %   EXPORTER_WAV
    %
    %
    
    N = round(duree * freq_echantillonnage);
    t = linspace(0, duree, N);    
    %[oscillateurs, frequences] = sort(abs(oscillateurs), 1, 'descend');
    
    moy = zeros(1, size(oscillateurs, 1));
    for i = 1 : size(oscillateurs, 1)
        moy(i) = sum(abs(oscillateurs(i, :)) ./ size(oscillateurs, 2));
    end
    [~, frequences] = sort(moy, 'descend');
    
    oscillateurs_tries = zeros(nombre_oscillateurs, size(oscillateurs, 2));
    for i = 1 : nombre_oscillateurs
        for j = 1 : size(oscillateurs, 2)
            oscillateurs_tries(i, j) = oscillateurs(frequences(i), j);
        end
    end
        
    out = zeros(N, 1);
    for i = 1 : N
        for i_osc = 1 : nombre_oscillateurs
            osc_ampl = 0;
            osc_freq = frequences(i_osc);
            for i_coef = 1 : size(oscillateurs, 2)
                facteur_puissance = t(i) ^ (i_coef - 1);
                composante = oscillateurs_tries(i_osc, i_coef);
                osc_ampl = osc_ampl + composante * facteur_puissance;
                out(i) = out(i) + osc_ampl * sin(2 * pi * osc_freq * t(i));
            end
        end
    end
    out = out ./ max(out);
    audiowrite(url, out, freq_echantillonnage);
end