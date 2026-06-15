% Pulizia ambiente di lavoro e chiusura figure
clear; clc; close all;

%% 1. Caricamento e preparazione dei dati
% --- Dati SENZA Anti-Windup ---
data_sforzo   = load('sforzo_deadbeat_senza_antiwindup.mat');
data_speed    = load('speed_deadbeat_senza_antiwindup.mat');

% --- Dati CON Anti-Windup ---
data_sforzo_aw = load('sforzo_deadbeat_antiwindup.mat');
data_speed_aw  = load('speed_deadbeat_antiwindup.mat');

% --- Dati Riferimento ---
data_setpoint = load('setpoint.mat');

% Estrazione automatica dei vettori dai file (Senza AW)
fields_sforzo = fieldnames(data_sforzo);
sforzo = data_sforzo.(fields_sforzo{1});

fields_speed = fieldnames(data_speed);
speed_rads = data_speed.(fields_speed{1});

% Estrazione automatica dei vettori dai file (Con AW)
fields_sforzo_aw = fieldnames(data_sforzo_aw);
sforzo_aw = data_sforzo_aw.(fields_sforzo_aw{1});

fields_speed_aw = fieldnames(data_speed_aw);
speed_rads_aw = data_speed_aw.(fields_speed_aw{1});

% Estrazione Setpoint
fields_setpoint = fieldnames(data_setpoint);
setpoint = data_setpoint.(fields_setpoint{1});

% --- CONVERSIONE RAD/S -> RPM ---
speed_rpm = speed_rads * (30 / pi);
speed_rpm_aw = speed_rads_aw * (30 / pi);

% --- CREAZIONE VETTORE TEMPO CORRETTO ---
t = linspace(0, 5, 50001)'; 

%% 2. Calcolo delle Metriche di Performance
valore_regime = setpoint(end); 
tolleranza = 0.01; 
banda_sup = valore_regime * (1 + tolleranza);
banda_inf = valore_regime * (1 - tolleranza);

% --- METRICHE SENZA ANTI-WINDUP ---
picco_max = max(speed_rpm);
if picco_max > valore_regime
    sovr_perc = ((picco_max - valore_regime) / valore_regime) * 100;
else
    sovr_perc = 0; 
end

indici_fuori_banda = find(speed_rpm > banda_sup | speed_rpm < banda_inf);
if isempty(indici_fuori_banda)
    ta = 0; 
elseif indici_fuori_banda(end) == length(t)
    ta = NaN; 
else
    ta = t(indici_fuori_banda(end) + 1);
end

ta = ta - 1;

% --- METRICHE CON ANTI-WINDUP ---
picco_max_aw = max(speed_rpm_aw);
if picco_max_aw > valore_regime
    sovr_perc_aw = ((picco_max_aw - valore_regime) / valore_regime) * 100;
else
    sovr_perc_aw = 0; 
end

indici_fuori_banda_aw = find(speed_rpm_aw > banda_sup | speed_rpm_aw < banda_inf);
if isempty(indici_fuori_banda_aw)
    ta_aw = 0; 
elseif indici_fuori_banda_aw(end) == length(t)
    ta_aw = NaN; 
else
    ta_aw = t(indici_fuori_banda_aw(end) + 1);
end

ta_aw = ta_aw -1;
%% 3. Plot dello Sforzo di Controllo (Confronto)
figure('Name', 'Sforzo di Controllo', 'NumberTitle', 'off');
% Traccia linea Senza AW (Rossa)
plot(t, sforzo, 'r', 'LineWidth', 1.5); 
hold on;
% Traccia linea Con AW (Verde)
plot(t, sforzo_aw, 'Color', '#77AC30', 'LineWidth', 1.5); 
grid on;
xlim([0.75 1.5]); % Zoom temporale richiesto
title('Sforzo di Controllo: Effetto dell''Anti-Windup');
xlabel('Tempo [s]');
ylabel('Tensione [V]');
legend('Deadbeat SENZA Anti-Windup', 'Deadbeat CON Anti-Windup', 'Location', 'best');

%% 4. Plot della Risposta (Speed) con Textbox Doppio
figure('Name', 'Risposta del Sistema', 'NumberTitle', 'off');
% Traccia linea Senza AW (Rossa)
plot(t, speed_rpm, 'r', 'LineWidth', 1.5);
hold on;
% Traccia linea Con AW (Verde)
plot(t, speed_rpm_aw, 'Color', '#77AC30', 'LineWidth', 1.5);
% Traccia Setpoint (Blu tratteggiata)
plot(t, setpoint, 'b--', 'LineWidth', 1.5);
grid on;
xlim([0.75 1.5]); % Zoom temporale richiesto
title('Risposta del Sistema (Zoom 0.75s - 1.5s)');
xlabel('Tempo [s]');
ylabel('Velocità [RPM]');
legend('Risposta SENZA Anti-Windup', 'Risposta CON Anti-Windup', 'Riferimento', 'Location', 'southeast');

% --- CREAZIONE DEL RIQUADRO TESTUALE (TEXTBOX) ---
if isnan(ta)
    ta_str = 'NON RAGG.';
else
    ta_str = sprintf('%.4fs', ta);
end

if isnan(ta_aw)
    ta_str_aw = 'NON RAGG.';
else
    ta_str_aw = sprintf('%.4fs', ta_aw);
end

% Array di stringhe formattato per il confronto diretto
testo_prestazioni = {
    'CONFRONTO PRESTAZIONI (Senza AW  |  Con AW)'
    '-------------------------------------------'
    sprintf('Riferimento:      %.2f RPM', valore_regime)
    sprintf('Picco massimo:    %.2f RPM  |  %.2f RPM', picco_max, picco_max_aw)
    sprintf('Sovraelongazione: %.2f %%       |  %.2f %%', sovr_perc, sovr_perc_aw)
    sprintf('T. Assest. (1%%):  %s     |  %s', ta_str, ta_str_aw)
};

% Inserimento del box nel grafico (ho allargato la larghezza a 0.45 per farci stare tutto)
annotation('textbox', [0.15 0.65 0.45 0.22], ... 
    'String', testo_prestazioni, ...
    'EdgeColor', 'black', ...
    'BackgroundColor', 'white', ...
    'FitBoxToText', 'on', ...
    'FontSize', 10, ...
    'FontName', 'Courier New');