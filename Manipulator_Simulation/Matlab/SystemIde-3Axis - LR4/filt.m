clc;clear;
filename = '.\test.txt';
N=5000;
t=0.002:0.002:10;
[q0,q1,q2,dq0,dq1,dq2,tol1,tol2,tol3]=textread(filename,'%n%n%n%n%n%n%n%n%n');
h=0.002;
% fp=15;
% fs=25;  
% f_sample = 250; % the sample frequency
% Rp = 3;     % passband 纹波大小
% Rs = 60;    % stopband 纹波大小
fp=10;
fs=30;  
f_sample = 1000; % the sample frequency
Rp = 3;     % passband 纹波大小
Rs = 50;    % stopband 纹波大小
[n, wn] = buttord(2.0*fp/f_sample, 2.0*fs/f_sample, Rp, Rs);
[b,  a] = butter(n, wn);
Fq0=filtfilt(b,a,q0);
Fq1=filtfilt(b,a,q1);
Fq2=filtfilt(b,a,q2);
Fdq0=zeros(N,1);
Fdq1=zeros(N,1);
Fdq2=zeros(N,1);
ddq01=zeros(N,1);
ddq11=zeros(N,1);
ddq21=zeros(N,1);
for i=1:N-2
Fdq0(i)=(Fq0(i+2)-Fq0(i))/(2*h);
Fdq1(i)=(Fq1(i+2)-Fq1(i))/(2*h);
Fdq2(i)=(Fq2(i+2)-Fq2(i))/(2*h);
end
for i=1:N-2
ddq01(i+1)=(Fq0(i+2)-2*Fq0(i+1)+Fq0(i))/(h^2);
ddq11(i+1)=(Fq1(i+2)-2*Fq1(i+1)+Fq1(i))/(h^2);
ddq21(i+1)=(Fq2(i+2)-2*Fq2(i+1)+Fq2(i))/(h^2);
end
%对角加速度进行滤波（视具体情况而定）
Fddq0 = filtfilt(b, a, ddq01);
Fddq1 = filtfilt(b, a, ddq11);
Fddq2 = filtfilt(b, a, ddq21);
   
 %对力矩进行平滑滤波
 %fp=15;
 %fs=25;
 %fp=50;
 %fs=75;
 %f_sample = 1000; % the sample frequency
 %Rp = 3;     % passband 纹波大小
 %Rs = 60;    % stopband 纹波大小
% 可通过buttord来选取butterworth的阶次和截止频率，或者自己手工设置
 %[n, wn] = buttord(2.0*fp/f_sample, 2.0*fs/f_sample, Rp, Rs);
 %f_cutoff_tor = wn*f_sample/2.0;
 %[b,  a] = butter(n, wn);
 %filt_tol1 = filtfilt(b, a, dtol1);
 %filt_tol2 = filtfilt(b, a, dtol2);
 %filt_tol3 = filtfilt(b, a, dtol3);
rloess_tol1 = smooth(tol1, 0.03, 'rloess');
rloess_tol2 = smooth(tol2, 0.03, 'rloess');
rloess_tol3 = smooth(tol3, 0.03, 'rloess');

figure(1);
subplot(3,1,1);
plot(t,q0,'r',t,Fq0,'b');
subplot(3,1,2);
plot(t,q1,'r',t,Fq1,'b');
subplot(3,1,3);
plot(t,q2,'r',t,Fq2,'b');
% figure(2);
% subplot(3,1,1);
% plot(t,dq0,'r',t,Fdq0,'b');
% subplot(3,1,2);
% plot(t,dq1,'r',t,Fdq1,'b');
% subplot(3,1,3);
% plot(t,dq2,'r',t,Fdq2,'b');
 figure(2);
 subplot(3,1,1);
 plot(t,Fdq0);
 subplot(3,1,2);
 plot(t,Fdq1);
 subplot(3,1,3);
 plot(t,Fdq2);
figure(3);
subplot(3,1,1);
plot(t,Fddq0,'r',t,ddq01,'b');
subplot(3,1,2);
plot(t,Fddq1,'r',t,ddq11,'b');
subplot(3,1,3);
plot(t,Fddq2,'r',t,ddq21,'b');
figure(4);
subplot(3,1,1);
plot(t,tol1,'r',t,rloess_tol1,'b');
subplot(3,1,2);
plot(t,tol2,'r',t,rloess_tol2,'b');
subplot(3,1,3);
plot(t,tol3,'r',t,rloess_tol3,'b');
fid = fopen('after_q.txt','wt');
fprintf(fid,'%g\n',Fq0,Fq1,Fq2);
fclose(fid);
fid = fopen('after_dq.txt','wt');
fprintf(fid,'%g\n',Fdq0,Fdq1,Fdq2);
fclose(fid);
fid = fopen('after_ddq.txt','wt');
fprintf(fid,'%g\n',ddq01,ddq11,ddq21);
fclose(fid);
fid = fopen('after_tol.txt','wt');
fprintf(fid,'%g\n',rloess_tol1,rloess_tol2,rloess_tol3);
fclose(fid);