clc;clear;
a1=0.02;a2=0.475;a3=0.02;g=9.81;
%以下参数为仿真需要随便设置的
%a1,a2,a3为前三轴杆长
%m1,m2,m3为杆的质量
%Iixx,Iixy,Iixz,Iiyy,Iiyz,Iizz为连杆在关节坐标系下的惯性张量
%Iiyyc,Iizzc为连杆在质心坐标系下的惯性张量
%lix,liy,liz为质心位置在前相邻关节坐标系下的x,y,z分量
%g的方向与z0轴方向相反
%Xmin为待辨识的最小参数集
q=[10*(pi/180);20*(pi/180);30*(pi/180)];
dq=[1;2;3];
ddq=[0.5;1;1.5];
I1xx=0;I1xy=0;I1xz=0;I1yyc=0;I1yz=0;I1zzc=0.5;
l1x=0.5*a1;l1y=0;l1z=0;
m1=12;
rlx=l1x/m1;
I1yy=m1*(rlx^2);%平行轴定理
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
%F1s=0;F1v=0;F2s=0;F2v=0;F3s=0;F3v=0;
Xlinear=[I1xx;I1xy;I1xz;I1yy;I1yz;I1zz;l1x;l1y;l1z;m1;I2xx;I2xy;I2xz;I2yy;I2yz;I2zz;l2x;l2y;l2z;m2;I3xx;I3xy;I3xz;I3yy;I3yz;I3zz;l3x;l3y;l3z;m3;F1s;F1v;F2s;F2v;F3s;F3v];
Xmin=[I1zz+I2yy+I3yy+m2*a1^2+m3*(a1^2+a2^2);I2xx-I2yy-m3*a2^2;I2xy;I2xz-a2*l3z;I2yz;I2zz+m3*a2^2;l2x+m3*a2;l2y;I3xx-I3yy;I3xy;I3xz;I3yz;I3zz;l3x;l3y;F1s;F1v;F2s;F2v;F3s;F3v];

q0=q(1);q1=q(2);q2=q(3);
dq0=dq(1);dq1=dq(2);dq2=dq(3);
ddq0=ddq(1);ddq1=ddq(2);ddq2=ddq(3);

%tol1中各最小参数集系数
I1zz1 = ddq0;
I2xx1 = cos(q1).*(ddq0.*cos(q1) - 2*dq0.*dq1.*sin(q1));
I2xy1 = -2*dq0.*dq1.*cos(2*q1) - ddq0.*sin(2*q1);
I2xz1 = ddq1.*cos(q1) - dq1.^2.*sin(q1);
I2yy1 = sin(q1).*(2*dq0.*dq1.*cos(q1) + ddq0.*sin(q1));
I2yz1 = -(dq1.^2).*cos(q1) - ddq1.*sin(q1);
I2zz1 = 0;
l2x1 = 2*a1*(dq0.*dq1.*cos(q1) + ddq0.*sin(q1));
l2y1 = 2*a1*(ddq0.*cos(q1) - dq0.*dq1.*sin(q1));
l2z1 = 0;
m21 = a1^2.*ddq0;
I3xx1 = ddq0./2 + (ddq0.*cos(2*q1 + 2*q2))./2 - dq0.*dq1.*sin(2*q1 + 2*q2) - dq0.*dq2.*sin(2*q1 + 2*q2);
I3xy1 = - ddq0.*sin(2*q1 + 2*q2) - 2*dq0.*dq1.*cos(2*q1 + 2*q2) - 2*dq0.*dq2.*cos(2*q1 + 2*q2);
I3xz1 = - sin(q1 + q2).*dq1.^2 - 2*sin(q1 + q2).*dq1.*dq2 - sin(q1 + q2).*dq2.^2 + ddq1.*cos(q1 + q2) + ddq2.*cos(q1 + q2);
I3yy1 = ddq0./2 - (ddq0.*cos(2*q1 + 2*q2))./2 + dq0.*dq1.*sin(2*q1 + 2*q2) + dq0.*dq2.*sin(2*q1 + 2*q2);
I3yz1 = - cos(q1 + q2).*dq1.^2 - 2*cos(q1 + q2).*dq1.*dq2 - cos(q1 + q2).*dq2.^2 - ddq1.*sin(q1 + q2) - ddq2.*sin(q1 + q2);
I3zz1 = 0;
l3x1 = 2*a1*ddq0.*sin(q1 + q2) - a2*ddq0.*cos(2*q1 + q2) + a2*ddq0.*cos(q2) + 2*a1*dq0.*dq1.*cos(q1 + q2) + 2*a1*dq0.*dq2.*cos(q1 + q2) - a2*dq0.*dq2.*sin(q2) + 2*a2*dq0.*dq1.*sin(2*q1 + q2) + a2*dq0.*dq2.*sin(2*q1 + q2);
l3y1 = a2*ddq0.*sin(2*q1 + q2) - a2*ddq0.*sin(q2) + 2*a1*ddq0.*cos(q1 + q2) - 2*a1*dq0.*dq1.*sin(q1 + q2) - 2*a1*dq0.*dq2.*sin(q1 + q2) - a2*dq0.*dq2.*cos(q2) + 2*a2*dq0.*dq1.*cos(2*q1 + q2) + a2*dq0.*dq2.*cos(2*q1 + q2);
l3z1 = a2*(sin(q1).*dq1.^2 - ddq1.*cos(q1));
m31 = (a1 + a2*sin(q1)).*(a1*ddq0 + a2*ddq0.*sin(q1) + 2*a2*dq0.*dq1.*cos(q1));

H1=[ddq0',I2xx1',I2xy1',I2xz1',I2yz1',0,l2x1',l2y1',I3xx1',I3xy1',I3xz1',I3yz1',0,l3x1',l3y1',sign(dq0)',dq0',0,0,0,0];
fai1=[0,0,0,0,0,I1zz1',0,0,0,0,I2xx1',I2xy1',I2xz1',I2yy1',I2yz1',0,l2x1',l2y1',0,m21',I3xx1',I3xy1',I3xz1',I3yy1',I3yz1',0,l3x1',l3y1',l3z1',m31',sign(dq0)',dq0',0,0,0,0];
tol1=fai1*Xlinear;
tol11=H1*Xmin;
%tol1=H1*Xmin+randn(10001,1);
%tol1=ddq0.*(Xmin(1)+(cos(q1).^2)*Xmin(2)-sin(2*q1)*Xmin(3)+2*a1.*sin(q1)*Xmin(7)+2*a1.*cos(q1)*Xmin(8)+(1/2 + cos(2*q1 + 2*q2)/2)* Xmin(9)-sin(2*(q1+q2))*Xmin(10)+(a2.*cos(q2)+2*a1.*sin(q1+q2)-a2*cos(2*q1+q2))*Xmin(14)+(a2.*sin(2*q1+q2)-a2.*sin(q2)+2*a1.*cos(q1+q2))*Xmin(15))+...
%    ddq1.*(cos(q1)*Xmin(4)-sin(q1)*Xmin(5)+cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
%    ddq2.*(cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
%    -cos(q1).*2.*dq0.*dq1.*sin(q1)*Xmin(2)-2*dq0.*dq1.*cos(2*q1).*Xmin(3)-dq1.^2.*sin(q1)*Xmin(4)-(dq1.^2).*cos(q1)*Xmin(5)+2*a1*dq0.*dq1.*cos(q1)*Xmin(7)-2*a1*dq0.*dq1.*sin(q1)*Xmin(8)-(dq0.*dq1.*sin(2*q1+2*q2)+dq0.*dq2.*sin(2*q1+2*q2))*Xmin(9)-2*dq0.*(dq1+dq2).*cos(2*(q1+q2))*Xmin(10)-(sin(q1+q2).*dq1.^2+2*sin(q1+q2).*dq1.*dq2+sin(q1+q2).*dq2.^2)*Xmin(11)+...
%    -((dq1+dq2).^2).*cos(q1+q2)*Xmin(12)+(2*a1*dq0.*dq1.*cos(q1+q2)+2*a1*dq0.*dq2.*cos(q1+q2)-a2*dq0.*dq2.*sin(q2)+2*a2*dq0.*dq1.*sin(2*q1+q2)+a2*dq0.*dq2.*sin(2*q1+q2))*Xmin(14)+(-2*a1*dq0.*dq1.*sin(q1+q2)-2*a1*dq0.*dq2.*sin(q1+q2)-a2*dq0.*dq2.*cos(q2)+2*a2*dq0.*dq1.*cos(2*q1+q2)+a2*dq0.*dq2.*cos(2*q1+q2))*Xmin(15)+...
%    sign(dq0)*Xmin(16)+dq0*Xmin(17);

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
H2=[0,I2xx1',I2xy1',I2xz1',0,I2zz1',l2x1',l2y1',I3xx1',I3xy1',I3xz1',I3yz1',I3zz1',l3x1',l3y1',0,0,sign(dq1)',dq1',0,0];
fai2=[0,0,0,0,0,0,0,0,0,0,I2xx1',I2xy1',I2xz1',I2yy1',0,I2zz1',l2x1',l2y1',0,0,I3xx1',I3xy1',I3xz1',I3yy1',I3yz1',I3zz1',l3x1',l3y1',l3z1',m31',0,0,sign(dq1)',dq1',0,0];
tol2=fai2*Xlinear;
tol21=H2*Xmin;
%tol2=ddq0.*(cos(q1)*Xmin(4)+cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
%     ddq1.*(Xmin(6)+Xmin(13)+2*a2.*cos(q2)*Xmin(14)- 2*a2.*sin(q2)*Xmin(15))+...
%     ddq2.*(Xmin(13)+a2.*cos(q2)*Xmin(14)- a2.*sin(q2)*Xmin(15))+...
%    (dq0.^2).*cos(q1).*sin(q1)*Xmin(2)+(dq0.^2).*cos(2*q1)*Xmin(3)-a1*(dq0.^2).*cos(q1)*Xmin(7)+a1*(dq0.^2).*sin(q1)*Xmin(8)+((dq0.^2).*sin(2*(q1+q2)))/2*Xmin(9)+(dq0.^2).*cos(2*(q1+q2))*Xmin(10)+(-a1*dq0.^2.*cos(q1+q2)-a2*dq2.^2.*sin(q2)-a2*dq0.^2.*sin(2*q1+q2)-2*a2*dq1.*dq2.*sin(q2))*Xmin(14)+(a1*dq0.^2.*sin(q1+q2)-a2*dq2.^2.*cos(q2)-a2*dq0.^2.*cos(2*q1+q2)-2*a2*dq1.*dq2.*cos(q2))*Xmin(15)+...
%     -g*sin(q1)*Xmin(7)-g*cos(q1)*Xmin(8)- g*sin(q1+q2)*Xmin(14)- g*cos(q1+q2)*Xmin(15)+...
%    sign(dq1)*Xmin(18)+dq1*Xmin(19);
    
I3xx1 = 0.5*dq0.^2.*sin(2*(q1 + q2));
I3xy1 = dq0.^2.*cos(2*(q1 + q2));
I3xz1 = ddq0.*cos(q1 + q2);
I3yy1 = -0.5*dq0.^2.*sin(2*(q1 + q2));
I3yz1 = -ddq0.*sin(q1 + q2);
I3zz1 = ddq1 + ddq2;
l3x1 = sin(q2).*(a2*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1)) - cos(q2).*(g*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1));
l3y1 = sin(q2).*(g.*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1)) + cos(q2).*(a2.*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1));
 
H3=[0,0,0,0,0,0,0,0,I3xx1',I3xy1',I3xz1',I3yz1',I3zz1',l3x1',l3y1',0,0,0,0,sign(dq2)',dq2'];
tol31=H3*Xmin;

fai3=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,I3xx1',I3xy1',I3xz1',I3yy1',I3yz1',I3zz1',l3x1',l3y1',0,0,0,0,0,0,sign(dq2)',dq2'];
tol3=fai3*Xlinear;
%tol3=ddq0.*(cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12))+...
%     +ddq1.*(Xmin(13)+a2.*cos(q2)*Xmin(14)-a2.*sin(q2)*Xmin(15))+...
%     +ddq2.*(Xmin(13))+...
%     +0.5*dq0.^2.*sin(2*(q1+q2))*Xmin(9)+dq0.^2.*cos(2*(q1+q2))*Xmin(10)+(cos(q2).*(a2*(-cos(q1)).*sin(q1).*dq0.^2-a1*dq0.^2.*cos(q1))-sin(q2).*(-a2.*(dq0.^2.*sin(q1).^2+dq1.^2)-a1*dq0.^2.*sin(q1)))*Xmin(14)+...
%     +(-sin(q2).*(a2*(-cos(q1).*sin(q1).*dq0.^2)-a1*dq0.^2.*cos(q1))-cos(q2).*(-a2.*(dq0.^2.*sin(q1).^2+dq1.^2)-a1*dq0.^2.*sin(q1)))*Xmin(15)+...
%     -g*(sin(q1).*cos(q2)+sin(q2).*cos(q1))*Xmin(14)- g*(-sin(q1).*sin(q2)+cos(q2).*cos(q1))*Xmin(15)+...
%     +sign(dq2)*Xmin(20)+dq2*Xmin(21);
 %求取M,C,G矩阵
 Xmin=[I1zz+I2yy+I3yy+m2*a1^2+m3*(a1^2+a2^2);I2xx-I2yy-m3*a2^2;I2xy;I2xz-a2*l3z;I2yz;I2zz+m3*a2^2;l2x+m3*a2;l2y;I3xx-I3yy;I3xy;I3xz;I3yz;I3zz;l3x;l3y;F1s;F1v;F2s;F2v;F3s;F3v];
 m11=Xmin(1)+(cos(q1)^2)*Xmin(2)-sin(2*q1)*Xmin(3)+2*a1*sin(q1)*Xmin(7)+2*a1*cos(q1)*Xmin(8)+(1/2+cos(2*q1+2*q2)/2)* Xmin(9)-sin(2*(q1+q2))*Xmin(10)+(a2.*cos(q2)+2*a1.*sin(q1+q2)-a2*cos(2*q1+q2))*Xmin(14)+(a2*sin(2*q1+q2)-a2*sin(q2)+2*a1*cos(q1+q2))*Xmin(15);
 m12=cos(q1)*Xmin(4)-sin(q1)*Xmin(5)+cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12);
 m13=cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12);
 m21=cos(q1)*Xmin(4)+cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12);
 m22=Xmin(6)+Xmin(13)+2*a2.*cos(q2)*Xmin(14)- 2*a2*sin(q2)*Xmin(15);
 m23=Xmin(13)+a2*cos(q2)*Xmin(14)-2*a2*sin(q2)*Xmin(15);
 m31=cos(q1+q2)*Xmin(11)-sin(q1+q2)*Xmin(12);
 m32=Xmin(13)+a2*cos(q2)*Xmin(14)-a2*sin(q2)*Xmin(15);
 m33=Xmin(13);
 c1= -cos(q1).*2.*dq0.*dq1.*sin(q1)*Xmin(2)-2*dq0.*dq1.*cos(2*q1).*Xmin(3)-dq1.^2.*sin(q1)*Xmin(4)-(dq1.^2).*cos(q1)*Xmin(5)+2*a1*dq0.*dq1.*cos(q1)*Xmin(7)-2*a1*dq0.*dq1.*sin(q1)*Xmin(8)-(dq0.*dq1.*sin(2*q1+2*q2)+dq0.*dq2.*sin(2*q1+2*q2))*Xmin(9)-2*dq0.*(dq1+dq2).*cos(2*(q1+q2))*Xmin(10)-(sin(q1+q2).*dq1.^2+2*sin(q1+q2).*dq1.*dq2+sin(q1+q2).*dq2.^2)*Xmin(11)+...
    -((dq1+dq2).^2).*cos(q1+q2)*Xmin(12)+(2*a1*dq0.*dq1.*cos(q1+q2)+2*a1*dq0.*dq2.*cos(q1+q2)-a2*dq0.*dq2.*sin(q2)+2*a2*dq0.*dq1.*sin(2*q1+q2)+a2*dq0.*dq2.*sin(2*q1+q2))*Xmin(14)+(-2*a1*dq0.*dq1.*sin(q1+q2)-2*a1*dq0.*dq2.*sin(q1+q2)-a2*dq0.*dq2.*cos(q2)+2*a2*dq0.*dq1.*cos(2*q1+q2)+a2*dq0.*dq2.*cos(2*q1+q2))*Xmin(15);
 c2=(dq0.^2).*cos(q1).*sin(q1)*Xmin(2)+(dq0.^2).*cos(2*q1)*Xmin(3)-a1*(dq0.^2).*cos(q1)*Xmin(7)+a1*(dq0.^2).*sin(q1)*Xmin(8)+((dq0.^2).*sin(2*(q1+q2)))/2*Xmin(9)+(dq0.^2).*cos(2*(q1+q2))*Xmin(10)+(-a1*dq0.^2.*cos(q1+q2)-a2*dq2.^2.*sin(q2)-a2*dq0.^2.*sin(2*q1+q2)-2*a2*dq1.*dq2.*sin(q2))*Xmin(14)+(a1*dq0.^2.*sin(q1+q2)-a2*dq2.^2.*cos(q2)-a2*dq0.^2.*cos(2*q1+q2)-2*a2*dq1.*dq2.*cos(q2))*Xmin(15);
 c3=0.5*dq0.^2.*sin(2*(q1+q2))*Xmin(9)+dq0.^2.*cos(2*(q1+q2))*Xmin(10)+(cos(q2).*(a2*(-cos(q1)).*sin(q1).*dq0.^2-a1*dq0.^2.*cos(q1))-sin(q2).*(-a2.*(dq0.^2.*sin(q1).^2+dq1.^2)-a1*dq0.^2.*sin(q1)))*Xmin(14)+...
    +(-sin(q2).*(a2*(-cos(q1).*sin(q1).*dq0.^2)-a1*dq0.^2.*cos(q1))-cos(q2).*(-a2.*(dq0.^2.*sin(q1).^2+dq1.^2)-a1*dq0.^2.*sin(q1)))*Xmin(15);
 g1=0;
 g2=(-g*sin(q1)*Xmin(7)-g*cos(q1)*Xmin(8)-g*sin(q1+q2)*Xmin(14)-g*cos(q1+q2)*Xmin(15));
 g3=(-g*(sin(q1)*cos(q2)+sin(q2)*cos(q1))*Xmin(14)- g*(-sin(q1)*sin(q2)+cos(q1)*cos(q1))*Xmin(15));
 f1=sign(dq0)*Xmin(16)+dq0*Xmin(17);
 f2=sign(dq1)*Xmin(18)+dq1*Xmin(19);
 f3=sign(dq2)*Xmin(20)+dq2*Xmin(21);
 M=[m11,m12,m13;m21,m22,m23;m31,m32,m33];C=[c1;c2;c3];G=[g1;g2;g3];f=[f1;f2;f3];
 tol=M*ddq+C+G+f;
% ddq=inv(M)*(tol-C-G-f);