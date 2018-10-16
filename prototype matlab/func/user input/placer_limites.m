function [echantillons] = placer_limites(echantillons)
    %   PLACER_LIMITES
    % - Affiche les racines pour faciliter la selection
    % - Demande a l'utilisateur de specifier la plage de valeurs a 
    %   conserver pour garder un nombre entier de periodes
    
    figure;    
    axis([5000 6000 -1 1]); % EUH
    hold on;
    plot(echantillons, '-k');
    for i = 2 : max(size(echantillons)) - 1
        if (echantillons(i - 1) > 0 && echantillons(i + 1) < 0) || (echantillons(i - 1) < 0 && echantillons(i + 1) > 0)
            plot(i, 0, '.r', 'LineWidth', 55);
        end
    end
    hold off;
    [x_debut, ~] = ginput(1);
    [x_fin, ~] = ginput(1);
    close;
    echantillons = echantillons(round(x_debut) : round(x_fin));
end