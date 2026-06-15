% Pulizia ambiente di lavoro
clear; clc; close all;

Ts = 0.0001; % Tempo di campionamento 
limite_campioni = 300000; % Limite a 300.000 campioni (30 secondi)

fprintf('\n=========================================\n');
fprintf('      ANALISI DAHLIN (File 3.mat)        \n');
fprintf('=========================================\n');

%% 1. Caricamento Dati e Taglio Globale
d3 = load('3.mat'); 
f3 = fieldnames(d3); 
mat3 = d3.(f3{1});

% Taglio ai primi 300.000 valori
end_idx = min(limite_campioni, size(mat3, 1));
mat3 = mat3(1:end_idx, :);

setpoint_3 = mat3(:, 1); 
risposta_3 = mat3(:, 2); 
t_3 = (0 : length(risposta_3) - 1)' * Ts;

%% 2. Ritaglio Finestra Temporale (10.5s - 12s)
% Troviamo gli indici esatti in cui il tempo è compreso in quell'intervallo
indici_finestra = find(t_3 >= 10.5 & t_3 <= 12);

% Estraiamo i sotto-vettori isolati
t_win    = t_3(indici_finestra);
risp_win = risposta_3(indici_finestra);
setp_win = setpoint_3(indici_finestra);

%% 3. Calcolo Specifiche SOLO sulla finestra temporale
val_regime_win = setp_win(end);
tolleranza = 0.01; 
banda_sup = val_regime_win * (1 + tolleranza);
banda_inf = val_regime_win * (1 - tolleranza);

% Picco e Sovraelongazione (isolati)
picco_win = max(risp_win);
if picco_win > val_regime_win
    sovr_win = ((picco_win - val_regime_win) / val_regime_win) * 100;
else
    sovr_win = 0;
end

% Tempo di Assestamento (isolato)
indici_fuori_win = find(risp_win > banda_sup | risp_win < banda_inf);
if isempty(indici_fuori_win)
    ta_win = t_win(1); % Già assestato
elseif indici_fuori_win(end) == length(t_win)
    ta_win = NaN; % Non si assesta entro i 12 secondi
else
    ta_win = t_win(indici_fuori_win(end) + 1);
end
ta_win = ta_win -11;

%% 4. Plot GRAFICO
figure('Name', 'Risposta Dahlin 3.mat (10.5 - 12s)', 'NumberTitle', 'off');

% Disegniamo tutto il vettore, ma poi applichiamo lo zoom
plot(t_3, risposta_3, 'Color', '#77AC30', 'LineWidth', 1.5); hold on;
plot(t_3, setpoint_3, 'b--', 'LineWidth', 1.5);

grid on; 
xlim([10.5 12]); % Zoom rigoroso sulla finestra richiesta

title('Risposta Sistema Dahlin (Zoom 10.5s - 12s)');
xlabel('Tempo [s]'); 
ylabel('Velocità');
legend('Risposta (Dahlin + AW)', 'Setpoint', 'Location', 'southeast');

% --- Inserimento Textbox con Specifiche Locali ---
if isnan(ta_win)
    str_ta = 'NON RAGG. (entro 12s)'; 
else
    str_ta = sprintf('%.4fs', ta_win); 
end

testo_prestazioni = {
    'METRICHE (Calcolate su finestra 10.5-12s)'
    '-----------------------------------------'
    sprintf('Riferimento:      %.2f', val_regime_win)
    sprintf('Picco massimo:    %.2f', picco_win)
    sprintf('Sovraelongazione: %.2f %%', sovr_win)
    sprintf('T. Assest. (1%%):  %s', str_ta)
};

annotation('textbox', [0.45 0.20 0.40 0.22], ... 
    'String', testo_prestazioni, ...
    'EdgeColor', 'black', ...
    'BackgroundColor', 'white', ...
    'FitBoxToText', 'on', ...
    'FontSize', 10, ...
    'FontName', 'Courier New');

fprintf('Elaborazione completata. Grafico 3.mat generato.\n\n');