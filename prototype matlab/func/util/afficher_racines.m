function [] = afficher_racines(echantillons)
    %   AFFICHER_RACINES
    % - Affiche les racines pour faciliter la selection
    
    hold on;
    for i = 2 : max(size(echantillons)) - 1
        if (echantillons(i - 1) > 0 && echantillons(i + 1) < 0) || (echantillons(i - 1) < 0 && echantillons(i + 1) > 0)
            errorbar(echantillons(i), 1);
        end
    end
    hold off;
end