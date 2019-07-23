clc;clear;
a1=0.02;a2=0.475;a3=0.02;g=9.81;
[a]=textread('after_q.txt');
q0=a(1:5000);q1=a(5001:10000);q2=a(10001:15000);
[b]=textread('after_dq.txt');
dq0=b(1:5000);dq1=b(5001:10000);dq2=b(10001:15000);
[c]=textread('after_ddq.txt');
ddq0=c(1:5000);ddq1=c(5001:10000);ddq2=c(10001:15000);
[d]=textread('after_tol.txt');
tol1=d(1:5000);tol2=d(5001:10000);tol3=d(10001:15000);

A=zeros(5000,1);
I1zz1 = ddq0;
I2xx1 = cos(q1).*(ddq0.*cos(q1) - 2*dq0.*dq1.*sin(q1));
I2xy1 = -2*dq0.*dq1.*cos(2*q1) - ddq0.*sin(2*q1);
I2xz1 = ddq1.*cos(q1) - dq1.^2.*sin(q1);
I2yy1 = sin(q1).*(2*dq0.*dq1.*cos(q1) + ddq0.*sin(q1));
I2yz1 = -(dq1.^2).*cos(q1) - ddq1.*sin(q1);
I2zz1 = A;
l2x1 = 2*a1*(dq0.*dq1.*cos(q1) + ddq0.*sin(q1));
l2y1 = 2*a1*(ddq0.*cos(q1) - dq0.*dq1.*sin(q1));
l2z1 = A;
m21 = a1^2.*ddq0;
I3xx1 = ddq0./2 + (ddq0.*cos(2*q1 + 2*q2))./2 - dq0.*dq1.*sin(2*q1 + 2*q2) - dq0.*dq2.*sin(2*q1 + 2*q2);
I3xy1 = - ddq0.*sin(2*q1 + 2*q2) - 2*dq0.*dq1.*cos(2*q1 + 2*q2) - 2*dq0.*dq2.*cos(2*q1 + 2*q2);
I3xz1 = - sin(q1 + q2).*dq1.^2 - 2*sin(q1 + q2).*dq1.*dq2 - sin(q1 + q2).*dq2.^2 + ddq1.*cos(q1 + q2) + ddq2.*cos(q1 + q2);
I3yy1 = ddq0./2 - (ddq0.*cos(2*q1 + 2*q2))./2 + dq0.*dq1.*sin(2*q1 + 2*q2) + dq0.*dq2.*sin(2*q1 + 2*q2);
I3yz1 = - cos(q1 + q2).*dq1.^2 - 2*cos(q1 + q2).*dq1.*dq2 - cos(q1 + q2).*dq2.^2 - ddq1.*sin(q1 + q2) - ddq2.*sin(q1 + q2);
I3zz1 = A;
l3x1 = 2*a1*ddq0.*sin(q1 + q2) - a2*ddq0.*cos(2*q1 + q2) + a2*ddq0.*cos(q2) + 2*a1*dq0.*dq1.*cos(q1 + q2) + 2*a1*dq0.*dq2.*cos(q1 + q2) - a2*dq0.*dq2.*sin(q2) + 2*a2*dq0.*dq1.*sin(2*q1 + q2) + a2*dq0.*dq2.*sin(2*q1 + q2);
l3y1 = a2*ddq0.*sin(2*q1 + q2) - a2*ddq0.*sin(q2) + 2*a1*ddq0.*cos(q1 + q2) - 2*a1*dq0.*dq1.*sin(q1 + q2) - 2*a1*dq0.*dq2.*sin(q1 + q2) - a2*dq0.*dq2.*cos(q2) + 2*a2*dq0.*dq1.*cos(2*q1 + q2) + a2*dq0.*dq2.*cos(2*q1 + q2);
l3z1 = a2*(sin(q1).*dq1.^2 - ddq1.*cos(q1));
m31 = (a1 + a2*sin(q1)).*(a1*ddq0 + a2*ddq0.*sin(q1) + 2*a2*dq0.*dq1.*cos(q1));
H1=[ddq0,I2xx1,I2xy1,I2xz1,I2yz1,A,l2x1,l2y1,I3xx1,I3xy1,I3xz1,I3yz1,A,l3x1,l3y1,sign(dq0),dq0,A,A,A,A];

I2xx1 = dq0.^2.*cos(q1).*sin(q1);
I2xy1=dq0.^2.*cos(2*q1);
I2xz1 = ddq0.*cos(q1);
I2yy1 = -dq0.^2.*cos(q1).*sin(q1);
I2yz1 = -ddq0.*sin(q1);
I2zz1 = ddq1;
l2x1 = -a1*dq0.^2.*cos(q1) - g*sin(q1);
l2y1 = -g*cos(q1) + a1*dq0.^2.*sin(q1);
I3xx1 = (dq0.^2.*sin(2*(q1 + q2)))/2;
I3xy1 = dq0.^2.*cos(2*(q1 + q2));
I3xz1 = ddq0.*cos(q1 + q2);
I3yy1 = -0.5*dq0.^2.*sin(2*(q1 + q2));
I3yz1 = -ddq0.*sin(q1 + q2);
I3zz1 = ddq1 + ddq2;
l3x1 = 2*a2*ddq1.*cos(q2) - a1*dq0.^2.*cos(q1 + q2) - a2*dq2.^2.*sin(q2) - a2*dq0.^2.*sin(2*q1 + q2) - g*sin(q1 + q2) + a2*ddq2.*cos(q2) - 2*a2*dq1.*dq2.*sin(q2);
l3y1 = a1*dq0.^2.*sin(q1 + q2) - 2*a2*ddq1.*sin(q2) - a2*ddq2.*sin(q2) - g*cos(q1 + q2) - a2*dq2.^2.*cos(q2) - a2*dq0.^2.*cos(2*q1 + q2) - 2*a2*dq1.*dq2.*cos(q2);
l3z1 = -a2*ddq0.*cos(q1);
m31 = -a2*(-a2*ddq1 + g*sin(q1) + a1*dq0.^2.*cos(q1) + a2*dq0.^2.*cos(q1).*sin(q1));
H2=[A,I2xx1,I2xy1,I2xz1,A,I2zz1,l2x1,l2y1,I3xx1,I3xy1,I3xz1,I3yz1,I3zz1,l3x1,l3y1,A,A,sign(dq1),dq1,A,A];
 
I3xx1 = 0.5*dq0.^2.*sin(2*(q1 + q2));
I3xy1 = dq0.^2.*cos(2*(q1 + q2));
I3xz1 = ddq0.*cos(q1 + q2);
I3yy1 = -0.5*dq0.^2.*sin(2*(q1 + q2));
I3yz1 = -ddq0.*sin(q1 + q2);
I3zz1 = ddq1 + ddq2;
l3x1 = sin(q2).*(a2*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1)) - cos(q2).*(g*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1));
l3y1 = sin(q2).*(g.*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1)) + cos(q2).*(a2.*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1));
H3=[A,A,A,A,A,A,A,A,I3xx1,I3xy1,I3xz1,I3yz1,I3zz1,l3x1,l3y1,A,A,A,A,sign(dq2),dq2];

tol=[tol1;tol2;tol3];
FAI=[H1;H2;H3];
N=5000;
t=0.002:0.002:10;
% [~,~,~,~,~,~,tol1_1,tol2_1,tol3_1]=textread('.\test1.txt','%n%n%n%n%n%n%n%n%n');
% [~,~,~,~,~,~,tol1_2,tol2_2,tol3_2]=textread('.\test2.txt','%n%n%n%n%n%n%n%n%n');
% [~,~,~,~,~,~,tol1_3,tol2_3,tol3_3]=textread('.\test3.txt','%n%n%n%n%n%n%n%n%n');
% [~,~,~,~,~,~,tol1_4,tol2_4,tol3_4]=textread('.\test4.txt','%n%n%n%n%n%n%n%n%n');
% [~,~,~,~,~,~,tol1_5,tol2_5,tol3_5]=textread('.\test5.txt','%n%n%n%n%n%n%n%n%n');
% std_tol1=zeros(5000,1);
% std_tol2=zeros(5000,1);
% std_tol3=zeros(5000,1);
% for i=1:5000
%     std_tol1(i)=std([tol1_1(i),tol1_2(i),tol1_3(i),tol1_4(i),tol1_5(i)]);
%     std_tol2(i)=std([tol2_1(i),tol2_2(i),tol2_3(i),tol2_4(i),tol2_5(i)]);
%     std_tol3(i)=std([tol3_1(i),tol3_2(i),tol3_3(i),tol3_4(i),tol3_5(i)]);
% end
% std=diag([std_tol1;std_tol2;std_tol3]);
% D=cov(std);
% X=inv(FAI'*inv(D)*FAI)*FAI'*inv(D)*tol
X = inv(FAI'*FAI)*FAI'*tol