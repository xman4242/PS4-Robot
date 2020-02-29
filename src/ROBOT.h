#ifndef ROBOT_h
#define ROBOT_h
#define DELTA_TIME 10 //Change in time between readings (millis)
#define MinIntegralVal 1 //This sets the minimum integral value. Change if you are having problems with it growing to large
#define ErrorPercent .05 //This is the percentage around the setpoint it will check for completion. Do not change unless you know what you are doing!
#include <Encoder.h>
#include <YETI_YUKON.h>
#include <STATE.h>
#include <PS4Controller.h>
#include <esp_bt_main.h>
#include <esp_bt_device.h>
#include <SPI.h>
#include <YUKON_CytronMD10.h>
#include "Subsystems\Drive.h"
#include "Subsystems\Lift.h"
#include "Subsystems\Claw.h"
#include "Autonomous\AUTONOMOUS.h"

class ROBOT
{
  public:
    ROBOT(YETI_YUKON &rYukon);

    void Setup();
    void Loop();
    void Auton1();
    void Auton2();
    void Auton3();
    void Auton4();
    IRAM_ATTR int32_t GetLeftEnc();
    IRAM_ATTR int32_t GetRightEnc();
    IRAM_ATTR int32_t GetLiftEnc();
    void DriveForEnc(float Inches, int16_t Speed);
    void TurnforEnc(int Degrees , int16_t Speed);
    void LiftForEnc(float Inches, int16_t Speed);
    void EndAuton();
    void ResetEnc();
    double PIDLoop(int &Setpoint, int SensorReading, double Kp, double Ki, double Kd, int MinError, int MaxOutput);
    void READXBOX();
    void READPS4();




    YETI_YUKON &Yukon;

    STATE State;

    //Motors
    YUKON_CytronMD10 DriveLeft;
    YUKON_CytronMD10 DriveRight;
    YUKON_CytronMD10 LiftMotor;
    YUKON_CytronMD10 ClawMotor;
    Encoder LeftEnc;
    Encoder RightEnc;
    Encoder LiftEnc;

    //Subsystems
    DRIVE Drive;
    LIFT Lift;
    CLAW Claw;
    AUTONOMOUS Auton;
    //USB
  

    //Vars
    int ErrorAmt = 0;
    int Integral = 0;
    int Derivative = 0;
    int Output = 0;
    int PreviousError = 0;
    int PreviousSensorReading = 0;
    int NegativeSide = 3;
    bool DebugMode = false;
  
    
    
   

    //PIN Declarations
    static const int _DriveLeftPWM = 0;
    static const int _DriveLeftDir = 0;
    static const bool _DriveLeftReversed = false;
        
    static const int _DriveRightPWM = 1;
    static const int _DriveRightDir = 1;
    static const bool _DriveRightReversed = false;
        
    static const int _LiftMotorPWM = 2;
    static const int _LiftMotorDir = 2;
    static const bool _LiftMotorReversed = true;
        
    static const int _ClawMotorPWM = 3;
    static const int _ClawMotorDir = 3;
    static const bool _ClawMotorReversed = false;
    
    static const int _LeftEncPin1 = 21;
    static const int _LeftEncPin2 = 22;

    static const int _RightEncPin1 = 17;
    static const int _RightEncPin2 = 14;

    static const int _LiftEncPin1 = 999;
    static const int _LiftEncPin2 = 999;

    static const uint8_t _Button0 = 0;
    static const uint8_t _LEDBuiltIn = 25;
    static const uint8_t EnablePin = 32;
    
  private:
      long _NextDisplayMillis = 0;
      long _NextMotorControllerWriteMillis = 0;
};

#endif