SmartToyData = 'Smart_Toy_Data.csv';
S = csvread(SmartToyData);

x = S(:,1);
y = S(:,2);
z = S(:,3);
t = linspace(0,60,283);


%plot raw data over time
figure
subplot(3,1,1)
scatter(t,x)
title('Raw X Gyro Data over time')
subplot(3,1,2)
scatter(t,y)
title('Raw Y Gyro Data over time')
subplot(3,1,3)
scatter(t,z)
title('Raw Z Gyro Data over time')