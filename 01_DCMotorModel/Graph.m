%% simulation
LW = 1.1; %Line Width
MaxAxisRPM=2100; %YMax Graph
Ttot = 0.2; %Simulation time
sim('C01A_DC_MotorEquation.slx'); %Run model to collect data
%% Plot 24V input step response
figure
PP = plot(td,y);
set(PP,'LineWidth',LW)
grid
axis([0 Ttot 0 MaxAxisRPM])
xlabel('Time (sec)') %ALWAYS UNIT
ylabel('Speed (rpm)') %ALWAYS UNIT
title('Motor velocity with 24V Step input') %ALWAYS TITLE

%% check time constant
ymax = max(yc);
tmax=max(td);
yt = ymax*0.6321;
ydiff = abs(yc - yt);
[mm,yy] = min(ydiff);
tau_y = td(yy)
gain_y = ymax;
% parameters
numi = gain_y;
deni = [tau_y, 1];
gi = tf(numi,deni);
% simulation of electric dynamics
[yr,tc,] = step(gi,tmax);

% comparison
figure
plot(tc,yr,'LineWidth',LW)
hold on
plot(t,yc,'LineWidth',LW)
hold off
grid
axis([0 tmax 0 MaxAxisRPM])
xlabel('Time (sec)')
ylabel('Speed (rpm)')
title(['First Order System approximation -TimeConstant=',num2str(tau_y),'s'])