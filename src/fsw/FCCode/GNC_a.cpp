#include "GNC_a.hpp"
#include <gnc/utilities.hpp>

GNC_a::GNC_a(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc_a", offset),
    fin_commands_f("gnc_a.fin_cmds"),
    glob_acc_vec_f("imu.glob_acc_vec"),
    thrust_commands_f("gnc_a.thrust_cmds"),
    setpoint_d("gnc_a.setpoint"),
    velocity_d("gnc_a.velocity"),
    position_d("gnc_a.position"),
    net_quat_d("gnc_a.net_quat"),
    glob_pos_err_d("gnc_a.glob_pos_err"),
    body_pos_err_d("gnc_a.body_pos_err"),
    body_velocity_d("gnc_a.body_velocity"),
    roll_integral_d("gnc_a.roll_integral"),
    pitch_integral_d("gnc_a.pitch_integral"),
    yaw_integral_d("gnc_a.yaw_integral"),
    x_integral_d("gnc_a.x_integral"),
    euler_d("gnc_a.euler"),
    a_com_d("gnc_a.a_com")

    

    {
        add_internal_field(fin_commands_f);
        add_internal_field(glob_acc_vec_f);
        add_internal_field(thrust_commands_f);
        add_internal_field(setpoint_d);
        add_internal_field(velocity_d);
        add_internal_field(position_d);
        add_internal_field(net_quat_d);
        add_internal_field(glob_pos_err_d);
        add_internal_field(body_pos_err_d);
        add_internal_field(body_velocity_d);
        add_internal_field(pitch_integral_d);
        add_internal_field(yaw_integral_d);
        add_internal_field(x_integral_d);
        add_internal_field(euler_d);
        add_internal_field(a_com_d);


        mission_mode_fp = find_internal_field<unsigned char>("ls.mode", __FILE__, __LINE__);
        omega_vec_fp = find_internal_field<lin::Vector3f>("imu.gyr_vec", __FILE__, __LINE__);
        acc_vec_fp = find_internal_field<lin::Vector3f>("imu.acc_vec", __FILE__, __LINE__);
        grav_vec_fp = find_internal_field<lin::Vector3f>("imu.grav_vec", __FILE__, __LINE__);
        lin_acc_vec_fp = find_internal_field<lin::Vector3f>("imu.linear_acc_vec", __FILE__, __LINE__);
        acc_error_fp = find_internal_field<lin::Vector3f>("ls.acc_error", __FILE__, __LINE__);     
        euler_vec_fp = find_internal_field<lin::Vector3f>("imu.euler_vec", __FILE__, __LINE__);
        quat_fp = find_internal_field<lin::Vector4d>("imu.quat", __FILE__, __LINE__);
        mag_vec_fp = find_internal_field<lin::Vector3f>("imu.mag_vec", __FILE__, __LINE__);
        init_quat_dp = find_internal_field<lin::Vector4d>("ls.init_quat", __FILE__, __LINE__);
        altitude_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);
        ground_level_fp = find_internal_field<float>("ls.ground_level", __FILE__, __LINE__);
        lat_long_fp = find_internal_field<lin::Vector2f>("gps.lat_long", __FILE__, __LINE__);
        init_lat_long_fp=find_internal_field<lin::Vector2f>("ls.init_coord", __FILE__, __LINE__);
        fix_qual_fp = find_internal_field<unsigned char>("gps.fix_qual", __FILE__, __LINE__);
        init_global_roll_dp = find_internal_field<double>("ls.glob_roll", __FILE__, __LINE__);

        // default all fins to no actuation
        fin_commands_f.set({
            0.0,
            0.0,
            0.0,
            0.0,
        });

        // default motor to no thrust
        thrust_commands_f.set({
            0.0,
            0.0,
        });
    
        

    }


void GNC_a::execute(){

    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_fp->get());

    switch(mode) {
        case mission_mode_t::starhopper1:
             setpoint_d.set(CONTROLS::setpoint_1);
             tvc();
            break;
        case mission_mode_t::starhopper2:
             setpoint_d.set(CONTROLS::setpoint_2);
             tvc();
            break;
        case mission_mode_t::starhopper3:
             setpoint_d.set(CONTROLS::setpoint_3);
             tvc();
            break;
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            // mission_mode_fp->set(static_cast<unsigned char>(mission_mode_t::landed));
            break;
    }

}

void quat_conj(lin::Vector4d const &q, lin::Vector4d &res) {
  res = {q(0), -q(1), -q(2), -q(3) };
}

void hamilton_product(lin::Vector4d const &q, lin::Vector4d const &r,
    lin::Vector4d &res) {
    res(0)=(r(0)*q(0)-r(1)*q(1)-r(2)*q(2)-r(3)*q(3));
    res(1)=(r(0)*q(1)+r(1)*q(0)-r(2)*q(3)+r(3)*q(2));
    res(2)=(r(0)*q(2)+r(1)*q(3)+r(2)*q(0)-r(3)*q(1));
    res(3)=(r(0)*q(3)-r(1)*q(2)+r(2)*q(1)+r(3)*q(0));
}


void rotate_frame(lin::Vector4d const &q, lin::Vector3d const &v, lin::Vector3d &res){
   lin::Vector4d q_v= {0.0,v(0),v(1),v(2)};
   lin::Vector4d intermediate = {0.0,0.0,0.0,0.0};
   lin::Vector4d q_res = {0.0,0.0,0.0,0.0};
   lin::Vector4d q_conj = {0.0,0.0,0.0,0.0};
   quat_conj(q,q_conj);
   hamilton_product(q,q_v,intermediate);
   hamilton_product(intermediate,q_conj,q_res);
   res(0)=q_res(1);
   res(1)=q_res(2);
   res(2)=q_res(3);
}

//Outputs Euler angles with the convention ZYX (Roll is outermost gimbal). Output is in radians
void quat2euler(lin::Vector4d const &q, lin::Vector3d &res){
    res(0)=atan2( 2* ( q(0) * q(1) + q(2) * q(3) ), 1-2*( pow(q(1),2) + pow(q(2),2) ));
    res(1)=asin(2* ( q(0) * q(2) - q(3) * q(1) ));
    res(2)=atan2( 2* ( q(0) * q(3) + q(1) * q(2) ), 1-2*( pow(q(2),2) + pow(q(3),2) ));

}

void distance(lin::Vector2d const &coord1, lin::Vector2d const &coord2, double &res){
    double R = 6371e3;
    double p1 = coord1(0)*PI/180;
    double p2 = coord2(0)*PI/180;
    double dp = p2-p1;
    double dl = (coord2(1)-coord1(1))*PI/180;
    double a = sin(dp/2)*sin(dp/2) + cos(p1)*cos(p2)*sin(dl/2)*sin(dl/2);
    double c = 2*atan2(sqrt(a),sqrt(1-a));
    res = R*c;
}

//Coord1 is reference position. 
void distance1(lin::Vector2d const &coord1, lin::Vector2d const &coord2, lin::Vector2d &res){
    res(0)=(coord2(1)-coord1(1))*40075000 * cos( coord1(0) * PI/180 ) / 360.0;
    res(1)=(coord2(0)-coord1(0))*111320;
}

lin::Matrix2x2d inv(lin::Matrix2x2d &A) {
    double a = A(0);
    double b = A(1);
    double c = A(2);
    double d = A(3);

    double det=a*d-b*c;
    lin::Matrix2x2d res = {d/det, -b/det, -c/det, a/det};
    return res;
}

//x_kmo is the previous state vector, P_kmo is the previous covariance matrix, a is the acceleration, z is the GPS state vector
void kalman(lin::Vector2d const &x_kmo, lin::Matrix2x2d const &P_kmo, double const &a, lin::Vector2d const &z, lin::Vector2d &x_kf, lin::Matrix2x2d &P_kf){
    //F is state transition matrix, B is control matrix, Q is IMU noise, R is GPS noise
    //P_k is predicted covariance matrix, x_k is dead reckoned position, 
    //P_kf is returned covariance matrix, x_kf is final position, K is Kalman Gain

    double dt = PAN::control_cycle_time_ms/1000.0;


    lin::Matrix2x2d F = {1.0, dt, 0.0, 1.0}; //Generates Transition Matrix
    lin::Vector2d B = {0.5*dt*dt, dt};      //Generates Control Matrix

    lin::Matrix2x2d Q = {1.0,0.0,1.0,0.0};  //Initializes IMU noise
    lin::Matrix2x2d R = {1.0,0.0,1.0,0.0};  //Initializes GPS noise

    //Prediction Step
    lin::Vector2d x_k = F*x_kmo+B*a;
    lin::Matrix2x2d P_k = F*P_kmo* lin::transpose(F)+Q;

    //Update Step
    lin::Matrix2x2d helper = P_k+R;
    lin::Matrix2x2d K = P_k*inv(helper);

    x_kf = x_k+K*(z-x_k);
    P_kf = P_k-K*P_k;
    
}

//Input is the desired thrust, output is the commands given to the two motors to get roll control
lin::Vector2f thrust(double const force, double const diff){
    lin::Vector2f out = {0.0,0.0};

    //Converts the desired thrust into a total actuatior value
    double a = (force+267.9944)/16.1234;

    //Distributes the Actuation value to each actuator depending on the differential
    out(0)=(a+diff)/2.0;
    out(1)=(a-diff)/2.0;

    //Limits actuator values from 0-180
    if (out(0)<0){
        out(0)=0;
    }if (out(1)<0){
        out(1)=0;
    }if (out(0)>180){
        out(0)=180;
    }if (out(1)>180){
        out(1)=180;
    }

    return out;
}


void GNC_a::tvc(){
    //-----------------------------Obtaining Useful Information for Controls-------------------------------
    //Converting Statefields into tangible vectors
    lin::Vector4f fin_commands = fin_commands_f.get();
    lin::Vector2f thrust_commands = thrust_commands_f.get();
    lin::Vector3d position = position_d.get();
    lin::Vector3d velocity = velocity_d.get();
    lin::Vector3d lin_acc_vec_d = lin_acc_vec_fp->get();
    lin::Vector3d glob_acc = glob_acc_vec_f.get();
    lin::Vector3d setpoint = setpoint_d.get();
    lin::Vector4d quat = quat_fp->get();
    //double altitude = altitude_fp->get()-ground_level_fp->get();

    lin::Vector4d init_quat_conj;
    lin::Vector4d quat_inv;
    lin::Vector4d net_quat_conj;
    lin::Vector4d net_quat;
    lin::Vector3d euler;

    lin::Vector4d init_quat = init_quat_dp->get();
    quat_conj(quat,quat_inv);
    quat_conj(init_quat,init_quat_conj);


    //Creates the quaternion to rotate about to go from body frame to equilibrium global frame.
    //net_quat is the quaternion of orientation with respect to the equilibrium frame (vertical rocket)
    hamilton_product(init_quat_conj,quat,net_quat);

    //Creates quaternion to rotate about to go from equilibrium global frame to body frame
    quat_conj(net_quat,net_quat_conj);
    quat2euler(net_quat,euler);

    //Saves net_quat to statefield
    net_quat_d.set({
        net_quat(0),
        net_quat(1),
        net_quat(2),
        net_quat(3),
    });

    //Calculates Position via GPS

    //Converts current GPS position into double (higher precision during calcuation)
    double lat = lat_long_fp->get()(0);
    double lon = lat_long_fp->get()(1);
    lin::Vector2d lat_long = {lat, lon};

    //Converts initial GPS position into double
    double init_lat = init_lat_long_fp->get()(0);
    double init_lon = init_lat_long_fp->get()(1);
    lin::Vector2d init_lat_long = {init_lat, init_lon};

    //Generates Global Position Vector (pos_east,pos_north)
    lin::Vector2d global_pos;
    distance1(init_lat_long, lat_long, global_pos);

    //Converts acceleration in body frame to acceleration in global frame (accounts for the boot quat not being (1,0,0,0))
    rotate_frame(net_quat, lin_acc_vec_d, glob_acc);

    //Sets the value of global acceleration while accounting for any bias in the IMU acceleration readings
    glob_acc_vec_f.set({
        glob_acc(0)-acc_error_fp->get()(0),
        glob_acc(1)-acc_error_fp->get()(1),
        glob_acc(2)-acc_error_fp->get()(2),
    });

   //Generates GPS Acceleration (acc_east,acc_north)
    double th = init_global_roll_dp->get();
    lin::Vector2d GPS_acc;
    GPS_acc = {
        cos(th)*glob_acc(1)+sin(th)*glob_acc(2),
        -sin(th)*glob_acc(1)+sin(th)*glob_acc(2)
    };

    Serial.print("(");
    Serial.print(glob_acc(1));
    Serial.print(",");
    Serial.print(glob_acc(2));
    Serial.print(")     ");

    Serial.print("(");
    Serial.print(GPS_acc(0));
    Serial.print(",");
    Serial.print(GPS_acc(1));
    Serial.println(")");



    //Calculates Position via numerical integration
    position_d.set({
        //altitude,
        position(0)+velocity(0)*PAN::control_cycle_time_ms/1000+0.5*glob_acc(0)*PAN::control_cycle_time_ms/1000*PAN::control_cycle_time_ms/1000,
        position(1)+velocity(1)*PAN::control_cycle_time_ms/1000+0.5*glob_acc(1)*PAN::control_cycle_time_ms/1000*PAN::control_cycle_time_ms/1000,
        position(2)+velocity(2)*PAN::control_cycle_time_ms/1000+0.5*glob_acc(2)*PAN::control_cycle_time_ms/1000*PAN::control_cycle_time_ms/1000,
    });
    

    //Calculates Velocity via numerical integration (Will eventually be calculated by differentiating GPS readings)
    velocity_d.set({
        velocity(0)+glob_acc(0)*PAN::control_cycle_time_ms/1000,
        velocity(1)+glob_acc(1)*PAN::control_cycle_time_ms/1000,
        velocity(2)+glob_acc(2)*PAN::control_cycle_time_ms/1000,
        });

    //Sets global position error
    glob_pos_err_d.set({
        setpoint(0)-position_d.get()(0),
        setpoint(1)-position_d.get()(1),
        setpoint(2)-position_d.get()(2),
    });

    lin::Vector3d glob_pos_err = glob_pos_err_d.get();

    //Rotates y and z components of velocity by the roll angle to get velocity in "body frame"
    //Sets body velocity vector
    body_velocity_d.set({
        velocity(1)*cos(euler(0))+velocity(2)*sin(euler(0)),
        -velocity(1)*sin(euler(0))+velocity(2)*cos(euler(0))
    });

    //Rotates y and z components of global position error by the roll angle to get the desired heading
    //Sets the value of the body position error vector
    body_pos_err_d.set({
        glob_pos_err(1)*cos(euler(0))+glob_pos_err(2)*sin(euler(0)),
        -glob_pos_err(1)*sin(euler(0))+glob_pos_err(2)*cos(euler(0))
    });

    //Creates a normalized body error vector. It has two entries. Error along all but the vertical axis.
    //Additionally, it ensures that no component has value greater than 1

    lin::Vector2d body_pos_err_norm;
    if (max(body_pos_err_d.get()(0),body_pos_err_d.get()(1))<CONTROLS::max_position_error){
        lin::Vector2d body_pos_err_norm {
            body_pos_err_d.get()(0)/CONTROLS::max_position_error,
            body_pos_err_d.get()(1)/CONTROLS::max_position_error
            }; 
    }else{
        lin::Vector2d body_pos_err_norm {
            body_pos_err_d.get()(0)/max(body_pos_err_d.get()(0),body_pos_err_d.get()(1)),
            body_pos_err_d.get()(1)/max(body_pos_err_d.get()(0),body_pos_err_d.get()(1))
            }; 
    }



    //-----------------------------Attitude Controller-------------------------------

     //The variables roll, pitch and yaw are in degrees
    double roll = euler(0)*180.0/PI;
    double pitch = euler(1)*180.0/PI;
    double yaw = euler(2)*180.0/PI;
    double delta_t = (PAN::control_cycle_time_ms/1000.0);

    //Stores Euler Angles to Statefield. These angles describe the orientation wrt equilibrium (vertical)
    euler_d.set({
        roll,
        pitch,
        yaw,
    });

    //Pitch and Z control

    //Calculate Pitch Integral
    pitch_integral_d.set(
        pitch_integral_d.get()-pitch*delta_t
    );

    double pitch_integral=pitch_integral_d.get();
    double pitch_derivative = omega_vec_fp->get()(1);

    double pitch_error=-CONTROLS::max_tilt*body_pos_err_norm(1)+CONTROLS::Kd_p_tilt*body_velocity_d.get()(1)-pitch;
    double pitch_p_correction = CONTROLS::Kp_pitch*pitch_error;
    double pitch_i_correction = CONTROLS::Ki_pitch*pitch_integral;
    double pitch_d_correction = CONTROLS::Kd_pitch*pitch_derivative;
    double pitch_alph_com = pitch_p_correction+pitch_i_correction+pitch_d_correction;

    //Yaw and Y position control

    //Calculate Yaw Integral
    yaw_integral_d.set({
        yaw_integral_d.get()-yaw*delta_t
    });

    double yaw_integral=yaw_integral_d.get();
    double yaw_derivative = omega_vec_fp->get()(2);

    double yaw_error=-CONTROLS::max_tilt*body_pos_err_norm(0)+CONTROLS::Kd_y_tilt*body_velocity_d.get()(0)-yaw;
    double yaw_p_correction = CONTROLS::Kp_yaw*yaw_error;
    double yaw_i_correction = CONTROLS::Ki_yaw*yaw_integral;
    double yaw_d_correction = CONTROLS::Kd_yaw*yaw_derivative;
    double yaw_alph_com = yaw_p_correction+yaw_i_correction+yaw_d_correction;

    //Roll Control
    roll_integral_d.set({
        roll_integral_d.get()+roll*delta_t
    });

    double roll_integral = roll_integral_d.get();
    double roll_derivative = omega_vec_fp->get()(0);

    double roll_error = -roll;
    double roll_p_correction = CONTROLS::Kp_roll*roll_error;
    double roll_i_correction = CONTROLS::Ki_roll*roll_integral;
    double roll_d_correction = CONTROLS::Kd_roll*roll_derivative;
    double roll_differential = roll_p_correction+roll_i_correction+roll_d_correction;
    

    //X (altitude) control

    double Kp_x;
    double Ki_x;
    double Kd_x;
    
    //Calculates X integral
    x_integral_d.set({
        x_integral_d.get()+(setpoint(0)-position_d.get()(0))*delta_t
    });

    double x_integral=x_integral_d.get();
    double x_derivative = velocity_d.get()(0);

    //Sets appropriate PID gains depending on whether Lodestar is ascending or decending
    if (position_d.get()(0)<setpoint(0)){
        Kp_x=CONTROLS::Kp_xa;
        Ki_x=CONTROLS::Ki_xa;
        Kd_x=CONTROLS::Kd_xa;
    }else{
        Kp_x=CONTROLS::Kp_xd;
        Ki_x=CONTROLS::Ki_xd;
        Kd_x=CONTROLS::Kd_xd;
    }

    double x_error = setpoint(0)-position_d.get()(0);
    double x_p_correction = Kp_x*x_error;
    double x_i_correction = Ki_x*x_integral;
    double x_d_correction = Kd_x*x_derivative;
    double x_a_com=x_p_correction+x_i_correction+x_d_correction;

    //Saves commanded acclerations to statefield
    a_com_d.set({
        x_a_com,
        pitch_alph_com,
        yaw_alph_com
    });


    //-----------------------------Actuation Algorithm-------------------------------

    double T;   //Local variable for commanded thrust force
    lin::Vector2d tvc_angles;

    //Normalizes commanded accelerations by their maximum expected values
    double norm_alph_pitch = pitch_alph_com/CONTROLS::alph_pitch_max;
    double norm_alph_yaw = yaw_alph_com/CONTROLS::alph_yaw_max;
    double norm_a_x = x_a_com/CONTROLS::a_x_max;

    //Calculates desired thrust force to get desired commanded vertical acceleration
    if (norm_a_x>0){
        T=norm_a_x*CONTROLS::T_max;
    }else{
        T=0.0;
    }

    tvc_angles(0)=-norm_alph_pitch*CONTROLS::servo_max;
    tvc_angles(1)=-norm_alph_yaw*CONTROLS::servo_max;
    T=T+fabs(norm_alph_pitch+norm_alph_yaw)*CONTROLS::weight;

    //Prevent servo saturation
    if (max(tvc_angles(0),tvc_angles(1))>CONTROLS::servo_max){
        tvc_angles(0)=tvc_angles(0)/max(tvc_angles(0),tvc_angles(1));
        tvc_angles(1)=tvc_angles(1)/max(tvc_angles(0),tvc_angles(1));
    }

    lin::Vector2d dist;
    distance1(init_lat_long, lat_long, dist);

    /*
    Serial.print("(");
    Serial.print(glob_acc_vec_f.get()(0));
    Serial.print(",");
    Serial.print(glob_acc_vec_f.get()(1));
    Serial.print(",");
    Serial.print(glob_acc_vec_f.get()(2));
    Serial.print(")     ");

    Serial.print("(");
    Serial.print(velocity_d.get()(0));
    Serial.print(",");
    Serial.print(velocity_d.get()(1));
    Serial.print(",");
    Serial.print(velocity_d.get()(2));
    Serial.println(")     ");
    */

    //Prints Distance from reference point
    /*
    Serial.print("(");
    Serial.print(init_lat,8);
    Serial.print(",");
    Serial.print(init_lon,8);
    Serial.print(")    ");

    Serial.print("(");
    Serial.print(lat,8);
    Serial.print(",");
    Serial.print(lon,8);
    Serial.print(")   ");

    Serial.print("(");
    Serial.print(dist(0),8);
    Serial.print(",");
    Serial.print(dist(1),8);
    Serial.println(")   ");
    */


    fin_commands_f.set(fin_commands);
    thrust_commands = thrust(400,roll_differential);
    thrust_commands_f.set(thrust_commands);

    //DebugSERIAL.print("Fix Qual: ");
    //DebugSERIAL.print(fix_qual_fp->get());

    

   
}

