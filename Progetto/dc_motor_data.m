%% DC MOTOR PARAMETER

%% DC MOTOR PARAMETER

%-------------------------- Parametri da DATASHEET --------------------------%

%L = 4.1e-3; 	% Inductance (H)
%R = 3.2;     	% Resistance (Ohm) 
%Km = 0.11;   	% Torque constant (Nm/A)
%Jdc = 0.352e-4; 	% Rotor Inertia(kg m2) DC motor
%Jbl = 0.380e-4;
% I due motori hanno gli alberi calettati J=Jdc+Jbl
%J=Jdc+Jbl;          % Inserire J Dynamo da datasheet

%b =(Km*0.3)/((1750*(2*pi))/60);        	% Coefficient of friction

%tao_m=85e-3;    % Da datasheet

Cn = 0.22;          % Nominal Torque (Nm)
Km = 0.11; % (Nm/A)
Nv = 1750;          % Idle speed
Nn = 1500;          % Nominal speed in rpm 
Wn = Nn*2*pi/60;    % Nominal speed in rad/s 
In = 1.9;           % Nominal current (A)

%%-------------------------- Parametri da estimation LSQ --------------------------%

L =  0.0062;
R = 3.2545;
J = 1.0043e-04;
b = 11e-04;


% Moodel parameters

tao_m = J/b; % Calcolato

%% CONVERSION
RadToRpm=60/(2*pi); %Convert rad->RPM
RpmToRads = 2*pi/60;

%% Encoder
PulseNumber = 2048*4;
RadiantsPerCount=2*pi/(PulseNumber-1);

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

%% Filters
%Offset Current Filter
TaoFilterOffsetCurrent=1; 

% Filtraggio encoder
% a= T/(T+taoFilterOmega) e b = taoFilter/(T+TaoFilter)
% Scelgo a=0.1 e b=0.9
a_filter = 0.1;
b_filter = 0.9;
%TaoFilterOmega = b_filter*TSample/a_filter
TaoFilterOmega=5e-3;

%% PI controller

% Parametri anello corrente
tao_pid_current = 1e-3 

Kpi = L/tao_pid_current
Tii = L/R

% Parametri anello velocità
tao_pid_speed = 10*tao_pid_current;

Kpw = J/(tao_pid_speed*Km)
Tiw = tao_m

%% Discretizzazione dell'impianto
s=tf('s');          
z=tf('z',TSample);

%DC Motor continuous transfer function
Gmot=tf([Km],[L*J R*J Km*Km]);    % b == 0

%Gmot=tf([Km],[L*J R*J+b*L Km*Km+b*R]); % b != 0
Gmot=24*Gmot;

%DC Motor discrete transfer function
Gpz=c2d(Gmot,TSample)

%% DeadBeat Controller

k=1;

Dz_deadbeat = (1/Gpz)*((z^-k)/(1-(z^-k)))

%% Dahlin Controller

lambda=0.010;
Theta=0.0001;
N=floor(Theta/TSample)

%Yz= ( 1-exp(-TSample/lambda) )*z^(-N-1) / (1-z^-1)*(1-exp(-TSample/lambda)*z^-1)

Gmz= ( 1-exp(-TSample/lambda) )*z^(-N-1) / (1-exp(-TSample/lambda)*z^-1)

Dz_dahlin = 1/Gpz *(Gmz/(1-Gmz))

Dz_dahlin =minreal(Dz_dahlin)


%% Antiwindup

GammaZ = (z^2)-(z^1)+0.25

%GammaZ = [1  -1.5  0.75  -0.125];
%GammaZ = tf(GammaZ, 1, TSample);
GammaZ=40*(z-0.8)*(z-0.9)*(z-0.7)
