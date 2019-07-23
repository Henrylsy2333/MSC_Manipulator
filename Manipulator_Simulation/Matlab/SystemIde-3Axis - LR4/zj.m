%建立机器人模型

%        theta    d           a        alpha     
 %SL1=Link([theta(1),  0, 0 , 0])
 %SL2=Link([theta(2)+pi/2 ,0 ,0.02, -pi/2 ])
 %SL3=Link([theta(3), 0 ,  0.475 ,  0 ])
 %SL4=Link([0       0          0.02      -pi/2       0     ],'modified');
 %SL5=Link([0     0.358         0         0         0     ],'modified');

%  SL1=Link('d', 0, 'a', 0, 'alpha', 0,'offset',0)
%  SL2=Link('d', 0, 'a', 0.02, 'alpha', pi/2,'offset',pi/2)
%  SL3=Link('d', 0, 'a', 0.475, 'alpha', 0,'offset',0)

%  SL1=Link('d', 0,     'a', 0.02,  'alpha', -pi/2 ,'offset',0,'modified');
%  SL2=Link('d', 0,     'a', 0.475, 'alpha', 0 ,    'offset',-pi/2,'modified');
%  SL3=Link('d', 0,     'a', 0.02,  'alpha', -pi/2, 'offset',0,'modified');
%  SL4=Link('d', 0.358, 'a', 0,     'alpha', 0,     'offset',0,'modified');
 SL1=Link('d', 0,     'a', 0,  'alpha', 0 ,'offset',0,'modified');
 SL2=Link('d', 0,     'a', 0.02, 'alpha', -pi/2 ,    'offset',-pi/2,'modified');
 SL3=Link('d', 0,     'a', 0.475,'alpha', 0, 'offset',0,'modified');
 SL4=Link('d', 0.358, 'a', 0.02, 'alpha', -pi/2,     'offset',0,'modified');
robot=SerialLink([SL1 SL2 SL3 SL4],'name','niaho')
%robot.fkine([0,0,0,0])
%%
a11 = -0.179050039083530;
b11 = 0.337912333425078;
a21 = 0.171887386116034;
b21 = -0.255559293055933;
a31 = -0.00651380374948211;
b31 = 0.0161055968145125;
a41 = 0.00147549492961256;
b41 = 0.000986457276365859;
a51 = 0.0122009617873660;
b51 = 0.0241887266275576;
q10 = 0.351072852429105;
a12 = 0.120217977915298;
b12 = -0.193015432622764;
a22 = 0.207065997472404;
b22 = -0.00241651400116285;
a32 = -0.328343700288920;
b32 = 0.0653126607113350;
a42 = 0.00105579744962090;
b42 = -0.00128536819297304;
a52 = 3.92745159661630e-06;
b52 = 0.00141039025259553;
q20 = -0.274529650621940;
a13 = 0.0417608793421279;
b13 = 0.0386035679949555;
a23 = -0.0640166429219427;
b23 = -0.332581363160303;
a33 = -0.0328662306566923;
b33 = 0.154562650500395;
a43 = 0.0225016334795022;
b43 = 0.0746750790992369;
a53 = 0.0326203607570049;
b53 = -0.0271658219144967;
q30 = -0.100157199917764;

t=0:0.002:10;
wf=0.2*pi;
q0=((q10+a11/wf*sin(wf*t)-b11/wf*cos(wf*t)+a21/(2*wf)*sin(2*wf*t)-b21/(2*wf)*cos(2*wf*t)+a31/(3*wf)*sin(3*wf*t)-b31/(3*wf)*cos(3*wf*t)+a41/(4*wf)*sin(4*wf*t)-b41/(4*wf)*cos(4*wf*t)+a51/(5*wf)*sin(5*wf*t)-b51/(5*wf)*cos(5*wf*t)))*180/pi;
q1=((q20+a12/wf*sin(wf*t)-b12/wf*cos(wf*t)+a22/(2*wf)*sin(2*wf*t)-b22/(2*wf)*cos(2*wf*t)+a32/(3*wf)*sin(3*wf*t)-b32/(3*wf)*cos(3*wf*t)+a42/(4*wf)*sin(4*wf*t)-b42/(4*wf)*cos(4*wf*t)+a52/(5*wf)*sin(5*wf*t)-b52/(5*wf)*cos(5*wf*t)))*180/pi;
q2=((q30+a13/wf*sin(wf*t)-b13/wf*cos(wf*t)+a23/(2*wf)*sin(2*wf*t)-b23/(2*wf)*cos(2*wf*t)+a33/(3*wf)*sin(3*wf*t)-b33/(3*wf)*cos(3*wf*t)+a43/(4*wf)*sin(4*wf*t)-b43/(4*wf)*cos(4*wf*t)+a53/(5*wf)*sin(5*wf*t)-b53/(5*wf)*cos(5*wf*t)))*180/pi;

%%
stat06 = zeros(4,4,5001);
   % robot.plot([0,0,0,0])
    %%
    robot;
    Q=[q0',q1',q2',zeros(length(q0),1)];
    %pp=robot.fkine(Q);
    plot(robot,Q)
%%
for i=1:5000
    %stat06(:,:,i)=robot.fkine([q0(i),q1(i),q2(i),0]);
    %plot(i,q0(i),'.r','MarkerSize',10)
    robot.plot([q0(i),q1(i),q2(i),0])

end  
%B=stat06(:,4:4:end);
%%
robot.plot([0,0,-pi/2,0])
%%
t=0:0.002:10;
figure(4);
subplot(311);
plot(t,B(1,:));
subplot(312);
plot(t,B(2,:));
subplot(313);
plot(t,B(3,:));
%T = robot.fkine([0,0,-pi/2,0])
