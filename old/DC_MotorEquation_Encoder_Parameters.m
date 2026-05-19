%% DC MOTOR PARAMETER

%clear;

%% DC MOTOR PARAMETER

L = 4.1e-3; 	% Inductance (H)
R = 3.2;     	% Resistance (Ohm) 
Km = 0.11;   	% Torque constant (Nm/A)
J = 0.352e-4; 	% Rotor Inertia(kg m2) DC motor

% I due motori hanno gli alberi calettati J=Jdc+Jbl
J=J*2;          % Inserire J Dynamo da datasheet

b =(Km*0.3)/((1750*(2*pi))/60);        	% Coefficient of friction

%% CONVERSION
RadToRpm=60/(2*pi); %Convert rad->RPM
RpmToRads = 2*pi/60;

%% OTHER
TSample=0.0001;

%% Encoder
PulseNumber = 2048*4;
RadiantsPerCount=2*pi/(PulseNumber-1);