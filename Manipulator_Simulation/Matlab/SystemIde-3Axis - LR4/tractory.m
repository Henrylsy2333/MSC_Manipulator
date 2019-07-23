clc;clear;
wf=0.2*pi;
%x0=[0.01;0.01;0.01;0;0.01;0;-0.01;0;0;0;0.1;0.01;0.01;-0.01;0.01;0.01;0.01;-0.01;0;0;0;0;0.01;0;-0.01;0;0.01;0;-0.01;0;0;0;0];
x0=[-0.01;0.01;0.01;0;0.01;0;-0.01;0;0;0;0.1;0.01;0.01;-0.01;0;-0.01;0;-0.01;0;0;0;0;0.1;0;-0.01;0;0.01;0;-0.01;0;0;0;0];
%x0=[-0.01,0.01,0,-0.1,0.01,-0.01,-0.01,-0.01,0,0,0.01,0.1,0,-0.01,-0.1,0,0,0.01,0.01,0.01,0,0.02,0.01,0.01,-0.01,-0.01,0.01,0.02,-0.01,-0.01,0,0,0.01];
Aeq= [0,1/wf,0,1/(2*wf),0,1/(3*wf),0,1/(4*wf),0,1/(5*wf),-1, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,1/wf,0,1/(2*wf),0,1/(3*wf),0,1/(4*wf),0,1/(5*wf),-1, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,1/wf,0,1/(2*wf),0,1/(3*wf),0,1/(4*wf),0,1/(5*wf),-1;...
      1,0,1,0,1,0,1,0,1,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 1,0,1,0,1,0,1,0,1,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 1,0,1,0,1,0,1,0,1,0,0;...
      0,wf,0,2*wf,0,3*wf,0,4*wf,0,5*wf,0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,wf,0,2*wf,0,3*wf,0,4*wf,0,5*wf,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 0,wf,0,2*wf,0,3*wf,0,4*wf,0,5*wf,0;...
      1/wf*sin(wf*10),-1/wf*cos(wf*10),1/(2*wf)*sin(2*wf*10),-1/(2*wf)*cos(2*wf*10),1/(3*wf)*sin(3*wf*10),-1/(3*wf)*cos(3*wf*10),1/(4*wf)*sin(4*wf*10),-1/(4*wf)*cos(4*wf*10),1/(5*wf)*sin(5*wf*10),-1/(5*wf)*cos(5*wf*10),1, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 1/wf*sin(wf*10),-1/wf*cos(wf*10),1/(2*wf)*sin(2*wf*10),-1/(2*wf)*cos(2*wf*10),1/(3*wf)*sin(3*wf*10),-1/(3*wf)*cos(3*wf*10),1/(4*wf)*sin(4*wf*10),-1/(4*wf)*cos(4*wf*10),1/(5*wf)*sin(5*wf*10),-1/(5*wf)*cos(5*wf*10),1, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, 1/wf*sin(wf*10),-1/wf*cos(wf*10),1/(2*wf)*sin(2*wf*10),-1/(2*wf)*cos(2*wf*10),1/(3*wf)*sin(3*wf*10),-1/(3*wf)*cos(3*wf*10),1/(4*wf)*sin(4*wf*10),-1/(4*wf)*cos(4*wf*10),1/(5*wf)*sin(5*wf*10),-1/(5*wf)*cos(5*wf*10),1;...
      cos(wf*10),sin(wf*10),cos(2*wf*10),sin(2*wf*10),cos(3*wf*10),sin(3*wf*10),cos(4*wf*10),sin(4*wf*10),cos(5*wf*10),sin(5*wf*10),0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, cos(wf*10),sin(wf*10),cos(2*wf*10),sin(2*wf*10),cos(3*wf*10),sin(3*wf*10),cos(4*wf*10),sin(4*wf*10),cos(5*wf*10),sin(5*wf*10),0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, cos(wf*10),sin(wf*10),cos(2*wf*10),sin(2*wf*10),cos(3*wf*10),sin(3*wf*10),cos(4*wf*10),sin(4*wf*10),cos(5*wf*10),sin(5*wf*10),0;...
      -wf*sin(wf*10),wf*cos(wf*10),-(2*wf)*sin(2*wf*10),(2*wf)*cos(2*wf*10),-(3*wf)*sin(3*wf*10),(3*wf)*cos(3*wf*10),-(4*wf)*sin(4*wf*10),(4*wf)*cos(4*wf*10),-(5*wf)*sin(5*wf*10),(5*wf)*cos(5*wf*10),0, 0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, -wf*sin(wf*10),wf*cos(wf*10),-(2*wf)*sin(2*wf*10),(2*wf)*cos(2*wf*10),-(3*wf)*sin(3*wf*10),(3*wf)*cos(3*wf*10),-(4*wf)*sin(4*wf*10),(4*wf)*cos(4*wf*10),-(5*wf)*sin(5*wf*10),(5*wf)*cos(5*wf*10),0, 0,0,0,0,0,0,0,0,0,0,0;...
      0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0, -wf*sin(wf*10),wf*cos(wf*10),-(2*wf)*sin(2*wf*10),(2*wf)*cos(2*wf*10),-(3*wf)*sin(3*wf*10),(3*wf)*cos(3*wf*10),-(4*wf)*sin(4*wf*10),(4*wf)*cos(4*wf*10),-(5*wf)*sin(5*wf*10),(5*wf)*cos(5*wf*10),0];
beq=zeros(18,1);
lb=[-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-170*pi/180,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-87*pi/180,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-210*pi/180];
ub=[inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,170*pi/180,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,122*pi/180,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,50*pi/180];
A=[];b=[];
nonlcon = @unitdisk;
[x,fval,exitflag,output]=fmincon(@fun,x0,A,b,Aeq,beq,lb,ub,nonlcon);
%x=[a11,b11,a21,b21,a31,b31,a41,b41,a51,b51,q10,a12,b12,a22,b22,a32,b32,a42,b42,a52,b52,q20,a13,b13,a23,b23,a33,b33,a43,b43,a53,b53,q30];
a11=x(1);b11=x(2);a21=x(3);b21=x(4);a31=x(5);b31=x(6);a41=x(7);b41=x(8);a51=x(9);b51=x(10);q10=x(11);
a12=x(12);b12=x(13);a22=x(14);b22=x(15);a32=x(16);b32=x(17);a42=x(18);b42=x(19);a52=x(20);b52=x(21);q20=x(22);
a13=x(23);b13=x(24);a23=x(25);b23=x(26);a33=x(27);b33=x(28);a43=x(29);b43=x(30);a53=x(31);b53=x(32);q30=x(33);

t=0:0.002:10;
q0=((q10+a11/wf*sin(wf*t)-b11/wf*cos(wf*t)+a21/(2*wf)*sin(2*wf*t)-b21/(2*wf)*cos(2*wf*t)+a31/(3*wf)*sin(3*wf*t)-b31/(3*wf)*cos(3*wf*t)+a41/(4*wf)*sin(4*wf*t)-b41/(4*wf)*cos(4*wf*t)+a51/(5*wf)*sin(5*wf*t)-b51/(5*wf)*cos(5*wf*t)))*180/pi;
dq0=((a11*cos(wf*t)+b11*sin(wf*t)+a21*cos(2*wf*t)+b21*sin(2*wf*t)+a31*cos(3*wf*t)+b31*sin(3*wf*t)+a41*cos(4*wf*t)+b41*sin(4*wf*t)+a51*cos(5*wf*t)+b51*sin(5*wf*t)))*180/pi;
ddq0=((-a11*wf*sin(wf*t)+b11*wf*cos(wf*t)-a21*2*wf*sin(2*wf*t)+b21*2*wf*cos(2*wf*t)-a31*3*wf*sin(3*wf*t)+b31*3*wf*cos(3*wf*t)-a41*4*wf*sin(4*wf*t)+b41*4*wf*cos(4*wf*t)-a51*5*wf*sin(5*wf*t)+b51*5*wf*cos(5*wf*t)))*180/pi;
q1=((q20+a12/wf*sin(wf*t)-b12/wf*cos(wf*t)+a22/(2*wf)*sin(2*wf*t)-b22/(2*wf)*cos(2*wf*t)+a32/(3*wf)*sin(3*wf*t)-b32/(3*wf)*cos(3*wf*t)+a42/(4*wf)*sin(4*wf*t)-b42/(4*wf)*cos(4*wf*t)+a52/(5*wf)*sin(5*wf*t)-b52/(5*wf)*cos(5*wf*t)))*180/pi;
dq1=((a12*cos(wf*t)+b12*sin(wf*t)+a22*cos(2*wf*t)+b22*sin(2*wf*t)+a32*cos(3*wf*t)+b32*sin(3*wf*t)+a42*cos(4*wf*t)+b42*sin(4*wf*t)+a52*cos(5*wf*t)+b52*sin(5*wf*t)))*180/pi;
ddq1=((-a12*wf*sin(wf*t)+b12*wf*cos(wf*t)-a22*2*wf*sin(2*wf*t)+b22*2*wf*cos(2*wf*t)-a32*3*wf*sin(3*wf*t)+b32*3*wf*cos(3*wf*t)-a42*4*wf*sin(4*wf*t)+b42*4*wf*cos(4*wf*t)-a52*5*wf*sin(5*wf*t)+b52*5*wf*cos(5*wf*t)))*180/pi;
q2=((q30+a13/wf*sin(wf*t)-b13/wf*cos(wf*t)+a23/(2*wf)*sin(2*wf*t)-b23/(2*wf)*cos(2*wf*t)+a33/(3*wf)*sin(3*wf*t)-b33/(3*wf)*cos(3*wf*t)+a43/(4*wf)*sin(4*wf*t)-b43/(4*wf)*cos(4*wf*t)+a53/(5*wf)*sin(5*wf*t)-b53/(5*wf)*cos(5*wf*t)))*180/pi;
dq2=((a13*cos(wf*t)+b13*sin(wf*t)+a23*cos(2*wf*t)+b23*sin(2*wf*t)+a33*cos(3*wf*t)+b33*sin(3*wf*t)+a43*cos(4*wf*t)+b43*sin(4*wf*t)+a53*cos(5*wf*t)+b53*sin(5*wf*t)))*180/pi;
ddq2=((-a13*wf*sin(wf*t)+b13*wf*cos(wf*t)-a23*2*wf*sin(2*wf*t)+b23*2*wf*cos(2*wf*t)-a33*3*wf*sin(3*wf*t)+b33*3*wf*cos(3*wf*t)-a43*4*wf*sin(4*wf*t)+b43*4*wf*cos(4*wf*t)-a53*5*wf*sin(5*wf*t)+b53*5*wf*cos(5*wf*t)))*180/pi;
figure(1);
subplot(311);
plot(t,q0);
subplot(312);
plot(t,q1);
subplot(313);
plot(t,q2);
figure(2);
subplot(311);
plot(t,dq0);
subplot(312);
plot(t,dq1);
subplot(313);
plot(t,dq2);
figure(3);
subplot(311);
plot(t,ddq0);
subplot(312);
plot(t,ddq1);
subplot(313);
plot(t,ddq2);
fid = fopen('para.txt','wt');
fprintf(fid,'%g\n',x);
fclose(fid);
function f=fun(x)
wf=0.2*pi;
t=0:0.002:10;
g=9.81;
a1=0.02;a2=0.475;a3=0.02;
A=zeros(5001,1);
q0=x(11)+x(1)/wf*sin(wf*t)-x(2)/wf*cos(wf*t)+x(3)/(2*wf)*sin(2*wf*t)-x(4)/(2*wf)*cos(2*wf*t)+x(5)/(3*wf)*sin(3*wf*t)-x(6)/(3*wf)*cos(3*wf*t)+x(7)/(4*wf)*sin(4*wf*t)-x(8)/(4*wf)*cos(4*wf*t)+x(9)/(5*wf)*sin(5*wf*t)-x(10)/(5*wf)*cos(5*wf*t);
dq0=x(1)*cos(wf*t)+x(2)*sin(wf*t)+x(3)*cos(2*wf*t)+x(4)*sin(2*wf*t)+x(5)*cos(3*wf*t)+x(6)*sin(3*wf*t)+x(7)*cos(4*wf*t)+x(8)*sin(4*wf*t)+x(9)*cos(5*wf*t)+x(10)*sin(5*wf*t);
ddq0=-x(1)*wf*sin(wf*t)+x(2)*wf*cos(wf*t)-x(3)*2*wf*sin(2*wf*t)+x(4)*2*wf*cos(2*wf*t)-x(5)*3*wf*sin(3*wf*t)+x(6)*3*wf*cos(3*wf*t)-x(7)*4*wf*sin(4*wf*t)+x(8)*4*wf*cos(4*wf*t)-x(9)*5*wf*sin(5*wf*t)+x(10)*5*wf*cos(5*wf*t);

q1=x(22)+x(12)/wf*sin(wf*t)-x(13)/wf*cos(wf*t)+x(14)/(2*wf)*sin(2*wf*t)-x(15)/(2*wf)*cos(2*wf*t)+x(16)/(3*wf)*sin(3*wf*t)-x(17)/(3*wf)*cos(3*wf*t)+x(18)/(4*wf)*sin(4*wf*t)-x(19)/(4*wf)*cos(4*wf*t)+x(20)/(5*wf)*sin(5*wf*t)-x(21)/(5*wf)*cos(5*wf*t);
dq1=x(12)*cos(wf*t)+x(13)*sin(wf*t)+x(14)*cos(2*wf*t)+x(15)*sin(2*wf*t)+x(16)*cos(3*wf*t)+x(17)*sin(3*wf*t)+x(18)*cos(4*wf*t)+x(19)*sin(4*wf*t)+x(20)*cos(5*wf*t)+x(21)*sin(5*wf*t);
ddq1=x(12)*wf*sin(wf*t)+x(13)*wf*cos(wf*t)-x(14)*2*wf*sin(2*wf*t)+x(15)*2*wf*cos(2*wf*t)-x(16)*3*wf*sin(3*wf*t)+x(17)*3*wf*cos(3*wf*t)-x(18)*4*wf*sin(4*wf*t)+x(19)*4*wf*cos(4*wf*t)-x(20)*5*wf*sin(5*wf*t)+x(21)*5*wf*cos(5*wf*t);

q2=x(33)+x(23)/wf*sin(wf*t)-x(24)/wf*cos(wf*t)+x(25)/(2*wf)*sin(2*wf*t)-x(26)/(2*wf)*cos(2*wf*t)+x(27)/(3*wf)*sin(3*wf*t)-x(28)/(3*wf)*cos(3*wf*t)+x(29)/(4*wf)*sin(4*wf*t)-x(30)/(4*wf)*cos(4*wf*t)+x(31)/(5*wf)*sin(5*wf*t)-x(32)/(5*wf)*cos(5*wf*t);
dq2=x(23)*cos(wf*t)+x(24)*sin(wf*t)+x(25)*cos(2*wf*t)+x(26)*sin(2*wf*t)+x(27)*cos(3*wf*t)+x(28)*sin(3*wf*t)+x(29)*cos(4*wf*t)+x(30)*sin(4*wf*t)+x(31)*cos(5*wf*t)+x(32)*sin(5*wf*t);
ddq2=-x(23)*wf*sin(wf*t)+x(24)*wf*cos(wf*t)-x(25)*2*wf*sin(2*wf*t)+x(26)*2*wf*cos(2*wf*t)-x(27)*3*wf*sin(3*wf*t)+x(28)*3*wf*cos(3*wf*t)-x(29)*4*wf*sin(4*wf*t)+x(30)*4*wf*cos(4*wf*t)-x(31)*5*wf*sin(5*wf*t)+x(32)*5*wf*cos(5*wf*t);

I11zz1 = ddq0;
I12xx1 = cos(q1).*(ddq0.*cos(q1) - 2*dq0.*dq1.*sin(q1));
I12xy1 = -2*dq0.*dq1.*cos(2*q1) - ddq0.*sin(2*q1);
I12xz1 = ddq1.*cos(q1) - dq1.^2.*sin(q1);
I12yy1 = sin(q1).*(2*dq0.*dq1.*cos(q1) + ddq0.*sin(q1));
I12yz1 = -(dq1.^2).*cos(q1) - ddq1.*sin(q1);
I12zz1 = A;
l12x1 = 2*a1*(dq0.*dq1.*cos(q1) + ddq0.*sin(q1));
l12y1 = 2*a1*(ddq0.*cos(q1) - dq0.*dq1.*sin(q1));
l12z1 = A;
m121 = a1^2.*ddq0;
I13xx1 = ddq0./2 + (ddq0.*cos(2*q1 + 2*q2))./2 - dq0.*dq1.*sin(2*q1 + 2*q2) - dq0.*dq2.*sin(2*q1 + 2*q2);
I13xy1 = - ddq0.*sin(2*q1 + 2*q2) - 2*dq0.*dq1.*cos(2*q1 + 2*q2) - 2*dq0.*dq2.*cos(2*q1 + 2*q2);
I13xz1 = - sin(q1 + q2).*dq1.^2 - 2*sin(q1 + q2).*dq1.*dq2 - sin(q1 + q2).*dq2.^2 + ddq1.*cos(q1 + q2) + ddq2.*cos(q1 + q2);
I13yy1 = ddq0./2 - (ddq0.*cos(2*q1 + 2*q2))./2 + dq0.*dq1.*sin(2*q1 + 2*q2) + dq0.*dq2.*sin(2*q1 + 2*q2);
I13yz1 = - cos(q1 + q2).*dq1.^2 - 2*cos(q1 + q2).*dq1.*dq2 - cos(q1 + q2).*dq2.^2 - ddq1.*sin(q1 + q2) - ddq2.*sin(q1 + q2);
I13zz1 = A;
l13x1 = 2*a1*ddq0.*sin(q1 + q2) - a2*ddq0.*cos(2*q1 + q2) + a2*ddq0.*cos(q2) + 2*a1*dq0.*dq1.*cos(q1 + q2) + 2*a1*dq0.*dq2.*cos(q1 + q2) - a2*dq0.*dq2.*sin(q2) + 2*a2*dq0.*dq1.*sin(2*q1 + q2) + a2*dq0.*dq2.*sin(2*q1 + q2);
l13y1 = a2*ddq0.*sin(2*q1 + q2) - a2*ddq0.*sin(q2) + 2*a1*ddq0.*cos(q1 + q2) - 2*a1*dq0.*dq1.*sin(q1 + q2) - 2*a1*dq0.*dq2.*sin(q1 + q2) - a2*dq0.*dq2.*cos(q2) + 2*a2*dq0.*dq1.*cos(2*q1 + q2) + a2*dq0.*dq2.*cos(2*q1 + q2);
l13z1 = a2*(sin(q1).*dq1.^2 - ddq1.*cos(q1));
m131 = (a1 + a2*sin(q1)).*(a1*ddq0 + a2*ddq0.*sin(q1) + 2*a2*dq0.*dq1.*cos(q1));
I22xx1 = dq0.^2.*cos(q1).*sin(q1);
I22xy1=dq0.^2.*cos(2*q1);
I22xz1 = ddq0.*cos(q1);
I22yy1 = -dq0.^2.*cos(q1).*sin(q1);
I22yz1 = -ddq0.*sin(q1);
I22zz1 = ddq1;
l22x1 = -a1*dq0.^2.*cos(q1) - g*sin(q1);
l22y1 = -g*cos(q1) + a1*dq0.^2.*sin(q1);
I23xx1 = (dq0.^2.*sin(2*(q1 + q2)))/2;
I23xy1 = dq0.^2.*cos(2*(q1 + q2));
I23xz1 = ddq0.*cos(q1 + q2);
I23yy1 = -0.5*dq0.^2.*sin(2*(q1 + q2));
I23yz1 = -ddq0.*sin(q1 + q2);
I23zz1 = ddq1 + ddq2;
l23x1 = 2*a2*ddq1.*cos(q2) - a1*dq0.^2.*cos(q1 + q2) - a2*dq2.^2.*sin(q2) - a2*dq0.^2.*sin(2*q1 + q2) - g*sin(q1 + q2) + a2*ddq2.*cos(q2) - 2*a2*dq1.*dq2.*sin(q2);
l23y1 = a1*dq0.^2.*sin(q1 + q2) - 2*a2*ddq1.*sin(q2) - a2*ddq2.*sin(q2) - g*cos(q1 + q2) - a2*dq2.^2.*cos(q2) - a2*dq0.^2.*cos(2*q1 + q2) - 2*a2*dq1.*dq2.*cos(q2);
l23z1 = -a2*ddq0.*cos(q1);
m231 = -a2*(-a2*ddq1 + g*sin(q1) + a1*dq0.^2.*cos(q1) + a2*dq0.^2.*cos(q1).*sin(q1));
I33xx1 = 0.5*dq0.^2.*sin(2*(q1 + q2));
I33xy1 = dq0.^2.*cos(2*(q1 + q2));
I33xz1 = ddq0.*cos(q1 + q2);
I33yy1 = -0.5*dq0.^2.*sin(2*(q1 + q2));
I33yz1 = -ddq0.*sin(q1 + q2);
I33zz1 = ddq1 + ddq2;
l33x1 = sin(q2).*(a2*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1)) - cos(q2).*(g*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1));
l33y1 = sin(q2).*(g.*sin(q1) - a2*(- cos(q1).*sin(q1).*dq0.^2 + ddq1) + a1*dq0.^2.*cos(q1)) + cos(q2).*(a2.*(dq0.^2.*sin(q1).^2 + dq1.^2) - g*cos(q1) + a1*dq0.^2.*sin(q1));

H=[ddq1',I12xx1',I12xy1',I12xz1',I12yz1',A,l12x1',l12y1',I13xx1',I13xy1',I13xz1',I13yz1',A,l13x1',l13y1',sign(dq0)',dq0',A,A,A,A;...
   A,I22xx1',I22xy1',I22xz1',A,I22zz1',l22x1',l22y1',I23xx1',I23xy1',I23xz1',I23yz1',I23zz1',l23x1',l23y1',A,A,sign(dq1)',dq1',A,A;...
   A,A,A,A,A,A,A,A,I33xx1',I33xy1',I33xz1',I33yz1',I33zz1',l33x1',l33y1',A,A,A,A,sign(dq2)',dq2'];
f=cond(H,2);
end

function [c,ceq] = unitdisk(x)
wf=0.2*pi;
c=[sqrt(x(1)^2+x(2)^2)/wf+sqrt(x(3)^2+x(4)^2)/(2*wf)+sqrt(x(5)^2+x(6)^2)/(3*wf)+sqrt(x(7)^2+x(8)^2)/(4*wf)+sqrt(x(9)^2+x(10)^2)/(5*wf)+abs(x(11))-170/180*pi,...
sqrt(x(12)^2+x(13)^2)/wf+sqrt(x(14)^2+x(15)^2)/(2*wf)+sqrt(x(16)^2+x(17)^2)/(3*wf)+sqrt(x(18)^2+x(19)^2)/(4*wf)+sqrt(x(20)^2+x(21)^2)/(5*wf)+abs(x(22))-87/180*pi,...
sqrt(x(23)^2+x(24)^2)/wf+sqrt(x(25)^2+x(26)^2)/(2*wf)+sqrt(x(27)^2+x(28)^2)/(3*wf)+sqrt(x(29)^2+x(30)^2)/(4*wf)+sqrt(x(31)^2+x(32)^2)/(5*wf)+abs(x(33))-50/180*pi,...
sqrt(x(1)^2+x(2)^2)+sqrt(x(3)^2+x(4)^2)+sqrt(x(5)^2+x(6)^2)+sqrt(x(7)^2+x(8)^2)+sqrt(x(9)^2+x(10)^2)-285/180*pi,...
sqrt(x(12)^2+x(13)^2)+sqrt(x(14)^2+x(15)^2)+sqrt(x(16)^2+x(17)^2)+sqrt(x(18)^2+x(19)^2)+sqrt(x(20)^2+x(21)^2)-290/180*pi,...
sqrt(x(23)^2+x(24)^2)+sqrt(x(25)^2+x(26)^2)+sqrt(x(27)^2+x(28)^2)+sqrt(x(29)^2+x(30)^2)+sqrt(x(31)^2+x(32)^2)-370/180*pi,...
sqrt(x(1)^2+x(2)^2)*wf+sqrt(x(3)^2+x(4)^2)*2*wf+sqrt(x(5)^2+x(6)^2)*3*wf+sqrt(x(7)^2+x(8)^2)*4*wf+sqrt(x(9)^2+x(10)^2)*5*wf-60/180*pi,...
sqrt(x(12)^2+x(13)^2)*wf+sqrt(x(14)^2+x(15)^2)*2*wf+sqrt(x(16)^2+x(17)^2)*3*wf+sqrt(x(18)^2+x(19)^2)*4*wf+sqrt(x(20)^2+x(21)^2)*5*wf-60/180*pi,...
sqrt(x(23)^2+x(24)^2)*wf+sqrt(x(25)^2+x(26)^2)*2*wf+sqrt(x(27)^2+x(28)^2)*3*wf+sqrt(x(29)^2+x(30)^2)*4*wf+sqrt(x(31)^2+x(32)^2)*5*wf-90/180*pi];
ceq = [];
end