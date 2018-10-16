function [echantillons] = placer_limites(echantillons)
    %   PLACER_LIMITES
    % - Affiche les racines pour faciliter la s�lection
    % - Demande � l'utilisateur de sp�cifier la plage de valeurs � 
    %   conserver pour garder un nombre entier de p�riodes
    
    figure;
    plot(t, echantillons);
    afficher_racines(echantillons);
    [x_debut, ~] = ginput;
    [x_fin, ~] = ginput;
    close;
    echantillons = echantillons(x_debut : x_fin);
end