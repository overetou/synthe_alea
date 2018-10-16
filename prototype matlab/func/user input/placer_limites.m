function [echantillons] = placer_limites(echantillons)
    %   PLACER_LIMITES
    % - Affiche les racines pour faciliter la selection
    % - Demande a l'utilisateur de specifier la plage de valeurs a 
    %   conserver pour garder un nombre entier de periodes
    
    figure;
    plot(t, echantillons);
    afficher_racines(echantillons);
    [x_debut, ~] = ginput;
    [x_fin, ~] = ginput;
    close;
    echantillons = echantillons(x_debut : x_fin);
end