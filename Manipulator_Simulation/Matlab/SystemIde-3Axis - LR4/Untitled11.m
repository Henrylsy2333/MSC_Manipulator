clc,clear
a1=0.05;a2=0.27;a3=0.07;m1=12;m2=8;m3=5;
cI1xx=0;cI1yy=0;cI1zz=0.5;cI1xy=0;cI1yz=0;cI1xz=0;
cI2xx=0;cI2yy=0;cI2zz=0.2;cI2xy=0;cI2yz=0;cI2xz=0;
cI3xx=0;cI3yy=0;cI3zz=0.1;cI3xy=0;cI3yz=0;cI3xz=0;
c1x=0.5*a1/m1;c1y=0;c1z=0;
c2x=0.5*a2/m2;c2y=0;c2z=0;
c3x=0.5*a3/m3;c3y=0;c3z=0;
L(1) = RevoluteMDH('d', 0, 'a', 0, 'alpha', 0,  'offset', 0,  ...     
    'I', [cI1xx, cI1yy, cI1zz, cI1xy, cI1yz, cI1xz], ...    % ע��˴��Ĺ����������� I �������������{Ci}�ģ���     
    'r', [c1x, c1y, c1z], ...             % ��Ҫͨ��ƽ���ᶨ�������ۺϵ�ת�ᴦ     
    'm', m1,...                        % �������� m
    'B', 20, ...     % ճ��Ħ�� 
    'G', 1, ...
    'Tc', [+2 -2]);          % (+) (-) ����Ħ��);
L(2) = RevoluteMDH('d', 0, 'a', a1, 'alpha',-pi/2.0, 'offset', -pi/2.0,  ...     
    'I', [cI2xx, cI2yy, cI2zz, cI2xy, cI2yz, cI2xz], ...    % ע��˴��Ĺ����������� I �������������{Ci}�ģ���     
    'r', [c2x, c2y, c2z], ...             % ��Ҫͨ��ƽ���ᶨ�������ۺϵ�ת�ᴦ     
    'm', m2,...                        % �������� m
    'B', 0, ...                     % ճ��Ħ��     
        'G', 1, ...
    'Tc', [+1 -1]);          % (+) (-) ����Ħ��);
L(3) = RevoluteMDH('d', 0, 'a', a2, 'alpha', 0, 'offset',pi/2, ...     
    'I', [cI3xx, cI3yy, cI3zz, cI3xy, cI3yz, cI3xz], ...    % ע��˴��Ĺ����������� I �������������{Ci}�ģ���     
    'r', [c3x, c3y, c3z], ...             % ��Ҫͨ��ƽ���ᶨ�������ۺϵ�ת�ᴦ     
    'm', m3,...                        % �������� m
    'B',0, ...                     % ճ��Ħ��    
        'G', 1, ...
    'Tc', [+2 -1]);          % (+) (-) ����Ħ��);                            
bot = SerialLink(L, ...     
    'name', 'three link');
q=[10*(pi/180) 20*(pi/180) 30*(pi/180)];
qd=[1 2 3];
qdd=[0.5 1 1.5];
grav=[0;0;9.81];
%j0=bot.jacob0(q)
tol =bot.rne(q,qd,qdd,grav);