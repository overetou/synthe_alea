function [echantillons] = placer_limites(echantillons)
    %   PLACER_LIMITES
    % - Affiche les racines pour faciliter la sélection
    % - Demande à l'utilisateur de spécifier la plage de valeurs à 
    %   conserver pour garder un nombre entier de périodes
    
    figure;
    plot(t, echantillons);
    afficher_racines(echantillons);
    [x_debut, ~] = ginput;
    [x_fin, ~] = ginput;
    close;
    echantillons = echantillons(x_debut : x_fin);
end