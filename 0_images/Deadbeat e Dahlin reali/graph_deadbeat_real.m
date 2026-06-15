% Pulizia ambiente di lavoro e chiusura figure precedenti
clear; clc; close all;

Ts = 0.0001; % Tempo di campionamento 
limite_campioni = 60000; % <--- Numero di campioni a cui tagliare i file 1 e 2

fprintf('\n=========================================\n');
fprintf('      ELABORAZIONE FILE 1, 2 e 3         \n');
fprintf('=========================================\n');

%% 1. Caricamento Dati e Taglio
% Caricamento 1.mat (Con Anti-Windup)
d1 = load('step_deadbeat_antiwindup.mat'); f1 = fieldnames(d1); mat1 = d1.(f1{1});
% Caricamento 2.mat (Senza Anti-Windup)
d2 = load('step_deadbeat_senza_antiwindup.mat'); f2 = fieldnames(d2); mat2 = d2.(f2{1});
% Caricamento 3.mat (Con Anti-Windup, Grafico a parte)
d3 = load('trap_deadbeat.mat'); f3 = fieldnames(d3); mat3 = d3.(f3{1});

% --- TAGLIO AI PRIMI 60.000 VALORI ---
% (Aggiunto controllo di sicurezza nel caso i file abbiano meno di 60000 campioni)
end_idx_1 = min(limite_campioni, size(mat1, 1));
end_idx_2 = min(limite_campioni, size(mat2, 1));
mat1 = mat1(1:end_idx_1, :);
mat2 = mat2(1:end_idx_2, :);

% Estrazione colonne (Col 1 = Setpoint, Col 2 = Risposta)
setpoint_12    = mat1(:, 1); % Uguale per 1 e 2
risposta_aw    = mat1(:, 2); % 1.mat
risposta_no_aw = mat2(:, 2); % 2.mat

setpoint_3 = mat3(:, 1);
risposta_3 = mat3(:, 2);

% Vettori dei tempi
t_12 = (0 : length(risposta_aw) - 1)' * Ts;
t_3  = (0 : length(risposta_3) - 1)' * Ts;

%% 2. Calcolo Metriche per Grafico 1 (Confronto 1.mat e 2.mat)
valore_regime = setpoint_12(end);
tolleranza = 0.01; 
banda_sup = valore_regime * (1 + tolleranza);
banda_inf = valore_regime * (1 - tolleranza);

% --- Metriche SENZA Anti-Windup (2.mat) ---
picco_max_no_aw = max(risposta_no_aw);
if picco_max_no_aw > valore_regime
    sovr_perc_no_aw = ((picco_max_no_aw - valore_regime) / valore_regime) * 100;
else
    sovr_perc_no_aw = 0;
end

indici_fuori_no_aw = find(risposta_no_aw > banda_sup | risposta_no_aw < banda_inf);
if isempty(indici_fuori_no_aw)
    ta_no_aw = 0; 
elseif indici_fuori_no_aw(end) == length(t_12)
    ta_no_aw = NaN; 
else
    ta_no_aw = t_12(indici_fuori_no_aw(end) + 1);
end

% --- Metriche CON Anti-Windup (1.mat) ---
picco_max_aw = max(risposta_aw);
if picco_max_aw > valore_regime
    sovr_perc_aw = ((picco_max_aw - valore_regime) / valore_regime) * 100;
else
    sovr_perc_aw = 0;
end

indici_fuori_aw = find(risposta_aw > banda_sup | risposta_aw < banda_inf);
if isempty(indici_fuori_aw)
    ta_aw = 0; 
elseif indici_fuori_aw(end) == length(t_12)
    ta_aw = NaN; 
else
    ta_aw = t_12(indici_fuori_aw(end) + 1);
end

%% 3. Plot GRAFICO 1 (Confronto tra 0 e 0.5 secondi)
figure('Name', 'Confronto Anti-Windup (0 - 0.5s)', 'NumberTitle', 'off');

% Plot Risposte
plot(t_12, risposta_no_aw, 'r', 'LineWidth', 1.5); hold on;
plot(t_12, risposta_aw, 'Color', '#77AC30', 'LineWidth', 1.5);
plot(t_12, setpoint_12, 'b--', 'LineWidth', 1.5);

grid on;
xlim([0 0.5]); % Limita la visuale dell'asse X tra 0 e 0.5s
title('Risposta del Sistema: Confronto (Zoom 0s - 0.5s)');
xlabel('Tempo [s]');
ylabel('Velocità');
legend('Senza Anti-Windup (2.mat)', 'Con Anti-Windup (1.mat)', 'Setpoint', 'Location', 'southeast');

% Preparazione stringhe per il riquadro
if isnan(ta_no_aw), str_ta_no_aw = 'NON RAGG.'; else, str_ta_no_aw = sprintf('%.4fs', ta_no_aw); end
if isnan(ta_aw), str_ta_aw = 'NON RAGG.'; else, str_ta_aw = sprintf('%.4fs', ta_aw); end

testo_prestazioni = {
    'CONFRONTO PRESTAZIONI (Senza AW  |  Con AW)'
    '-------------------------------------------'
    sprintf('Riferimento:      %.2f', valore_regime)
    sprintf('Picco massimo:    %.2f  |  %.2f', picco_max_no_aw, picco_max_aw)
    sprintf('Sovraelongazione: %.2f %%       |  %.2f %%', sovr_perc_no_aw, sovr_perc_aw)
    sprintf('T. Assest. (1%%):  %s     |  %s', str_ta_no_aw, str_ta_aw)
};

% Textbox prestazioni
annotation('textbox', [0.15 0.65 0.45 0.22], ... 
    'String', testo_prestazioni, ...
    'EdgeColor', 'black', ...
    'BackgroundColor', 'white', ...
    'FitBoxToText', 'on', ...
    'FontSize', 10, ...
    'FontName', 'Courier New');

%% 4. Plot GRAFICO 2 (3.mat tra 7 e 10 secondi)
figure('Name', 'Risposta 3.mat (7 - 10s)', 'NumberTitle', 'off');

plot(t_3, risposta_3, 'Color', '#77AC30', 'LineWidth', 1.5); hold on;
plot(t_3, setpoint_3, 'b--', 'LineWidth', 1.5);

grid on;
xlim([7 10]); % Limita l'asse X tra 7 e 10s
title('Risposta del Sistema con Anti-Windup (Zoom 7s - 10s)');
xlabel('Tempo [s]');
ylabel('Velocità');
legend('Risposta (3.mat)', 'Setpoint', 'Location', 'best');

fprintf('Elaborazione completata. Grafici generati.\n');
fprintf('=========================================\n\n');