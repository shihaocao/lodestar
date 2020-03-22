s = tf('s');
P = 1/(s^2 + 10*s + 20);

Kp = 30;
C = pid(Kp)
T = feedback(C*P,1)

t = 0:0.01:2;
step(T,t)