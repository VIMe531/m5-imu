clear;
clc;

%% load file
log = readmatrix('teraterm.csv');

%% set parameters
num_data = 129;

t_loop = 201*1e-03; % ループにかかる時間を定義
t_ea = t_loop * (num_data-1); % 終了時刻を定義
t_eg = t_loop * (num_data-2);
ta = 0:t_loop:t_ea;   % set time
tg = 0:t_loop:t_eg;

accX = log(:,1);    % x軸方向加速度
accY = log(:,2);    % y軸
accZ = log(:,3);    % z軸
gyroX = log(:,4);   % x軸方向角速度
gyroY = log(:,5);   % y軸
gyroZ = log(:,6);   % z軸

%% calculate angle

roll = atan2(accZ,accY);
pitch = atan2(accZ,accX);

roll = roll - pi/2;
pitch = pitch - pi/2;

theta_x(1) = (gyroX(1)+gyroX(2))*t_loop/2;
theta_y(1) = (gyroY(1)+gyroY(2))*t_loop/2;

for i=2:128
    theta_x(i) = theta_x(i-1) + (gyroX(i)+gyroX(i+1))*t_loop/2;
    theta_y(i) = theta_y(i-1) + (gyroY(i)+gyroY(i+1))*t_loop/2;
end

%{
for i=2:129
    gyroX_calc = gyroX(1:i);
    gyroY_calc = gyroY(1:i);
    theta_x(i) = trapz(gyroX_calc);
    theta_y(i) = trapz(gyroY_calc);
end
%}

theta_x = theta_x*pi/180;
theta_y = theta_y*pi/180;

%% display data

accfig = figure(1);
clf;
grid on;
hold on;
plot(ta,roll,'r');
plot(ta,pitch,'b');
xlabel('time [s]');
ylabel('angle [rad]');
legend('x-axis','y-axis','Location','best');
hold off;
grid off;

gyrofig = figure(2);
clf;
grid on;
hold on;
plot(tg,theta_x,'r');
plot(tg,theta_y,'b');
xlabel('time [s]');
ylabel('angle [rad]');
legend('x-axis','y-axis','Location','best');
hold off;
grid off;

saveas(accfig,'fig-angle-accel.emf','meta');
saveas(gyrofig,'fig-angle-gyro.emf','meta');

saveas(accfig,'fig-angle-accel.jpg');
saveas(gyrofig,'fig-angle-gyro.jpg');