function [] = afficher_racines(echantillons)
    %   AFFICHER_RACINES
    % - Affiche les racines pour faciliter la sélection
    
    hold on;
    for i = 2 : max(size(echantillons)) - 1
        if (echantillons(i - 1) > 0 && echantillons(i + 1) < 0) || (echantillons(i - 1) < 0 && echantillons(i + 1) > 0)
            plot(i, 0, 'c');
        end
    end
    hold off;
end

