function [] = afficher_racines(echantillons)
    %   AFFICHER_RACINES
    % - Affiche les racines pour faciliter la selection
    
    hold on;
    for i = 2 : max(size(echantillons)) - 1
        if (echantillons(i - 1) > 0 && echantillons(i + 1) < 0) || (echantillons(i - 1) < 0 && echantillons(i + 1) > 0)
            plot(i, 0, '*', 'LineWidth', 5);
        end
    end
    hold off;
end