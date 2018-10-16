function [echantillons] = placer_limites(echantillons)
    %   PLACER_LIMITES
    % - Affiche les racines pour faciliter la selection
    % - Demande a l'utilisateur de specifier la plage de valeurs a 
    %   conserver pour garder un nombre entier de periodes
    
    figure;
    plot(echantillons);
    axis([5000 6000 -1 1]);
    afficher_racines(echantillons);
    [x_debut, ~] = ginput(1);
    [x_fin, ~] = ginput(1);
    close;
    echantillons = echantillons(x_debut : x_fin);
end