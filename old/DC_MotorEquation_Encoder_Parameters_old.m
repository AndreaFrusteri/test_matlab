%% DC MOTOR PARAMETER

%clear;

%% DC MOTOR PARAMETER

L = 4.1e-3; 	% Inductance (H)
R = 3.2;     	% Resistance (Ohm) 
Km = 0.11;   	% Torque constant (Nm/A)
J = 0.352e-4; 	% Rotor Inertia(kg m2) DC motor
% J=Jdc+Jbl;
J=J*2;

b =(Km*0.3)/((1750*(2*pi))/60);        	% Coefficient of friction


%% CONVERSION
RadToRpm=60/(2*pi); %Convert rad->RPM
RpmToRads = 2*pi/60;

%%OTHER
TSample=0.0001;


%%Encoder
PulseNumber = 2048*4;
RadiantsPerCount=2*pi/(PulseNumber-1);

%% TRANSFER FUNCION
s=tf('s');
z=tf('z',TSample);
%DC Motor continuous transfer function
Gmot=tf([Km],[L*J R*J+b*L Km*Km+b*R]);
GmotInv=1/Gmot;
% I need two poles
pole1=1/(1+0.002*s);
pole2=1/(1+0.001*s);
GmotInv=GmotInv*pole1*pole1;
% GmotInv Discretization
GmotInvz=c2d(GmotInv,TSample);




