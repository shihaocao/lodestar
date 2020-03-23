
function [f1,f2,f3,f4]=FinAngles(roll_alpha,pitch_alpha,yaw_alpha)
    %Sets maximum accelerations used for normalization
    roll_max=200;
    pitch_max=200;
    yaw_max=100;
    
    %Fin/Canard angles for neutral stability (fin angle needed for CP=CG)
    fin_eq=0;
    canard_eq=41.418;
    
    
    %Creates Normalized Accelerations
    roll_norm=abs(roll_alpha/roll_max);
    pitch_norm=abs(pitch_alpha/pitch_max);
    yaw_norm=abs(yaw_alpha/yaw_max);
    
    %Ensures that no normalized accleration is over 1
    if roll_norm>1
        roll_norm=1;
    end
        
    if pitch_norm>1
        pitch_norm=1;
    end
    
    if yaw_norm>1
        yaw_norm=1;
    end
    
    %Determines Fin Command matrices depending on sign of commnanded
    %acceleration
    if roll_alpha>0
        M_roll=[0;0.535;0;0.535];
    else
        M_roll=[0.535;0;0.535;0];
    end
    
    if pitch_alpha>0
        M_pitch=[0;0;1;1];
    else
        M_pitch=[1;1;0;0];
    end
    
    if yaw_alpha>0
        M_yaw=[1;0;0;1];
    else
        M_yaw=[0;1;1;0];
    end
    
    %Calculates normalized fin angles
    F=(M_roll*roll_norm+M_pitch*pitch_norm+M_yaw*yaw_norm);
    
    %Ensures that no normalized fin angle is over 1
    if max(F)>1
        F=F/max(F);
    end
    
    %Converts normalized fin angles to real fin angles
    F=90*F;
    
    %Accounts for corrections to make a neutrally stable craft 
    if F(1)+canard_eq>90
        F(1)=90;
    else
        F(1)=F(1)+canard_eq;
    end
    
    if F(2)+canard_eq>90
        F(2)=90;
    else
        F(2)=F(2)+canard_eq;
    end
    
    if F(3)+fin_eq>90
        F(3)=90;
    else
        
        F(3)=F(3)+fin_eq;
    end
    
    if F(4)+fin_eq>90
        F(4)=90;
    else
        F(4)=F(4)+fin_eq;
    end
    
    f1=F(1);
    f2=F(2);
    f3=F(3);
    f4=F(4);  
end

