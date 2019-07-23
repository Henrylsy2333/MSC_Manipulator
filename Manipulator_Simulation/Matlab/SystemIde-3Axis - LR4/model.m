
a1=0.02;a2=0.475;a3=0.02;m1=12;m2=8;m3=5;
cI1xx=0;cI1yy=0;cI1zz=0.5;cI1xy=0;cI1yz=0;cI1xz=0;
cI2xx=0;cI2yy=0;cI2zz=0.2;cI2xy=0;cI2yz=0;cI2xz=0;
cI3xx=0;cI3yy=0;cI3zz=0.1;cI3xy=0;cI3yz=0;cI3xz=0;
c1x=0.5*a1/m1;c1y=0;c1z=0;
c2x=0.5*a2/m2;c2y=0;c2z=0;
c3x=0.5*a3/m3;c3y=0;c3z=0;
L(1) = RevoluteMDH('d', 0, 'a', 0, 'alpha', 0,  'offset', 0,  ...     
    'I', [cI1xx, cI1yy, cI1zz, cI1xy, cI1yz, cI1xz], ...    % 注意此处的惯性张量矩阵 I 是针对质心坐标{Ci}的，故     
    'r', [c1x, c1y, c1z], ...             % 需要通过平行轴定理将惯量折合到转轴处     
    'm', m1,...                        % 连杆质量 m
    'B', 96.14, ...                     % 粘性摩擦
    'G', 1, ...
    'Tc', [+97.26 -97.26]);          % (+) (-) 库伦摩擦);
L(2) = RevoluteMDH('d', 0, 'a', a1, 'alpha',-pi/2.0, 'offset', -pi/2.0,  ...     
    'I', [cI2xx, cI2yy, cI2zz, cI2xy, cI2yz, cI2xz], ...    % 注意此处的惯性张量矩阵 I 是针对质心坐标{Ci}的，故     
    'r', [c2x, c2y, c2z], ...             % 需要通过平行轴定理将惯量折合到转轴处     
    'm', m2,...                        % 连杆质量 m
    'B', 65.03, ...                     % 粘性摩擦
    'G', 1, ...
    'Tc', [+1.03 -1.03]);          % (+) (-) 库伦摩擦);
L(3) = RevoluteMDH('d', 0, 'a', a2, 'alpha', 0, 'offset',0, ...     
    'I', [cI3xx, cI3yy, cI3zz, cI3xy, cI3yz, cI3xz], ...    % 注意此处的惯性张量矩阵 I 是针对质心坐标{Ci}的，故     
    'r', [c3x, c3y, c3z], ...             % 需要通过平行轴定理将惯量折合到转轴处     
    'm', m3,...                        % 连杆质量 m
    'B',19.3, ...                     % 粘性摩擦
    'G', 1, ...
    'Tc', [+33.43 -33.43]);          % (+) (-) 库伦摩擦);  
L(4) = RevoluteMDH('d', 0.358, 'a', a3, 'alpha', -pi/2.0, 'offset',0, ...     
    'I', [cI3xx, cI3yy, cI3zz, cI3xy, cI3yz, cI3xz], ...    % 注意此处的惯性张量矩阵 I 是针对质心坐标{Ci}的，故     
    'r', [c3x, c3y, c3z], ...             % 需要通过平行轴定理将惯量折合到转轴处     
    'm', m3,...                        % 连杆质量 m
    'B',19.3, ...                     % 粘性摩擦
    'G', 1, ...
    'Tc', [+33.43 -33.43]);          % (+) (-) 库伦摩擦);  
bot = SerialLink(L, ...     
    'name', 'three link');

%q=[10*(pi/180) 20*(pi/180) 30*(pi/180)];
%qd=[1 2 3];
%qdd=[0.5 1 1.5];

% wf=2*pi*0.1;
% t=0:0.001:10;
% 
% a11=0.1343;b11=-0.8042;a21=-0.1343;b21=0.4026;a31=0;b31=0;a41=0;b41=-0.0001;a51=0;b51=-0.0001;q10=-0.9596;
% a12=-0.3184;b12=0.1984;a22=0.11;b22=-0.0198;a32=0.0023;b32=0;a42=-0.0018;b42=-0.0002;a52=0.2079;b52=-0.0316;q20=0.2899;
% a13=-0.3755;b13=-0.6864;a23=0.0567;b23=0.0966;a33=0.136;b33=-0.0396;a43=0.156;b43=0.0862;a53=0.0269;b53=0.0534;q30=-0.9852;
% 
% q1temp=(q10+a11/wf*sin(wf*t)-b11/wf*cos(wf*t)+a21/(2*wf)*sin(2*wf*t)-b21/(2*wf)*cos(2*wf*t)+a31/(3*wf)*sin(3*wf*t)-b31/(3*wf)*cos(3*wf*t)+a41/(4*wf)*sin(4*wf*t)-b41/(4*wf)*cos(4*wf*t)+a51/(5*wf)*sin(5*wf*t)-b51/(5*wf)*cos(5*wf*t));
% dq1temp=(a11*cos(wf*t)+b11*sin(wf*t)+a21*cos(2*wf*t)+b21*sin(2*wf*t)+a31*cos(3*wf*t)+b31*sin(3*wf*t)+a41*cos(4*wf*t)+b41*sin(4*wf*t)+a51*cos(5*wf*t)+b51*sin(5*wf*t));
% ddq1temp=(-a11*wf*sin(wf*t)+b11*wf*cos(wf*t)-a21*2*wf*sin(2*wf*t)+b21*2*wf*cos(2*wf*t)-a31*3*wf*sin(3*wf*t)+b31*3*wf*cos(3*wf*t)-a41*4*wf*sin(4*wf*t)+b41*4*wf*cos(4*wf*t)-a51*5*wf*sin(5*wf*t)+b51*5*wf*cos(5*wf*t));
% 
% q2temp=(q20+a12/wf*sin(wf*t)-b12/wf*cos(wf*t)+a22/(2*wf)*sin(2*wf*t)-b22/(2*wf)*cos(2*wf*t)+a32/(3*wf)*sin(3*wf*t)-b32/(3*wf)*cos(3*wf*t)+a42/(4*wf)*sin(4*wf*t)-b42/(4*wf)*cos(4*wf*t)+a52/(5*wf)*sin(5*wf*t)-b52/(5*wf)*cos(5*wf*t));
% dq2temp=(a12*cos(wf*t)+b12*sin(wf*t)+a22*cos(2*wf*t)+b22*sin(2*wf*t)+a32*cos(3*wf*t)+b32*sin(3*wf*t)+a42*cos(4*wf*t)+b42*sin(4*wf*t)+a52*cos(5*wf*t)+b52*sin(5*wf*t));
% ddq2temp=(-a12*wf*sin(wf*t)+b12*wf*cos(wf*t)-a22*2*wf*sin(2*wf*t)+b22*2*wf*cos(2*wf*t)-a32*3*wf*sin(3*wf*t)+b32*3*wf*cos(3*wf*t)-a42*4*wf*sin(4*wf*t)+b42*4*wf*cos(4*wf*t)-a52*5*wf*sin(5*wf*t)+b52*5*wf*cos(5*wf*t));
% 
% q3temp=(q30+a13/wf*sin(wf*t)-b13/wf*cos(wf*t)+a23/(2*wf)*sin(2*wf*t)-b23/(2*wf)*cos(2*wf*t)+a33/(3*wf)*sin(3*wf*t)-b33/(3*wf)*cos(3*wf*t)+a43/(4*wf)*sin(4*wf*t)-b43/(4*wf)*cos(4*wf*t)+a53/(5*wf)*sin(5*wf*t)-b53/(5*wf)*cos(5*wf*t));
% dq3temp=(a13*cos(wf*t)+b13*sin(wf*t)+a23*cos(2*wf*t)+b23*sin(2*wf*t)+a33*cos(3*wf*t)+b33*sin(3*wf*t)+a43*cos(4*wf*t)+b43*sin(4*wf*t)+a53*cos(5*wf*t)+b53*sin(5*wf*t));
% ddq3temp=(-a13*wf*sin(wf*t)+b13*wf*cos(wf*t)-a23*2*wf*sin(2*wf*t)+b23*2*wf*cos(2*wf*t)-a33*3*wf*sin(3*wf*t)+b33*3*wf*cos(3*wf*t)-a43*4*wf*sin(4*wf*t)+b43*4*wf*cos(4*wf*t)-a53*5*wf*sin(5*wf*t)+b53*5*wf*cos(5*wf*t));
% 
% q1=q1temp';q2=q2temp';q3=q3temp';
% dq1=dq1temp';dq2=dq2temp';dq3=dq3temp';
% ddq1=ddq1temp';ddq2=ddq2temp';ddq3=ddq3temp';
% 
% N=length(t);
% tol=zeros(N,3);
% q=zeros(N,3);
% qd=zeros(N,3);
% qdd=zeros(N,3);
% 
% for i=1:N
% q(i,:)=[q1(i) q2(i) q3(i)];
% qd(i,:)=[dq1(i) dq2(i) dq3(i)];
% qdd(i,:)=[ddq1(i) ddq2(i) ddq3(i)];
% grav=[0;0;9.81];
% tol(i,:)=bot.rne(q(i,:),qd(i,:),qdd(i,:),grav);
% end
% 
% figure(2);
% plot(t,tol);

stat06 = zeros(4,4,5001);
for i=1:1:5001
    stat06(:,:,i)=bot.fkine([q0(i),q1(i),q2(i),0]);
    B=stat06(:,4:4:end);
end
t=0:0.002:10;
figure(4);
subplot(311);
plot(t,B(1,:));
subplot(312);
plot(t,B(2,:));
subplot(313);
plot(t,B(3,:));
