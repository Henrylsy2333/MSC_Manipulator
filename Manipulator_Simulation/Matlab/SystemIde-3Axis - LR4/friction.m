clc;clear;
t=0.002:0.002:10;
[b]=textread('after_dq.txt');
dq0=b(1:5000);dq1=b(5001:10000);dq2=b(10001:15000);
f=zeros(1,5000);
f= 148.5697*sign(dq0)+5.0803*dq0+90.1494*sign(dq1)+2.3764*dq1+379.1525*sign(dq2)+0.1276*dq2;
figure(1);
plot(t,f);