#include "Methods.h"
#include "BNO055-Serial.h"
#include "AS5048A-Magnetic-Encoder.h"
#include "BNO055-Serial.h"
#include "CommonFunctions.h"
// #include "PID.h"


/////////////////////////////////////////////////////////////////////////////
//                              Function Definitions                       //
/////////////////////////////////////////////////////////////////////////////

////Useful but not necessary features////
void GetTeensyTemp(Feedback_t * Feedback)
{

}

////Common Features////
void Current_Clamp(Current_t *Current, uint32_t *PWM_Pin)
{

}

////Control Systems////
void RotundaControlSystem(Feedback_t * Feedback, Commands_t *Command)
{

}
uint16_t GetPWM(uint16_t Val)
{
    return map(Val, 0, 1023, 0, (pow(2,analogWriteResVal()) - 1));
}


double ClipLimits(double Input, double Min, double Max)
{
    if(Input > Max)
    {
        Input = Max;
    }
    else if(Input < Min)
    {
        Input = Min;
    }
    return Input;
}

#define WRIST_ROLL_OFFSET 0 


double PID_Output_Avg = 0;
void ShoulderControlSystem(uint32_t Shoulder, Feedback_t * Feedback)
{
	// 35 5 2
    ////Constants////
    const double PID_Weight = 0.005;     //  Weight for the Exponential Moving Average
    const double Up_Limit   = 1023;     //  Maximum Clip value for the PID Loop
    const double Down_Limit = -300;    	//  Minimum Clip value for the PID Loop
    const double Offset     = 141;        //  Software offset for arm position.
    const double Kp  = 25;              //  Kp -  proportional gain
    const double Kd  = 0;               //  Kd -  Derivative gain
    const double Ki  = 0;               //  Ki -  Integral gain
    const double Dt  = 0.005;           //  Dt -  loop interval time

    ////Variables////
    static double Feedback_Avg = 0;
    static double Pre_Error;    //  Stores previous error to use with the integral.
    static double Integral;     //  Stores up the error over time.
    bool Locked = false;

    ////Feedback Variables////
    uint16_t Encoder_Data_Shoulder;
    uint16_t Encoder_Data_Wrist;
    double Encoder_Ang_adj;

    ////DO NOT REMOVE EVER !!!THIS IS A PATCH FOR WEIRD INCOMMING COMMANDS
    static uint32_t Input_Command = 270;
    if((Shoulder < 281) && (Shoulder > 139))
    {
        Input_Command = Shoulder;
    }

    ////Wrist Feedback////
    // if(Encoder_Get_Data(&Encoder_Data_Wrist, WRIST_ENCODER_CS))
    // {
    //     double Roll_F_Mapped = map(Encoder_Data_Wrist, 0, 16383, 0, 360);
    //     uint32_t Roll_F_Adjusted = SoftwareaAdjust(Roll_F_Mapped, 0, 360, WRIST_ROLL_OFFSET);
    //     Feedback->Wrist_Roll = Roll_F_Adjusted;
    // }
    // else
    // {
    //     Serial.println("Encoder Error, Locked Wrist!");
    //     analogWrite(WRIST_PWM_1_LEFT,  0);
    //     analogWrite(WRIST_PWM_2_LEFT,  0);
    //     analogWrite(WRIST_PWM_1_RIGHT, 0);
    //     analogWrite(WRIST_PWM_2_RIGHT, 0);
    //     analogWrite(SHOULDER_PWM, 0);
    // }  

    ////Shoulder Feedback////
   
    if(Encoder_Get_Data(&Encoder_Data_Shoulder, SHOULDER_ENCODER_CS))
    {
        double Encoder_Ang = map(Encoder_Data_Shoulder, 0, 16383, 0, 360);
        Encoder_Ang_adj = SoftwareaAdjust(Encoder_Ang, 0, 360, Offset);
       // Serial.print(" Raw: "); Serial.println(Encoder_Ang_adj);
        (Feedback -> Shoulder) = (uint32_t)Encoder_Ang_adj;
        Locked = false;
    }
    else
    {
        Locked = true;
        analogWrite(SHOULDER_PWM, 0);
        analogWrite(WRIST_PWM_1_LEFT,  0);
        analogWrite(WRIST_PWM_2_LEFT,  0);
        analogWrite(WRIST_PWM_1_RIGHT, 0);
        analogWrite(WRIST_PWM_2_RIGHT, 0);
        Serial.println("Encoder Error, Locked Shoulder!");
    }

    ////Control System////
    if(!Locked)
    {
        ////PID Calculations////
        // Calculate Error
        double Error = (double)Input_Command - Encoder_Ang_adj;

        // Proportional term
        double Pout = Kp * Error;

        // Integral term
        //Integral += Error * Dt;
       // double Iout = Ki * Integral;

        // Derivative term
        //double Derivative = (Error - Pre_Error) / Dt;
        //double Dout = Kd * Derivative;

        // Calculate total Output
        double PID_Output = Pout; //+ Iout + Dout;

        // Save Error to previous Error
       // Pre_Error = Error;
        
        //Exponential Moving Average to smooth PID Output
        //static double PID_Output_Avg = 0;
        static bool Dir_Prev = 0;
        bool DirOut = 0;

        PID_Output_Avg = (PID_Output * PID_Weight) + (PID_Output_Avg * (1 - PID_Weight));
        
        // static uint32_t Command_Old = 0;
        // if(Command -> Shoulder != Command_Old)
        // {
        //     Integral = 0;
        //     Command_Old = Command -> Shoulder;
        // }


        // Check for slowing down
        if(PID_Output < PID_Output_Avg) 
        {
        	PID_Output_Avg = PID_Output; 
        }
        // if(Error < 2)
        // {
        //     PID_Output_Avg = 0;
        // }
        // // Check for swapped direction
        // DirOut = (PID_Output_Avg > 0) ? 0 : 1;
        // if(DirOut != Dir_Prev)
        // {
        // 	PID_Output_Avg = PID_Output;
        // 	Dir_Prev = DirOut;
        // }

        //Clip the limits if they exceed the minimum and maximum set limits.
       PID_Output_Avg = ClipLimits(PID_Output_Avg, Down_Limit, Up_Limit);

        ////Control IO////
        if(analogWriteResVal() == 10)
        {
            DirOut = (PID_Output_Avg > 0) ? 0 : 1;
            digitalWrite(SHOULDER_DIR, DirOut);
            analogWrite(SHOULDER_PWM, (uint32_t)abs(PID_Output_Avg));
        }
        else
        {
        	Serial.println("analogWriteResVal Error!");
        }

        // Feedback////
        // static int count = 0;
        //     if(count > 1)
        //     {
        //         // Serial.print(" ");  Serial.print((int)Input_Command);
        //         // Serial.print(" "); Serial.print(Encoder_Ang_adj);
        //         // Serial.print(" O "); Serial.print((uint32_t)abs(PID_Output_Avg));
        //         // Serial.print(" | "); Serial.print(PID_Output);
        //         // Serial.print(" E "); Serial.print(Error);
        //         // Serial.print(" | "); Serial.println(DirOut);

        //         Serial1.print(" ");  Serial1.print((int)Input_Command);
        //         Serial1.print(" "); Serial1.print(Encoder_Ang_adj);
        //         Serial1.print(" | "); Serial1.print((uint32_t)abs(PID_Output_Avg));
        //         Serial1.print(" | "); Serial1.print(PID_Output);
        //         Serial1.print(" | "); Serial1.println(DirOut);
        //         count = 0;
        //     }
        //     count ++;
    }

}


void ElbowControlSystem(Feedback_t * Feedback, Commands_t *Command)
{
	
}


#define WRIST_ROLL_OFFSET   0
void WristControlSystem(Feedback_t * Feedback, Commands_t *Command)
{
	////Constants
	const uint32_t Lower_Limit = 40;
	const uint32_t Upper_Limit = 320;
	const uint32_t Wrist_Precision = 3;
	const double   Wrist_Average = 0.2;
    const uint16_t MAX_PWM = pow(2, analogWriteResVal()) - 1;

    ////Variables
    static double PWM_Avg_L = 0;
    static double PWM_Avg_R = 0;

    motorControl_t PWM_L;
    motorControl_t PWM_R;

    double PWM_Duty_L = 0;
    double PWM_Duty_R = 0;

    ////Collet Command////
    double Pitch_Raw = Command -> Wrist_Pitch;
    static double Pitch_C = 180;
    if((Pitch_Raw < 271) && (Pitch_Raw > 89))
    {
        Pitch_C = Pitch_Raw;
    }

    double Wrist_C = Command -> Wrist_Roll;

    ////Collect Feedback////
	double Pitch_F = Feedback -> Wrist_Pitch;
    double Roll_F = Feedback -> Wrist_Roll;

    double Error           = Pitch_C - Pitch_F;
    double Error_Magnitude = abs(Error);
    int    Error_Polarity  = ((Pitch_C - Pitch_F) / Error_Magnitude); // 1 or -1
    bool   Error_Bool      = (Error + (Error * Error_Polarity)) / (2 * Error);

	// Check Limits
	if((Pitch_F < Lower_Limit) || (Pitch_F > Upper_Limit)){ 
	   PWM_Duty_L = 0;
       PWM_Duty_R = 0;
	   PWM_Avg_L = 0;
       PWM_Avg_R = 0;
	}									
	if((Command -> Wrist_Roll) == 0)
	{
        if(Error_Magnitude > Wrist_Precision)
        {
            PWM_Duty_L =   (MAX_PWM/2)  * (Error_Polarity);
            PWM_Duty_R =   -(MAX_PWM/2) * (Error_Polarity);
        }
        else
        {
            PWM_Duty_L = 0;
            PWM_Duty_R = 0;
            PWM_Avg_L = 0;
            PWM_Avg_R = 0;
        }
	}
	else if((Command -> Wrist_Roll) == 1)
	{
        if(Error_Magnitude > Wrist_Precision)
        {
            PWM_Duty_L = (MAX_PWM/2) - (!Error_Bool  * 400);
            PWM_Duty_R = (MAX_PWM/2) - (Error_Bool * 400);
        }
        else
        {
            PWM_Duty_L = (MAX_PWM/2);
            PWM_Duty_R = (MAX_PWM/2);
        }
	}
	else if((Command -> Wrist_Roll) == 2)
	{
        if(Error_Magnitude > Wrist_Precision)
        {
            PWM_Duty_L = -(MAX_PWM/2) + (Error_Bool  * 400);
            PWM_Duty_R = -(MAX_PWM/2) + (!Error_Bool * 400);
        }
        else
        {
            PWM_Duty_L = -(MAX_PWM/2);
            PWM_Duty_R = -(MAX_PWM/2);
        }
	}

    // else{                                           
    //     if((Command -> Wrist_Roll) == 0)
    //     {
    //         // Stop
    //         if((Pitch_F < Lower_Limit) || (Pitch_F > Upper_Limit)){ 
    //            PWM_Duty_L = 0;
    //            PWM_Duty_R = 0;
    //            PWM_Avg_L = 0;
    //            PWM_Avg_R = 0;
    //         }
    //         // Move Up
    //         else if(Pitch_C > (Pitch_F + Wrist_Precision)){     
              
    //           PWM_Duty_L = MAX_PWM/2;
    //           PWM_Duty_R = -(MAX_PWM/2);
    //         }
    //         // Move Down
    //         else if(Pitch_C < (Pitch_F - Wrist_Precision)){     
             
    //           PWM_Duty_L = -(MAX_PWM/2);
    //           PWM_Duty_R = MAX_PWM/2;}
    //     }
    //     else if((Command -> Wrist_Roll) == 1)
    //     {
    //         PWM_Duty_L = MAX_PWM/2 - (Pitch_F + Wrist_Precision);
    //         PWM_Duty_R = MAX_PWM/2;
    //         //Dir_L = HIGH;
    //         //Dir_R = HIGH; 
    //     }
    //     else if((Command -> Wrist_Roll) == 2)
    //     {
    //         PWM_Duty_L = -MAX_PWM/2;
    //         PWM_Duty_R = -MAX_PWM/2;
    //         //Dir_L = LOW;
    //         //Dir_R = LOW; 
    //     }
    // }

	PWM_Avg_L = (PWM_Duty_L * Wrist_Average) + (PWM_Avg_L * (1 - Wrist_Average));
    PWM_Avg_R = (PWM_Duty_R * Wrist_Average) + (PWM_Avg_R * (1 - Wrist_Average));
	
	if(analogWriteResVal() == 10)
    {
        PWM_L = drv8870MotorControl((int)PWM_Avg_L, 1);
        PWM_R = drv8870MotorControl((int)PWM_Avg_R, 1);

		analogWrite(WRIST_PWM_1_LEFT,  PWM_L.pwm1);
		analogWrite(WRIST_PWM_2_LEFT,  PWM_L.pwm2);
		analogWrite(WRIST_PWM_1_RIGHT, PWM_R.pwm1);
		analogWrite(WRIST_PWM_2_RIGHT, PWM_R.pwm2);
    }
    else
    {
    	Serial.println("analogWriteResVal Error!");
    }


	// static int count = 0;
	// if(count > 10)
	// {
	// 	Serial.print(" Pitch_C: ");   Serial.print(Pitch_C);
	// 	Serial.print(" Pitch_F: ");   Serial.print(Pitch_F);
	// 	// Serial.print(" Roll_C: ");    Serial.print(Wrist_C);
	// 	// Serial.print(" Roll_F: ");    Serial.print(Roll_F);
 //        Serial.print(" Mag: ");     Serial.print(Error_Magnitude);
 //        Serial.print(" Pol: ");     Serial.print(Error_Polarity);
 //        Serial.print(" Bool: ");     Serial.print(Error_Bool);
        
        
	// 	Serial.print(" PWM_L: ");     Serial.print(PWM_Duty_L);
 //        Serial.print(" ");          Serial.print(PWM_Avg_L);
 //        Serial.print(" ");          Serial.print((int)PWM_L.pwm1);
 //        Serial.print(" ");          Serial.print((int)PWM_L.pwm2);
        

	// 	Serial.print(" PWM_R: ");     Serial.print(PWM_Duty_R);
 //        Serial.print(" ");          Serial.print(PWM_Avg_R);
 //        Serial.print(" ");          Serial.print((int)PWM_R.pwm1);
 //        Serial.print(" ");          Serial.println((int)PWM_R.pwm2);

	// 	count = 0;
	// }	
	// count ++;
}


// Whoever is furthest away from the target point gets priority in terms of percent.

// 50%     50%  = Full duty cycle
// Pitch + Roll = Duty cycle

// if pitch is 100 units away
// rotation is 20 units away

// then pitch gets 100/120 percent of power.
// roll gets 		20/120 	percent of power.

// use a scale of 0 - 99
// 0-49 = backwards
// 50 - 99 = forwards




void ClawControlSystem(Feedback_t * Feedback, Commands_t *Command)
{

}

// void ShoulderControlSystemBANGBANG(Commands_t *Command, Feedback_t * Feedback)
// {  
//     //return pid.calculate(Command -> Shoulder, Feedback -> Shoulder);
// 	int32_t MaxPWM = pow(2,analogWriteResVal()) - 1;
// 	int32_t TenthPWM = MaxPWM/10;

// 	static uint32_t PWM_Duty = 0;
// 	static uint32_t DIROut= 0;
// 	static double Feedback_Avg = 0;
// 	static int count = 0;

// 	Feedback -> Shoulder = pulseIn(SHOULDER_ENCODER, HIGH);
// 	// if(abs(Feedback_Avg - Feedback -> Shoulder) > 50)
// 	// {
// 		Feedback_Avg = (Feedback_Avg * (1 - AVG)) + ((double)(Feedback -> Shoulder) * AVG);
// 	//}

// 	// Check Limits
// 	if((Feedback_Avg < BASE_LIM_DOWM) || (Feedback_Avg > BASE_LIM_UP)){ 
// 	   PWM_Duty = 0;
// 	}
// 	// Move Up
// 	else if((Command -> Shoulder) > (Feedback_Avg + Wrist_Precision)){ 	
	  
// 	  DIROut = HIGH; 
// 	  PWM_Duty = TenthPWM;
// 	}
// 	// Move Down
// 	else if((Command -> Shoulder) < (Feedback_Avg - Wrist_Precision)){ 	
	 
// 	  DIROut = LOW; 
// 	  PWM_Duty = TenthPWM;
// 	}
// 	// Hold position
// 	else{ 											
	
// 	  DIROut = LOW;
// 	  PWM_Duty = 0;
// 	}

// 	digitalWrite(SHOULDER_DIR, DIROut);
// 	analogWrite(SHOULDER_PWM, PWM_Duty);

// 	// if(count > 100)
// 	// {
// 		Serial1.print("Com: ");
// 		Serial1.print((int)(Command -> Shoulder));
// 		Serial1.print(" Fed: ");
// 		Serial1.print(Feedback_Avg);
// 		Serial1.print(" PWM: ");
// 		Serial1.print(PWM_Duty);
// 		Serial1.print(" DIR: ");
// 		Serial1.print(DIROut);
// 		Serial1.print("\n");
// 		count = 0;
// 	// }
// 	count ++;

// }

// //accelerometer
// #define MPU                 0x68
// #define THRESHOLD           0.5

// void GetAccelAnalog(){
// 	const float Exp_Avg = 0.1;
// 	//Raw Values
//     uint32_t Accel_Y_Raw = analogRead(23);
//     uint32_t Accel_Z_Raw = analogRead(23);

//     //Mapped Values
//     uint32_t Accel_Y_Map= map(Accel_Y_Raw, 410, 619, -90, 90);
//     uint32_t Accel_Z_Map= map(Accel_Z_Raw, 447, 655, -90, 90);

//     double Degrees_X = RAD_TO_DEG * (atan2(-Accel_Y_Map, -Accel_Z_Map) + PI);
//     //accel.y = RAD_TO_DEG * (atan2(-accel.xAng, -accel.zAng) + PI);
//     //accel.z = RAD_TO_DEG * (atan2(-accel.yAng, -accel.xAng) + PI);

//     if     (Degrees_X >  0   && Degrees_X <  270){ Degrees_X += 90; }
//     else if(Degrees_X >= 270 && Degrees_X <= 360){ Degrees_X = -270 + Degrees_X;}

//    	double Degrees_X_Fil = Degrees_X * Exp_Avg + ( Degrees_X_Fil * (1 - Exp_Avg));

// }

// #define MPU                 0x68
// #define THRESHOLD           0.5
// #define AVG_ACCEL           0.5
// #define AVG_DEG				0.5

// void MPU_Initialize()
// {
// 	Wire.begin();
//   	Wire.beginTransmission(MPU);
//   	Wire.write(byte(0x6B));  	// PWR_MGMT_1 register
//   	Wire.write(byte(0x0));     	// set to zero (wakes up the MPU-6050)
//   	Wire.endTransmission(true);
// }

// double getAccel()
// {
	
// 	static double Accel_X_Fil 	= 0;
// 	static double Accel_Y_Fil 	= 0;
// 	static double Accel_Z_Fil 	= 0;
// 	static double Pitch_Fil 	= 0;
// 	static double Roll_Fil 		= 0;
// 	static double Yaw_Fil 		= 0;
// 	static double Pitch_Full	= 0;
// 	//Send Request to read from register 0x3B
// 	Wire.beginTransmission(MPU);
// 	Wire.write(0x3B);  							
// 	Wire.endTransmission(false);

// 	Wire.requestFrom(MPU,6,true);  					// Requesting 6 Registers
// 	int16_t Accel_X_Raw = Wire.read() << 8 | Wire.read();  	// 0x3B (ACCEL_X_H_Byte) & 0x3C (ACCEL_X_L_Byte)     
// 	int16_t Accel_Y_Raw = Wire.read() << 8 | Wire.read();  	// 0x3D (ACCEL_Y_H_Byte) & 0x3E (ACCEL_Y_L_Byte)
// 	int16_t Accel_Z_Raw = Wire.read() << 8 | Wire.read();  	// 0x3F (ACCEL_Z_H_Byte) & 0x40 (ACCEL_Z_L_Byte)

// 	// Exponential Moving Average on the Raw Accelerometer Values
// 	Accel_X_Fil = Accel_X_Raw * AVG_ACCEL + (Accel_X_Fil * (1 - AVG_ACCEL));
// 	Accel_Y_Fil = Accel_Y_Raw * AVG_ACCEL + (Accel_Y_Fil * (1 - AVG_ACCEL));
// 	Accel_Z_Fil = Accel_Z_Raw * AVG_ACCEL + (Accel_Z_Fil * (1 - AVG_ACCEL));

// 	// Convert acceleration to degrees
// 	double Pitch_Raw = atan( Accel_X_Fil / (sqrt((Accel_Y_Fil * Accel_Y_Fil) + (Accel_Z_Fil * Accel_Z_Fil)))) * (180.0 / 3.141592);
//    	double Roll_Raw =  atan( Accel_Y_Fil / (sqrt((Accel_X_Fil * Accel_X_Fil) + (Accel_Z_Fil * Accel_Z_Fil)))) * (180.0 / 3.141592);
//    	double Yaw_Raw =   atan( (sqrt((Accel_X_Fil * Accel_X_Fil) + (Accel_Y_Fil * Accel_Y_Fil))) / Accel_Z_Fil) * (180.0 / 3.141592);

// 	// double Pitch_Raw = atan2(Accel_X_Fil, sqrt(pow(Accel_Y_Fil,2) + pow(Accel_Z_Fil,2))) * (180.0 / PI);
// 	// double Roll_Raw  = (180 / PI) * atan(sqrt(pow(Accel_Y_Fil,2) + pow(Accel_X_Fil,2)) / (Accel_Z_Fil));
	
// 	// Low Pass Filter on angle values
// 	Pitch_Fil = Pitch_Raw * AVG_DEG + (Pitch_Fil * (1 - AVG_DEG));
// 	Roll_Fil  = Roll_Raw  * AVG_DEG + (Roll_Fil  * (1 - AVG_DEG));
// 	Yaw_Fil   = Yaw_Raw   * AVG_DEG + (Yaw_Fil  * (1 - AVG_DEG));
// 	if((Pitch_Fil > 0) && (Yaw_Fil > 0)){ Pitch_Full = 90 - Pitch_Fil;  }
// 	if((Pitch_Fil < 0) && (Yaw_Fil > 0)){ Pitch_Full = 90 - Pitch_Fil; }                                                   
// 	if((Pitch_Fil < 0) && (Yaw_Fil < 0)){ Pitch_Full = 270 + Pitch_Fil;  }                                                  
// 	if((Pitch_Fil > 0) && (Yaw_Fil < 0)){ Pitch_Full = 270 + Pitch_Fil;  }


// 	// Serial1.print("Pitch: ");
// 	// Serial1.print(Pitch_Fil);
// 	// Serial1.print(" Roll: ");
// 	// Serial1.print(Roll_Fil);
// 	// Serial1.print("Pitch: ");
// 	// Serial1.println(Pitch_Full);

// 	// Serial.print("Pitch: ");
// 	// Serial.print(Pitch_Fil);
// 	// Serial.print(" Roll: ");
// 	// Serial.print(Roll_Fil);
// 	// Serial.print("Pitch: ");
// 	// Serial.println(Pitch_Full);

// 	return Pitch_Full;
// }


// // + +  90 -  0         90 - x
// // - +  0  to -90		 90 - x
// // - - -90 to 0         270 + x
// // + -  0 	to 90		 270 + x








