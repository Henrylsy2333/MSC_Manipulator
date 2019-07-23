syms a1 a2
syms q1 q2 q3
L1 = Link('d', 0, 'a', 0,  'alpha', 0);        
L2 = Link('d', 0, 'a', a1, 'alpha', pi/2);        
L3 = Link('d', 0, 'a', a2, 'alpha', 0);            
bot = SerialLink([L1 L2 L3],'name','50kg','offset',[0 pi/2 0]);             
J = bot.jacob0([q1 q2 q3])  

