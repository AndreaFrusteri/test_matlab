%% MCU Parameters
% MCU frequency
MCU_Frequency = 200e6;
MCU_Period = 1/MCU_Frequency;
%PWM Switching frequency
PWM_Frequency 	= 10e3;    			
PWM_Period      = 1/PWM_Frequency;  %s  	// PWM switching time period
%PWM register
TBPRD  = uint16 (MCU_Frequency/(2*PWM_Frequency)); % Time Base Period Register

%%Sample Period
TSample=PWM_Period;

%% Analog Reading
%input sensing
ADCResolution = 2^12;
ADCCount=ADCResolution-1;
VrefADC=3;
GainVsense=4.99/(62+4.99);
GainCurrentSense=10;
RShunt=0.007;

%Current Offset
OffsetADCINC4=2296;

%%Encoder
PulseNumber = 2048*4;
RadiantsPerCount=2*pi/(PulseNumber-1);

%% CONVERSION
RadToRpm=60/(2*pi); %Convert rad->RPM
RpmToRads = 2*pi/60;

%% Filter
%Offset Current Filter
TaoFilterOffsetCurrent=1; 

% Omega filter - To Be Defined
% a= T/(T+taoFilterOmega) e b = taoFilter/(T+TaoFilter)
% Scelgo a=0.1 e b=0.9
a_filter = 0.1;
b_filter = 0.9;
TaoFilterOmega = b_filter*TSample/a_filter
%TaoFilterOmega=1000; % Choose right value <-----------------

% Costanti di tempo per i filtri (Tau)
%TaoFilterOmega = 0.015;    % 15 ms - Filtro per omegaRPM: abbastanza lento per l'encoder, veloce per la meccanica
Tau_I     = 0.001;    % 1 ms  - Filtro per Isen_A: molto veloce, taglia solo il rumore PWM ad alta frequenza
Tau_Vdc   = 0.030;    % 30 ms - Filtro per Vdc_link: lento, stabilizza la lettura ignorando i transitori di switching

%% PI Current parameters

%......