
clc
clear all
close all
data=serialport("COM5",115200);
global datamatrix;
datamatrix=[];
global counter;
counter=0;

% 設置定時器對象
t = timer;
t.TimerFcn = @(~,~)readSerialData(data);
t.ExecutionMode = 'fixedRate';
t.Period = 0.005;

% 啟動定時器
start(t);

% 等待一分鐘
pause(60);

% 停止定時器
stop(t);
delete(data);
%disp(datamatrix);

%plot 3d ellipse
X=datamatrix(:,1);
Y=datamatrix(:,2);
Z=datamatrix(:,3);

[center, radii, evecs, pars ] = ellipsoid_fit(datamatrix,'');
[ex,ey,ez]=ellipsoid(center(1),center(2),center(3),radii(1),radii(2),radii(3));
disp(center);
disp(radii);

figure;

scatter3(X,Y,Z);
hold on;
 h = surf(ex, ey, ez);
 set(h, 'FaceColor','y');
 set(h, 'FaceAlpha', 0.3);
hold off;
function readSerialData(data)
    global datamatrix;
    global counter;
    str = readline(data); % 
    counter=counter+1;
    if(counter>7)
        str_arr = strsplit(str, ','); 
        double_arr= str2double(str_arr); 
        datamatrix = [datamatrix; double_arr]; 
        disp(double_arr);
    end
end