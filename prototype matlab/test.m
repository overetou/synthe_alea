banque_spectres = importer_spectres('./audio/input/');
spectres = choisir_spectres(banque_spectres);
oscillateurs = interpolation(spectres, placer_instants());
oscillateurs = optimisation(oscillateurs);
exporter_wav(oscillateurs, './audio/output/test.wav');