%% Inizializzazione del Workspace

close all; clear; clc;

% 1. Inizializzazione dati dinamo
mcb_pmsm_foc_qep_f28379d_data; 

% 2. Inizializzazione dati motore dc e controllori per motore dc
dc_motor_data

disp('Parametri caricati con successo nel Workspace.');

% 3. Apertura del modello Simulink
%CommandInterface
%BasePerTracing

%disp('Apertura simulink.');

%% Porta COM
comport="COM6";