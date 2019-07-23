clc;clear;
a1=0.02;a2=0.475;a3=0.02;g=9.81;
A=zeros(5001,1);
filename = '.\para.txt';
[x]=textread(filename,'%n');

a11=x(1);b11=x(2);a21=x(3);b21=x(4);a31=x(5);b31=x(6);a41=x(7);b41=x(8);a51=x(9);b51=x(10);q10=x(11);
a12=x(12);b12=x(13);a22=x(14);b22=x(15);a32=x(16);b32=x(17);a42=x(18);b42=x(19);a52=x(20);b52=x(21);q20=x(22);
a13=x(23);b13=x(24);a23=x(25);b23=x(26);a33=x(27);b33=x(28);a43=x(29);b43=x(30);a53=x(31);b53=x(32);q30=x(33);

% a11=0.1343;b11=-0.8042;a21=-0.1343;b21=0.4026;a31=0;b31=0;a41=0;b41=-0.0001;a51=0;b51=-0.0001;q10=-0.9596;
% a12=-0.3184;b12=0.1984;a22=0.11;b22=-0.0198;a32=0.0023;b32=0;a42=-0.0018;b42=-0.0002;a52=0.2079;b52=-0.0316;q20=0.2899;
% a13=-0.3755;b13=-0.6864;a23=0.0567;b23=0.0966;a33=0.136;b33=-0.0396;a43=0.156;b43=0.0862;a53=0.0269;b53=0.0534;q30=-0.9852;

wf=2*pi*0.1;
t=0:0.002:10;
q0=(q10+a11/wf*sin(wf*t)-b11/wf*cos(wf*t)+a21/(2*wf)*sin(2*wf*t)-b21/(2*wf)*cos(2*wf*t)+a31/(3*wf)*sin(3*wf*t)-b31/(3*wf)*cos(3*wf*t)+a41/(4*wf)*sin(4*wf*t)-b41/(4*wf)*cos(4*wf*t)+a51/(5*wf)*sin(5*wf*t)-b51/(5*wf)*cos(5*wf*t));
dq0=(a11*cos(wf*t)+b11*sin(wf*t)+a21*cos(2*wf*t)+b21*sin(2*wf*t)+a31*cos(3*wf*t)+b31*sin(3*wf*t)+a41*cos(4*wf*t)+b41*sin(4*wf*t)+a51*cos(5*wf*t)+b51*sin(5*wf*t));
ddq0=(-a11*wf*sin(wf*t)+b11*wf*cos(wf*t)-a21*2*wf*sin(2*wf*t)+b21*2*wf*cos(2*wf*t)-a31*3*wf*sin(3*wf*t)+b31*3*wf*cos(3*wf*t)-a41*4*wf*sin(4*wf*t)+b41*4*wf*cos(4*wf*t)-a51*5*wf*sin(5*wf*t)+b51*5*wf*cos(5*wf*t));

q1=(q20+a12/wf*sin(wf*t)-b12/wf*cos(wf*t)+a22/(2*wf)*sin(2*wf*t)-b22/(2*wf)*cos(2*wf*t)+a32/(3*wf)*sin(3*wf*t)-b32/(3*wf)*cos(3*wf*t)+a42/(4*wf)*sin(4*wf*t)-b42/(4*wf)*cos(4*wf*t)+a52/(5*wf)*sin(5*wf*t)-b52/(5*wf)*cos(5*wf*t));
dq1=(a12*cos(wf*t)+b12*sin(wf*t)+a22*cos(2*wf*t)+b22*sin(2*wf*t)+a32*cos(3*wf*t)+b32*sin(3*wf*t)+a42*cos(4*wf*t)+b42*sin(4*wf*t)+a52*cos(5*wf*t)+b52*sin(5*wf*t));
ddq1=(-a12*wf*sin(wf*t)+b12*wf*cos(wf*t)-a22*2*wf*sin(2*wf*t)+b22*2*wf*cos(2*wf*t)-a32*3*wf*sin(3*wf*t)+b32*3*wf*cos(3*wf*t)-a42*4*wf*sin(4*wf*t)+b42*4*wf*cos(4*wf*t)-a52*5*wf*sin(5*wf*t)+b52*5*wf*cos(5*wf*t));

q2=(q30+a13/wf*sin(wf*t)-b13/wf*cos(wf*t)+a23/(2*wf)*sin(2*wf*t)-b23/(2*wf)*cos(2*wf*t)+a33/(3*wf)*sin(3*wf*t)-b33/(3*wf)*cos(3*wf*t)+a43/(4*wf)*sin(4*wf*t)-b43/(4*wf)*cos(4*wf*t)+a53/(5*wf)*sin(5*wf*t)-b53/(5*wf)*cos(5*wf*t));
dq2=(a13*cos(wf*t)+b13*sin(wf*t)+a23*cos(2*wf*t)+b23*sin(2*wf*t)+a33*cos(3*wf*t)+b33*sin(3*wf*t)+a43*cos(4*wf*t)+b43*sin(4*wf*t)+a53*cos(5*wf*t)+b53*sin(5*wf*t));
ddq2=(-a13*wf*sin(wf*t)+b13*wf*cos(wf*t)-a23*2*wf*sin(2*wf*t)+b23*2*wf*cos(2*wf*t)-a33*3*wf*sin(3*wf*t)+b33*3*wf*cos(3*wf*t)-a43*4*wf*sin(4*wf*t)+b43*4*wf*cos(4*wf*t)-a53*5*wf*sin(5*wf*t)+b53*5*wf*cos(5*wf*t));
%q3=zeros(1,10001);dq3=zeros(1,10001);ddq3=zeros(1,10001);
I1xx=0;I1xy=0;I1xz=0;I1yyc=0;I1yz=0;I1zzc=0.5;
l1x=0.5*a1;l1y=0;l1z=0;
m1=12;
rlx=l1x/m1;
I1yy=m1*(rlx^2);
I1zz=I1zzc+m1*(rlx^2);
I2xx=0;I2xy=0;I2xz=0;I2yyc=0;I2yz=0;I2zzc=0.2;
l2x=0.5*a2;l2y=0;l2z=0;
m2=8;
r2x=l2x/m2;
I2yy=m2*(r2x^2);
I2zz=I2zzc+m2*(r2x^2);
I3xx=0;I3xy=0;I3xz=0;I3yyc=0;I3yz=0;I3zzc=0.1;
l3x=0.5*a3;l3y=0;l3z=0;
m3=5;
r3x=l3x/m3;
I3yy=m3*(r3x^2);
I3zz=I3zzc+m3*(r3x^2);
F1s=97.26;F1v=96.14;F2s=1.03;F2v=65.03;F3s=33.43;F3v=19.3;
Xlinear=[I1xx;I1xy;I1xz;I1yy;I1yz;I1zz;l1x;l1y;l1z;m1;I2xx;I2xy;I2xz;I2yy;I2yz;I2zz;l2x;l2y;l2z;m2;I3xx;I3xy;I3xz;I3yy;I3yz;I3zz;l3x;l3y;l3z;m3;F1s;F1v;F2s;F2v;F3s;F3v];
Xmin=[I1zz+I2yy+I3yy+m2*a1^2+m3*(a1^2+a2^2);I2xx-I2yy-m3*a2^2;I2xy;I2xz-a2*l3z;I2yz;I2zz+m3*a2^2;l2x+m3*a2;l2y;I3xx-I3yy;I3xy;I3xz;I3yz;I3zz;l3x;l3y;F1s;F1v;F2s;F2v;F3s;F3v];
%Xmin=[9.53;28.07;-22.1;5.32;3.79;72.68;41.69;-0.93;-6.04;13.18;-9.3;-2.14;6.93;10.23;-5.21;F1s;F1v;F2s;F2v;F3s;F3v];

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

H1=[ddq0',I2xx1',I2xy1',I2xz1',I2yz1',A,l2x1',l2y1',I3xx1',I3xy1',I3xz1',I3yz1',A,l3x1',l3y1',sign(dq0)',dq0',A,A,A,A];
fai1=[A,A,A,A,A,I1zz1',A,A,A,A,I2xx1',I2xy1',I2xz1',I2yy1',I2yz1',A,l2x1',l2y1',A,m21',I3xx1',I3xy1',I3xz1',I3yy1',I3yz1',A,l3x1',l3y1',l3z1',m31',sign(dq0)',dq0',A,A,A,A];
tol1=fai1*Xlinear;
tol11=H1*Xmin;
%tol1=H1*Xmin+randn(10001,1);
tol111=ddq0.*(Xmin(1)+(cos(q1).^2)*Xmin(2)-sin(2*q1)*Xmin(3)+2*a1.*sin(q1)*Xmin(7)+2*a1.*cos(q1)*Xmin(8)+(1/2 + cos(2*q1 + 2*q2)/2)* Xmin(9)-sin(2*(q1+q2))*Xmin(10)+(a2.*cos(q2)+2*a1.*sin(q1+q2)-a2*cos(2*q1+q2))*Xmin(14)+(a2.*sin(2*q1+q2)-a2.*sin(q2)+2*a1.*cos(q1+q2))*Xmin(15))+...
   ddq1.*(cos(q1)*Xmin(4)-sin(q1)*Xmin(5)+cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
   ddq2.*(cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
   -cos(q1).*2.*dq0.*dq1.*sin(q1)*Xmin(2)-2*dq0.*dq1.*cos(2*q1).*Xmin(3)-dq1.^2.*sin(q1)*Xmin(4)-(dq1.^2).*cos(q1)*Xmin(5)+2*a1*dq0.*dq1.*cos(q1)*Xmin(7)-2*a1*dq0.*dq1.*sin(q1)*Xmin(8)-(dq0.*dq1.*sin(2*q1+2*q2)+dq0.*dq2.*sin(2*q1+2*q2))*Xmin(9)-2*dq0.*(dq1+dq2).*cos(2*(q1+q2))*Xmin(10)-(sin(q1+q2).*dq1.^2+2*sin(q1+q2).*dq1.*dq2+sin(q1+q2).*dq2.^2)*Xmin(11)+...
   -((dq1+dq2).^2).*cos(q1+q2)*Xmin(12)+(2*a1*dq0.*dq1.*cos(q1+q2)+2*a1*dq0.*dq2.*cos(q1+q2)-a2*dq0.*dq2.*sin(q2)+2*a2*dq0.*dq1.*sin(2*q1+q2)+a2*dq0.*dq2.*sin(2*q1+q2))*Xmin(14)+(-2*a1*dq0.*dq1.*sin(q1+q2)-2*a1*dq0.*dq2.*sin(q1+q2)-a2*dq0.*dq2.*cos(q2)+2*a2*dq0.*dq1.*cos(2*q1+q2)+a2*dq0.*dq2.*cos(2*q1+q2))*Xmin(15)+...
   sign(dq0)*Xmin(16)+dq0*Xmin(17);

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
H2=[A,I2xx1',I2xy1',I2xz1',A,I2zz1',l2x1',l2y1',I3xx1',I3xy1',I3xz1',I3yz1',I3zz1',l3x1',l3y1',A,A,sign(dq1)',dq1',A,A];
fai2=[A,A,A,A,A,A,A,A,A,A,I2xx1',I2xy1',I2xz1',I2yy1',A,I2zz1',l2x1',l2y1',A,A,I3xx1',I3xy1',I3xz1',I3yy1',I3yz1',I3zz1',l3x1',l3y1',l3z1',m31',A,A,sign(dq1)',dq1',A,A];
tol2=fai2*Xlinear;
tol21=H2*Xmin;
tol211=ddq0.*(cos(q1)*Xmin(4)+cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
    ddq1.*(Xmin(6)+Xmin(13)+2*a2.*cos(q2)*Xmin(14)- 2*a2.*sin(q2)*Xmin(15))+...
    ddq2.*(Xmin(13)+a2.*cos(q2)*Xmin(14)- a2.*sin(q2)*Xmin(15))+...
   (dq0.^2).*cos(q1).*sin(q1)*Xmin(2)+(dq0.^2).*cos(2*q1)*Xmin(3)-a1*(dq0.^2).*cos(q1)*Xmin(7)+a1*(dq0.^2).*sin(q1)*Xmin(8)+((dq0.^2).*sin(2*(q1+q2)))/2*Xmin(9)+(dq0.^2).*cos(2*(q1+q2))*Xmin(10)+(-a1*dq0.^2.*cos(q1+q2)-a2*dq2.^2.*sin(q2)-a2*dq0.^2.*sin(2*q1+q2)-2*a2*dq1.*dq2.*sin(q2))*Xmin(14)+(a1*dq0.^2.*sin(q1+q2)-a2*dq2.^2.*cos(q2)-a2*dq0.^2.*cos(2*q1+q2)-2*a2*dq1.*dq2.*cos(q2))*Xmin(15)+...
    -g*sin(q1)*Xmin(7)-g*cos(q1)*Xmin(8)- g*sin(q1+q2)*Xmin(14)- g*cos(q1+q2)*Xmin(15)+...
   sign(dq1)*Xmin(18)+dq1*Xmin(19);

    
I3xx1 = 0.5*dq0.^2.*sin(2*(q1 + q2));
I3xy1 = dq0.^2.*cos(2*(q1 + q2));
I3xz1 = ddq0.*cos(q1 + q2);
I3yy1 = -0.5*dq0.^2.*sin(2*(q1 + q2));
I3yz1 = -ddq0.*sin(q1 + q2);
I3zz1 = ddq1 + ddq2;
l3x1 = sin(q2).*(a2*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1)) - cos(q2).*(g*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1));
l3y1 = sin(q2).*(g.*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1)) + cos(q2).*(a2.*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1));
 
H3=[A,A,A,A,A,A,A,A,I3xx1',I3xy1',I3xz1',I3yz1',I3zz1',l3x1',l3y1',A,A,A,A,sign(dq2)',dq2'];
tol31=H3*Xmin;

fai3=[A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,I3xx1',I3xy1',I3xz1',I3yy1',I3yz1',I3zz1',l3x1',l3y1',A,A,A,A,A,A,sign(dq2)',dq2'];
tol3=fai3*Xlinear;
tol311=ddq0.*(cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
    +ddq1.*(Xmin(13)+a2.*cos(q2)*Xmin(14)-a2.*sin(q2)*Xmin(15))+...
    +ddq2.*(Xmin(13))+...
    +0.5*dq0.^2.*sin(2*(q1+q2))*Xmin(9)+dq0.^2.*cos(2*(q1+q2))*Xmin(10)+(cos(q2).*(a2*(-cos(q1)).*sin(q1).*dq0.^2-a1*dq0.^2.*cos(q1))-sin(q2).*(-a2.*(dq0.^2.*sin(q1).^2+dq1.^2)-a1*dq0.^2.*sin(q1)))*Xmin(14)+...
    +(-sin(q2).*(a2*(-cos(q1).*sin(q1).*dq0.^2)-a1*dq0.^2.*cos(q1))-cos(q2).*(-a2.*(dq0.^2.*sin(q1).^2+dq1.^2)-a1*dq0.^2.*sin(q1)))*Xmin(15)+...
    -g*(sin(q1).*cos(q2)+sin(q2).*cos(q1))*Xmin(14)- g*(-sin(q1).*sin(q2)+cos(q2).*cos(q1))*Xmin(15)+...
    +sign(dq2)*Xmin(20)+dq2*Xmin(21);

figure(1);
plot(t,tol1,t,tol2,t,tol3);
figure(2);
plot(t,tol11,t,tol21,t,tol31);
figure(3);
plot(t,tol111,t,tol211,t,tol311);
fid = fopen('tol1.txt','wt');
fprintf(fid,'%g\n',tol1);
fclose(fid);
fid = fopen('tol2.txt','wt');
fprintf(fid,'%g\n',tol2);
fclose(fid);
fid = fopen('tol3.txt','wt');
fprintf(fid,'%g\n',tol3);
fclose(fid);
% ttol1=[0:0.001:10;tol1']
% save ttol1
% ttol2=[0:0.001:10;tol2']
% save ttol2
% ttol3=[0:0.001:10;tol3']
% save ttol3