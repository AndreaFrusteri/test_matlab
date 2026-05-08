%% DC MOTOR PARAMETER

%clear;

%% DC MOTOR PARAMETER

L = 4.1e-3; 	% Inductance (H)
R = 3.2;     	% Resistance (Ohm) 
Km = 0.11;   	% Torque constant (Nm/A)
J = 0.352e-4; 	% Rotor Inertia(kg m2)
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

%% PI Current
G_curr = tf(1, [L R]);
[C, info] = pidtune(G_curr, 'PI')

%% PI Speed
% 1. Funzione di trasferimento meccanica: Corrente -> Velocità
% J*s*w + b*w = Km*i  => w/i = Km / (Js + b)
G_mech = tf(Km, [J b]);

% 2. Anello chiuso di corrente (Reale/Riferimento)
% Usiamo il regolatore C che hai già calcolato
T_curr = feedback(C * G_curr, 1);

% 3. Sistema visto dal regolatore di velocità
% È l'unione della risposta in corrente e della meccanica
G_speed_loop = T_curr * G_mech;

% 4. Tuning del PI di velocità
% pidtune ottimizzerà i guadagni Kp e Ki automaticamente
[C_speed, info_speed] = pidtune(G_speed_loop, 'PI');

