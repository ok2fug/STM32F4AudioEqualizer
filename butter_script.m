%Variables
Fs = 80000;
Order = 2;
F7 = 16000;
F0 = 31;
Bands = 8;

syms z;
a = vpasolve(F7/F0 == z^(Bands-1),z);
%x contiene la relacion entre cada banda
x=double(abs(a(1,1)));
%n contiene la relacion entre bandas
a = vpasolve(F7/F0 == z^(2*(Bands-1)),z);
n=double(abs(a(1,1)));
Q = n/(n*n-1);

%Section 0
[z,p,k] = butter(Order,[(F0*x^0)/n F0*n*x^0]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_0 = coeffs;
[h,w] = freqz(sos,10000);
h0 = abs (h);


%Section 1
[z,p,k] = butter(Order,[(F0*x^1)/n F0*n*x^1]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_1 = coeffs;
[h,w] = freqz(sos,10000);
h1 = abs (h);

%Section 2
[z,p,k] = butter(Order,[(F0*x^2)/n F0*n*x^2]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_2 = coeffs;
[h,w] = freqz(sos,10000);
h2 = abs (h);

%Section 3
[z,p,k] = butter(Order,[(F0*x^3)/n F0*n*x^3]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_3 = coeffs;
[h,w] = freqz(sos,10000);
h3 = abs (h);

%Section 4
[z,p,k] = butter(Order,[(F0*x^4)/n F0*n*x^4]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_4 = coeffs;
[h,w] = freqz(sos,10000);
h4 = abs (h);

%Section 5
[z,p,k] = butter(Order,[(F0*x^5)/n F0*n*x^5]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_5 = coeffs;
[h,w] = freqz(sos,10000);
h5 = abs (h);

%Section 6
[z,p,k] = butter(Order,[(F0*x^6)/n F0*n*x^6]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_6 = coeffs;
[h,w] = freqz(sos,10000);
h6 = abs (h);

%Section 7
[z,p,k] = butter(Order,[(F0*x^7)/n F0*n*x^7]*2/Fs);
% turn into biquads
sos = zp2sos(z,p,k,'up','two');
% eliminate a0
coeffs = sos(:,[1 2 3 5 6]);
% make a linear array
coeffs = [coeffs(1,:) coeffs(2,:)];
coeffs(4) = - coeffs(4);
coeffs(5) = - coeffs(5);
coeffs(9) = - coeffs(9);
coeffs(10) = - coeffs(10);
coeffs_7 = coeffs;
[h,w] = freqz(sos,10000);
h7 = abs (h);


for i = 1:10000
    h(i) = h0(i) + h1(i) + h2(i) + h3(i) + h4(i) + h5(i) + 0.9*h6(i) + 1.3*h7(i);
end
plot(24000*w/pi,20*log10(abs(h)));
hold on 
plot(24000*w/pi,20*log10(abs(h0)));
hold on 
plot(24000*w/pi,20*log10(abs(h1)));
hold on 
plot(24000*w/pi,20*log10(abs(h2)));
hold on 
plot(24000*w/pi,20*log10(abs(h3)));
hold on 
plot(24000*w/pi,20*log10(abs(h4)));
hold on 
plot(24000*w/pi,20*log10(abs(h5)));
hold on 
plot(24000*w/pi,20*log10(abs(h6)));
hold on 
plot(24000*w/pi,20*log10(abs(h7)));
ax = gca;
ax.YLim = [-60 20];
ax.XTick = 0:2000:24000;
xlabel('Frequency [Hz]')
ylabel('Magnitude (dB)')

fileID = fopen('coefficients.txt','w');
fprintf(fileID, '//8 Bands constant Q = %f equalizer coefficients\n',Q);
fprintf(fileID, '//X = %f, n=%f\n\n',x,n);
fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F1 = %fHz\n',F0);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_1;\n');
fprintf(fileID,'static float32_t firStateF32_1[8];\n');
fprintf(fileID,'static float32_t firCoeffs_1[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_0(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_0(10));

fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F2 = %fHz\n',F0*x^1);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_2;\n');
fprintf(fileID,'static float32_t firStateF32_2[8];\n');
fprintf(fileID,'static float32_t firCoeffs_2[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_1(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_1(10));

fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F3 = %fHz\n',F0*x^2);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_3;\n');
fprintf(fileID,'static float32_t firStateF32_3[8];\n');
fprintf(fileID,'static float32_t firCoeffs_3[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_2(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_2(10));


fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F4 = %fHz\n',F0*x^3);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_4;\n');
fprintf(fileID,'static float32_t firStateF32_4[8];\n');
fprintf(fileID,'static float32_t firCoeffs_4[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_3(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_3(10));


fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F5 = %fHz\n',F0*x^4);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_5;\n');
fprintf(fileID,'static float32_t firStateF32_5[8];\n');
fprintf(fileID,'static float32_t firCoeffs_5[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_4(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_4(10));


fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F6 = %fHz\n',F0*x^5);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_6;\n');
fprintf(fileID,'static float32_t firStateF32_6[8];\n');
fprintf(fileID,'static float32_t firCoeffs_6[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_5(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_5(10));


fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F7 = %fHz\n',F0*x^6);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_7;\n');
fprintf(fileID,'static float32_t firStateF32_7[8];\n');
fprintf(fileID,'static float32_t firCoeffs_7[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_6(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_6(10));


fprintf(fileID,'//------------------------------------------//\n\n');
fprintf(fileID, '//F8 = %fHz\n',F0*x^7);
fprintf(fileID,'arm_biquad_casd_df1_inst_f32  S_8;\n');
fprintf(fileID,'static float32_t firStateF32_8[8];\n');
fprintf(fileID,'static float32_t firCoeffs_8[10] = { ');
for n = 1:9
    fprintf(fileID,'%.20f, ',coeffs_7(n));
end
fprintf(fileID,'%.20f };\n\n',coeffs_7(10));
fprintf(fileID,'//------------------------------------------//\n\n');

fclose(fileID);