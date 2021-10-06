#include "Methods.h"

/////////////////////////////////////////////////////////////////////////////
//                              Function Definitions                       //
/////////////////////////////////////////////////////////////////////////////
void initialize()
{
   for(uint8_t i = 7; i < 23; i++){
    if(i == 9)
    {
      pinMode(i, OUTPUT);
      i++;
    }
    pinMode(i, INPUT);
    }
   for(uint8_t i = 0; i < 7; i++){
    pinMode(i, OUTPUT);
    }
    pinMode(BATTERY_CHARGE, OUTPUT);
    pinMode(OPEN_CLAW, INPUT_PULLUP);
    pinMode(CLOSE_CLAW, INPUT_PULLUP);
    pinMode(POSITION_ONE, INPUT_PULLUP);
    pinMode(POSITION_TWO, INPUT_PULLUP);
    pinMode(POSITION_THREE, INPUT_PULLUP);
    pinMode(WRIST_LEFT, INPUT_PULLUP);
    pinMode(WRIST_RIGHT, INPUT_PULLUP);
    //pinMode(20, OUTPUT);

    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0);
}

int EMA(uint16_t measurement, uint16_t prev, uint8_t alpha) {
  return ((measurement * alpha) / 100 + (prev * (100 - alpha)) / 100);
}

double boundaries(double angle, double low, double high)
{
  if(angle >= low && angle <= high)
    return angle;
  else if(angle < low)
    return low;
  else
    return high;
}

double JoyMap(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void joystickInput(Command_S A[])
{
  ///////// 4 Button Line Up ////////
  Joystick.button(1, !digitalRead(OPEN_CLAW)); // open
  Joystick.button(2, !digitalRead(CLOSE_CLAW)); // close
  Joystick.button(3, !digitalRead(POSITION_ONE)); // 
  Joystick.button(4, !digitalRead(POSITION_TWO)); //
  

  //////// Isolated BUtton //////////
  Joystick.button(5, !digitalRead(POSITION_THREE)); // 
  
  //////// 2 Side by Side Buttons ////////
  Joystick.button(6, !digitalRead(WRIST_LEFT)); // wrist roll left
  Joystick.button(7, !digitalRead(WRIST_RIGHT)); // wrist roll right

  A[BASE].raw = analogRead(A[BASE].pin);                        //      |  Base           Axis 0
  A[SHOULDER].raw = analogRead(A[SHOULDER].pin);                //      |  Shoulder       Axis 1
  A[ELBOW].raw = analogRead(A[ELBOW].pin);                      //      |  Elbow          Axis 2
  A[WRIST_PITCH].raw = analogRead(A[WRIST_PITCH].pin);          //      |  Wrist Pitch    Axis 4
                                                                //      |
  A[ROTUNDA_CAM].raw = analogRead(A[ROTUNDA_CAM].pin); //Side Pot;      | Wrist Rotation  Axis 5
  A[CLAW_TORQUE].raw = analogRead(A[CLAW_TORQUE].pin); //Slider Pot;    | Claw Torque     Axis 3

  A[BASE].smooth = EMA(A[BASE].raw, A[BASE].smooth, EXP);
  A[SHOULDER].smooth = EMA(A[SHOULDER].raw, A[SHOULDER].smooth, EXP);
  A[ELBOW].smooth = EMA(A[ELBOW].raw, A[ELBOW].smooth, EXP);
  A[WRIST_PITCH].smooth = EMA(A[WRIST_PITCH].raw, A[WRIST_PITCH].smooth, EXP);
  A[ROTUNDA_CAM].smooth = EMA(A[ROTUNDA_CAM].raw, A[ROTUNDA_CAM].smooth, EXP);
  A[CLAW_TORQUE].smooth = EMA(A[CLAW_TORQUE].raw, A[CLAW_TORQUE].smooth, EXP);

  A[BASE].joy = JoyMap(A[BASE].smooth, 0, 1023, -1, 1);      
  A[SHOULDER].joy = JoyMap(A[SHOULDER].smooth, 0, 1023, -1, 1);
  A[ELBOW].joy = JoyMap(A[ELBOW].smooth, 0, 1023, -1, 1);
  A[WRIST_PITCH].joy = JoyMap(A[WRIST_PITCH].smooth, 0, 1023, -1, 1);
  A[ROTUNDA_CAM].joy = JoyMap(A[ROTUNDA_CAM].smooth, 0, 1023, -1, 1);
  A[CLAW_TORQUE].joy = JoyMap(A[CLAW_TORQUE].smooth, 0, 1023, -1, 1);

  A[BASE].joy = boundaries(A[BASE].joy, BASE_LOW, BASE_HIGH);      
  A[SHOULDER].joy = boundaries(A[SHOULDER].joy, SHOULDER_LOW, SHOULDER_HIGH);
  A[ELBOW].joy = boundaries(A[ELBOW].joy, ELBOW_LOW, ELBOW_HIGH);
  A[WRIST_PITCH].joy = boundaries(A[WRIST_PITCH].joy, PITCH_LOW, PITCH_HIGH);
  A[ROTUNDA_CAM].joy = boundaries(A[ROTUNDA_CAM].joy, ROTATION_LOW, ROTATION_HIGH);
  A[CLAW_TORQUE].joy = boundaries(A[CLAW_TORQUE].joy, TORQUE_LOW, TORQUE_HIGH);


// Calibration Steps:  
// Uncomment Calibration Section and Comment out Calibrated Section
// Load To Teensy
// Note minimum and max values reachable on HTML 5 Gamepad Site
// Set corresponding LOW and HIGH values in Methods.h
// Comment out Calibration Section and Uncomment Calibrated Section
// Load To Teensy

///////// Calibration /////////  

  // A[BASE].angle        = A[BASE].smooth;
  // A[SHOULDER].angle    = A[SHOULDER].smooth;
  // A[ELBOW].angle       = A[ELBOW].smooth;
  // A[ROTUNDA_CAM].angle = A[ROTUNDA_CAM].smooth;
  // A[WRIST_PITCH].angle = A[WRIST_PITCH].smooth;
  // A[CLAW_TORQUE].angle = A[CLAW_TORQUE].smooth;

//////// Calibrated //////////

  A[BASE].angle = JoyMap(A[BASE].joy, BASE_LOW, BASE_HIGH, 480, 1023);      // 480 for deadzone compensation in linux os
  A[SHOULDER].angle = JoyMap(A[SHOULDER].joy, SHOULDER_LOW, SHOULDER_HIGH, 1023, 0);
  A[ELBOW].angle = JoyMap(A[ELBOW].joy, ELBOW_LOW, ELBOW_HIGH, 0, 1023);
  A[WRIST_PITCH].angle = JoyMap(A[WRIST_PITCH].joy, PITCH_LOW, PITCH_HIGH, 0, 1023);
  A[ROTUNDA_CAM].angle = JoyMap(A[ROTUNDA_CAM].joy, ROTATION_LOW, ROTATION_HIGH, 0, 1023);
  A[CLAW_TORQUE].angle = JoyMap(A[CLAW_TORQUE].joy, TORQUE_LOW, TORQUE_HIGH, 0, 1023);

////// End ///////////

  Joystick.X(A[BASE].angle);
  //Joystick.Y(A[BASE].smooth);
  //Joystick.Z(A[BASE].raw);

  Joystick.Y(A[SHOULDER].angle);
  Joystick.Z(A[ELBOW].angle);                    //in usb.desc.c, set joystick_interface to following:
  Joystick.sliderLeft(A[WRIST_PITCH].angle);     //Usage (Sliders) 0x09, 0x35,
  Joystick.sliderRight(A[ROTUNDA_CAM].angle); 
  Joystick.Zrotate(A[CLAW_TORQUE].angle);        //Usage (Rz) 0x09, 0x33,

///////// Wrist and Claw Torque Lock //////

  //Joystick.sliderRight(511);
  //Joystick.Zrotate(0);
}

void currentIndicator(Command_S A[]) // repurposed to indicate rotation state of base
{
  uint16_t leds;

  /////////// Original Purposed Code ////////////

  // uint16_t highest;
  // for(uint8_t i = 0; i < 6; i++)
  // {
  //   uint16_t temp = A[i].feedback;
  //   if(highest < temp) 
  //     {highest = temp;}
  // }
  //////////////////////////////////////////////


  shiftOut(DATA_PIN, CLOCK_PIN, 1, leds);
  for(int16_t i = 7; i >= 0; i--)
    {
    //if(highest > (1005 / 7) * i + 3) // original if statement
      if((A[BASE].raw) > (1005 / 7) * i + 3)
        {
          bitSet(leds, i);
          shiftOut(DATA_PIN, CLOCK_PIN, 1, leds);
        }
      else
        {
          bitClear(leds, i);
          shiftOut(DATA_PIN, CLOCK_PIN, 1, leds);
        }
    }
}

void feedbackMotor(Command_S A[])
{
  A[BASE].PWM = (((MAX_PWM * A[BASE].feedback) / 2) / MAX_ANALOG);
  A[SHOULDER].PWM = (((MAX_PWM * A[SHOULDER].feedback) / 2) / MAX_ANALOG);
  A[ELBOW].PWM = (((MAX_PWM * A[ELBOW].feedback) / 2) / MAX_ANALOG);
  A[WRIST_PITCH].PWM = (((MAX_PWM * A[WRIST_PITCH].feedback)  / 2) / MAX_ANALOG);
  A[ROTUNDA_CAM].PWM = (((MAX_PWM * A[ROTUNDA_CAM].feedback)  / 2) / MAX_ANALOG);
  A[CLAW_TORQUE].PWM = (((MAX_PWM * A[CLAW_TORQUE].feedback) / 2) / MAX_ANALOG);
  analogWrite(A[BASE].mPin, A[BASE].PWM);
  analogWrite(A[SHOULDER].mPin, A[SHOULDER].PWM);
  analogWrite(A[ELBOW].mPin, A[ELBOW].PWM);
  analogWrite(A[WRIST_PITCH].mPin, A[WRIST_PITCH].PWM);
  analogWrite(A[ROTUNDA_CAM].mPin, A[ROTUNDA_CAM].PWM);      
  analogWrite(A[CLAW_TORQUE].mPin, A[CLAW_TORQUE].PWM);
}
