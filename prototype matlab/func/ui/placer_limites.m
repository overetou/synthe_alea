function [echantillons] = placer_limites(echantillons)
    %
    %
    %
    
    figure;
    plot(t, echantillons);
    [x_debut, ~] = ginput;
    [x_fin, ~] = ginput;
    close;
    echantillons = echantillons(x_debut : x_fin);
end