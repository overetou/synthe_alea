banque = 'bank_factory';

f = 440;
s_r = 44100;
n_waves = 1000;
gain = 0.8;

T = 1/f;
n_T = round(T * s_r);
t = linspace(0, n_waves * T, n_waves * s_r);

%% square
wave(1 : n_T / 2) = 1;
wave(n_T / 2 + 1 : n_T) = - 1;
for i = 0 : n_waves - 1
   out(i * n_T + 1 : (i + 1) * n_T) = wave(1 : n_T);
end

audiowrite(strcat('./audio/input/', banque, '/osc_square.wav'), gain .* out, s_r);

%% saw
for i = 1 : n_T
   wave(i) = 1 - (2 * i / n_T); 
end
for i = 0 : n_waves - 1
   out(i * n_T + 1 : (i + 1) * n_T) = wave(1 : n_T);
end
audiowrite(strcat('./audio/input/', banque, '/osc_saw.wav'), gain .* out, s_r);

%% tri
for i = 1 : n_T / 2
   wave(i) = 1 - (4 * i / n_T);
   wave(i + n_T / 2) = - 1 + (4 * i / n_T);
end
for i = 0 : n_waves - 1
   out(i * n_T + 1 : (i + 1) * n_T) = wave(1 : n_T);
end
audiowrite(strcat('./audio/input/', banque, '/osc_tri.wav'), gain .* out, s_r);