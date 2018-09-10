[xSamples, sampleRate] = audioread('sample2.wav');
N = 1024; % pour une précision de 1Hz
xSamples = xSamples(1:N);
amplitudes = abs(fft(xSamples, N));
amplitudes = amplitudes(1:N/2);
frequences = (1:N/2) .* (sampleRate/N);

max_amplitude = max(amplitudes);
amplitudes = amplitudes ./ max_amplitude;

puissance = sum(amplitudes) / N;

fid = fopen('sample2.txt','wt'); % améliorer pour meilleure lisibilité à la lecture
fprintf(fid, 'amplitudes :\n');
fprintf(fid, 'a = %f\n', amplitudes);
fprintf(fid, '\n frequences :\n');
fprintf(fid, 'f = %f\n', frequences);
fclose(fid);
