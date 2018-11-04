function [instants] = placer_instants(duree)
    %   PLACER_INSTANTS
    %
    %
    
    grille_temporelle = linspace(0, duree, 10000);
    figure;
    plot(grille_temporelle, 0, '.k', 'LineWidth', 40);
    [instants, ~] = ginput;
    close;
end

