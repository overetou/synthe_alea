[xSamples, sampleRate] = audioread('sample1.wav');
N = sampleRate; % pour une précision de 1Hz
xSamples = xSamples(1:N);
amplitudes = abs(fft(xSamples, N));
amplitudes = amplitudes(1:N/2);
frequences = (1:N/2) .* (sampleRate/N);

fid = fopen('sample1.txt','wt'); % améliorer pour meilleure lisibilité à la lecture
fprintf(fid, '%f     %f\n', amplitudes, frequences);
fclose(fid);
