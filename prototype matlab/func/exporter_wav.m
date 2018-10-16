function [] = exporter_wav(oscillateurs, nombre_oscillateurs, freq_echantillonnage, url, duree)
    %   EXPORTER_WAV
    %
    %
    
    N = round(duree * freq_echantillonnage);
    t = linspace(0, duree, N);    
    [oscillateurs, frequences] = sort(oscillateurs, 1, 'descend');
    out = zeros(N, 1);
    for i = 1 : N
        for i_osc = 1 : nombre_oscillateurs
            osc_ampl = 0;
            osc_freq = frequences(i_osc);
            for i_coef = 1 : size(oscillateurs, 2)
                facteur_puissance = t(i) ^ i_coef;
                composante = oscillateurs(i_osc, i_coef);
                osc_ampl = osc_ampl + composante * facteur_puissance;
                out(i) = out(i) + osc_ampl * sin(2 * pi * osc_freq * t(i));
            end
        end
    end
    out = out ./ max(out);
    audiowrite(url, out, freq_echantillonnage);
end