function [oscillateurs] = interpolation(spectres, instants)
    %   INTERPOLATION
    %
    %
    
    if size(spectres, 2) ~= max(size(instants))
       error("Nombre de spectres different du nombre d'instants") 
    end
    J = size(spectres, 2);
    A = zeros(J);
    for i = 1 : J
       for j = 1 : J
          A(i, j) = instants(i) ^ (j - 1); 
       end
    end
    I = size(spectres, 1);
    oscillateurs = zeros(size(spectres));
    for i = 1 : I
        sp = spectres(i, :);
        osc = A \ transpose(sp);
        oscillateurs(i, :) = osc(:);
    end
end