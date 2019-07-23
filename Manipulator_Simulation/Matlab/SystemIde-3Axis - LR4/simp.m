syms q0 q1 q2 dq0 dq1 dq2 ddq0 ddq1 ddq2 g a1 a2 a3
x0 = cos(q1);x1 = sin(q1);x2 = -x1;x3 = dq0*x2;x4 = dq1*x3;
x5 = ddq0*x0 + x4;x6 = dq0*x0;x7 = dq1*x6;x8 = -x7;x9 = x1*x8;
x10 = -ddq0*x1 + x8;x11 = x4 + x5;x12 = x3*x6;x13 = ddq1 + x12;x14 = ((dq1)*(dq1));
x15 = ((x6)*(x6));x16 = -x15;x17 = -x4;x18 = -x10;x19 = -x14;
x20 = ((x3)*(x3));x21 = -x12;x22 = x18 + x7;x23 = a1*ddq0;x24 = -x20;
x25 = -a1*((dq0)*(dq0));x26 = x0*x25 - g*x1;x27 = g*x0 + x1*x25;x28 = cos(q2);x29 = sin(q2);
x30 = -x29;x31 = x28*x3 + x30*x6;x32 = dq2*x31 + x10*x29 + x28*x5;x33 = x28*x6 + x29*x3;x34 = dq1 + dq2;
x35 = x33*x34;x36 = -x35;x37 = -dq2*x33 + x10*x28 - x29*x5;x38 = x36 + x37;x39 = x31*x34;
x40 = x32 + x39;x41 = ddq1 + ddq2;x42 = x31*x33;x43 = x41 + x42;x44 = x28*x43;
x45 = ((x34)*(x34));x46 = ((x33)*(x33));x47 = -x46;x48 = x45 + x47;x49 = -x39;
x50 = ((x31)*(x31));x51 = -x45;x52 = x50 + x51;x53 = -x42;x54 = x41 + x53;
x55 = x35 - x37;x56 = a2*x22 + x23;x57 = -x56;x58 = -a2;x59 = -x50;
x60 = x47 + x59;x61 = a2*x13 + x26;x62 = a2*(x19 + x24) + x27;x63 = x28*x61 + x30*x62;x64 = -x63;
x65 = x28*x62 + x29*x61;x66 = x46 + x59;x67 = x32 + x49;x68 = x35 + x37;x69 = -x65;

  Mregress5 = ddq0;
  Mregress10 = x0*x5 + x9;
  Mregress11 = x2*x11 + x0*(x10 + x8);
  Mregress12 = x2*(x14 + x16) + x13*x0;
  Mregress13 = x1*x18 + x17*x0;
  Mregress14 = x2*(ddq1 + x21) + x0*(x20 + x19);
  Mregress15 = x0*x4 - x9;
  Mregress16 = a1*x22 - x2*x23;
  Mregress17 = a1*x11 + x0*x23;
  Mregress18 = a1*(x16 + x24) - x0*x26 + x2*x27;
  Mregress19 = a1*x23;
  Mregress20 = x0*(x28*x32 + x30*x35) + x2*(x28*x35 + x29*x32);
  Mregress21 = x0*(x28*x38 + x30*x40) + x2*(x28*x40 + x29*x38);
  Mregress22 = x0*(x30*x48 + x44) + x2*(x28*x48 + x29*x43);
  Mregress23 = x0*(x28*x49 + x30*x37) + x2*(x28*x37 + x29*x49);
  Mregress24 = x0*(x28*x52 + x30*x54) + x2*(x28*x54 + x29*x52);
  Mregress25 = x0*(x28*x39 + x30*x36) + x2*(x28*x36 + x29*x39);
  Mregress26 = a1*x55 + x0*x30*x57 + x2*(x28*x57 + x55*x58);
  Mregress27 = a1*x40 + x0*x28*x56 + x2*(x29*x56 + x40*x58);
  Mregress28 = a1*x60 + x0*(x28*x64 + x30*x65) + x2*(x28*x65 + x29*x64 + x58*x60);
  Mregress29 = a1*x56 + a2*x2*x57;

  
  Mregress40 = x21;
  Mregress41 = x15 + x24;
  Mregress42 = x17 + x5;
  Mregress43 = x12;
  Mregress44 = x10 + x7;
  Mregress45 = ddq1;
  Mregress46 = x26;
  Mregress47 = -x27;
  Mregress50 = x53;
  Mregress51 = x66;
  Mregress52 = x67;
  Mregress53 = x42;
  Mregress54 = x68;
  Mregress55 = x41;
  Mregress56 = a2*(x29*(x51 + x59) + x44) + x63;
  Mregress57 = a2*(x28*(x47 + x51) + x29*(-x41 + x42)) + x69;
  Mregress58 = a2*(x28*(-x32 + x39) + x29*x68);
  Mregress59 = a2*(x28*x63 + x29*x65);

  
  Mregress80 = x53;
  Mregress81 = x66;
  Mregress82 = x67;
  Mregress83 = x42;
  Mregress84 = x68;
  Mregress85 = x41;
  Mregress86 = x63;
  Mregress87 = x69;

A1=simplify(Mregress10) 
A2=simplify(Mregress11)
A3=simplify(Mregress12)
A4=simplify(Mregress13)
A5=simplify(Mregress14)
A6=simplify(Mregress15)
A7=simplify(Mregress16)
A8=simplify(Mregress17)
A9=simplify(Mregress18)
A10=simplify(Mregress19)
A11=simplify(Mregress20)
A12=simplify(Mregress21)
A13=simplify(Mregress22)
A14=simplify(Mregress23)
A15=simplify(Mregress24)
A16=simplify(Mregress25)
A17=simplify(Mregress26)
A18=simplify(Mregress27)
A19=simplify(Mregress28)
A20=simplify(Mregress29)

B1=simplify(Mregress40)
B2=simplify(Mregress41)
B3=simplify(Mregress42)
B4=simplify(Mregress43)
B5=simplify(Mregress44)
B6=simplify(Mregress45)
B7=simplify(Mregress46)
B8=simplify(Mregress47)
B9=simplify(Mregress50)
B10=simplify(Mregress51)
B11=simplify(Mregress52)
B12=simplify(Mregress53)
B13=simplify(Mregress54)
B14=simplify(Mregress55)
B15=simplify(Mregress56)
B16=simplify(Mregress57)
B17=simplify(Mregress58)
B18=simplify(Mregress59)

C1=simplify(Mregress80)
C2=simplify(Mregress81)
C3=simplify(Mregress82)
C4=simplify(Mregress83)
C5=simplify(Mregress84)
C6=simplify(Mregress85)
C7=simplify(Mregress86)
C8=simplify(Mregress87)