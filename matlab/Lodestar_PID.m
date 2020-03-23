delta_t=.01;
t_total=3;
t=[0:delta_t:t_total]';

%PID Gains
Kp_roll=1.3;
Ki_roll=0;
Kd_roll=4.2;

Kp_pitch=2.8;
Ki_pitch=0;
Kd_pitch=7;

Kp_yaw=0;
Ki_yaw=0;
Kd_yaw=0;

%Debugging of Physics Engine
M_pitch_f1=zeros(t_total/delta_t+1,1);
M_pitch_f2=zeros(t_total/delta_t+1,1);
M_pitch_f3=zeros(t_total/delta_t+1,1);
M_pitch_f4=zeros(t_total/delta_t+1,1);
M_roll_f1=zeros(t_total/delta_t+1,1);
M_roll_f2=zeros(t_total/delta_t+1,1);
M_roll_f3=zeros(t_total/delta_t+1,1);
M_roll_f4=zeros(t_total/delta_t+1,1);
drag_f1=zeros(t_total/delta_t+1,1);
drag_f2=zeros(t_total/delta_t+1,1);
drag_f3=zeros(t_total/delta_t+1,1);
drag_f4=zeros(t_total/delta_t+1,1);
f1_eff_area=zeros(t_total/delta_t+1,1);
f2_eff_area=zeros(t_total/delta_t+1,1);
f3_eff_area=zeros(t_total/delta_t+1,1);
f4_eff_area=zeros(t_total/delta_t+1,1);


%Initialization of Arrays
roll_theta=zeros(t_total/delta_t+1,1);
roll_omega=zeros(t_total/delta_t+1,1);
roll_alpha=zeros(t_total/delta_t+1,1);
roll_alpha_com=zeros(t_total/delta_t+1,1);
roll_error=zeros(t_total/delta_t+1,1);
roll_p_correction=zeros(t_total/delta_t+1,1);
roll_integral=zeros(t_total/delta_t+1,1);
roll_i_correction=zeros(t_total/delta_t+1,1);
roll_derivative=zeros(t_total/delta_t+1,1);
roll_d_correction=zeros(t_total/delta_t+1,1);

pitch_theta=zeros(t_total/delta_t+1,1);
pitch_omega=zeros(t_total/delta_t+1,1);
pitch_alpha=zeros(t_total/delta_t+1,1);
pitch_alpha_com=zeros(t_total/delta_t+1,1);
pitch_error=zeros(t_total/delta_t+1,1);
pitch_p_correction=zeros(t_total/delta_t+1,1);
pitch_integral=zeros(t_total/delta_t+1,1);
pitch_i_correction=zeros(t_total/delta_t+1,1);
pitch_derivative=zeros(t_total/delta_t+1,1);
pitch_d_correction=zeros(t_total/delta_t+1,1);

yaw_theta=zeros(t_total/delta_t+1,1);
yaw_omega=zeros(t_total/delta_t+1,1);
yaw_alpha=zeros(t_total/delta_t+1,1);
yaw_error=zeros(t_total/delta_t+1,1);
yaw_p_correction=zeros(t_total/delta_t+1,1);
yaw_integral=zeros(t_total/delta_t+1,1);
yaw_i_correction=zeros(t_total/delta_t+1,1);
yaw_derivative=zeros(t_total/delta_t+1,1);
yaw_d_correction=zeros(t_total/delta_t+1,1);

f1=zeros(t_total/delta_t+1,1);
f2=zeros(t_total/delta_t+1,1);
f3=zeros(t_total/delta_t+1,1);
f4=zeros(t_total/delta_t+1,1);

%Initial Conditions
roll_theta(1)=0;
roll_omega(1)=0;
roll_alpha(1)=0;

pitch_theta(1)=0;
pitch_omega(1)=0;
pitch_alpha(1)=0;

yaw_theta(1)=0;
yaw_omega(1)=0;
yaw_alpha(1)=0;



%Calculation
for i = 2:length(roll_theta)
    %Calculation of Roll
    roll_error(i)=-roll_theta(i-1);
    roll_p_correction(i)= Kp_roll*roll_error(i);
    roll_integral(i)=roll_integral(i-1)+roll_error(i)*delta_t;
    roll_i_correction(i)=Ki_roll*roll_integral(i);
    roll_derivative(i)=(roll_error(i)-roll_error(i-1))/delta_t;
    roll_d_correction(i)=Kd_roll*roll_derivative(i);
    roll_alpha_com(i)=roll_i_correction(i)+roll_p_correction(i)+roll_d_correction(i);
    
    %Calculation of Pitch
    pitch_error(i)=-pitch_theta(i-1);
    pitch_p_correction(i)= Kp_pitch*pitch_error(i);
    pitch_integral(i)=pitch_integral(i-1)+pitch_error(i)*delta_t;
    pitch_i_correction(i)=Ki_pitch*pitch_integral(i);
    pitch_derivative(i)=(pitch_error(i)-pitch_error(i-1))/delta_t;
    pitch_d_correction(i)=Kd_pitch*pitch_derivative(i);
    pitch_alpha_com(i)=pitch_i_correction(i)+pitch_p_correction(i)+pitch_d_correction(i);
    
    %Calculation of Yaw
    yaw_error(i)=-yaw_theta(i-1);
    yaw_p_correction(i)= Kp_yaw*yaw_error(i);
    yaw_integral(i)=yaw_integral(i-1)+yaw_error(i)*delta_t;
    yaw_i_correction(i)=Ki_yaw*yaw_integral(i);
    yaw_derivative(i)=(yaw_error(i)-yaw_error(i-1))/delta_t;
    yaw_d_correction(i)=Kd_yaw*yaw_derivative(i);
    yaw_alpha(i)=yaw_i_correction(i)+yaw_p_correction(i)+yaw_d_correction(i);
    
    %Fin Angles
    [f1(i),f2(i),f3(i),f4(i)]=FinAngles(roll_alpha_com(i),pitch_alpha_com(i),yaw_alpha(i));
    
    %Physics
    [roll_alpha(i),pitch_alpha(i),yaw_alpha(i),M_roll_f1(i),M_roll_f2(i),M_roll_f3(i),M_roll_f4(i),M_pitch_f1(i),M_pitch_f2(i),M_pitch_f3(i),M_pitch_f4(i),drag_f1(i),drag_f2(i),drag_f3(i),drag_f4(i),f1_eff_area(i),f2_eff_area(i),f3_eff_area(i),f4_eff_area(i)]=PhysicsEngine(f1(i),f2(i),f3(i),f4(i),roll_theta(i-1),pitch_theta(i-1),yaw_theta(i-1),t(i));
    roll_omega(i)=roll_omega(i-1)+roll_alpha(i-1)*delta_t;
    pitch_omega(i)=pitch_omega(i-1)+pitch_alpha(i-1)*delta_t;
    yaw_omega(i)=yaw_omega(i-1)+yaw_alpha(i-1)*delta_t;
    roll_theta(i)=roll_theta(i-1)+roll_omega(i-1)*delta_t;
    pitch_theta(i)=pitch_theta(i-1)+pitch_omega(i-1)*delta_t;
    yaw_theta(i)=yaw_theta(i-1)+yaw_omega(i-1)*delta_t;
    
    %Stops Simulation if roll angle exceeds 90 degrees
    if abs(pitch_theta(i))>90 | abs(roll_theta(i))>90
        break;
    end
end

%Plotting
hold off
plot (t,pitch_theta)
hold on
plot (t,roll_theta)

xlabel('Time (sec)')
ylabel('Angle (degrees)')