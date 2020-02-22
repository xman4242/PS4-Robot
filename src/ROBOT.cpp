#include "ROBOT.h"

ROBOT::ROBOT(YETI_YUKON &rYukon) : Yukon(rYukon),
     DriveLeft(_DriveLeftPWM, &Yukon.PWM, _DriveLeftDir, &Yukon.GPIO, _DriveLeftReversed), 
     DriveRight(_DriveRightPWM, &Yukon.PWM, _DriveRightDir, &Yukon.GPIO, _DriveRightReversed), 
     LiftMotor(_LiftMotorPWM, &Yukon.PWM, _LiftMotorDir, &Yukon.GPIO, _LiftMotorReversed), 
     ClawMotor(_ClawMotorPWM, &Yukon.PWM, _ClawMotorDir, &Yukon.GPIO, _ClawMotorReversed), 
     LeftEnc(_LeftEncPin1,_LeftEncPin2),
     RightEnc(_RightEncPin1, _RightEncPin2),
     LiftEnc(_LiftEncPin1, _LiftEncPin2),
    Drive(*this),
    Lift(*this),
    Claw(*this),
    Auton(*this),
    Xbox(&Usb)
    
        
    

{
}

void ROBOT::Setup()
{   
    Usb.Init();
    DriveLeft.Init();
    DriveRight.Init();
    LiftMotor.Init();
    ClawMotor.Init();
    PS4.begin("20:20:20:20:20:20"); 
    Serial.println("PS4 Ready");
    LeftEnc.write(0);
    RightEnc.write(0);

    pinMode(_Button0, INPUT_PULLUP);
    pinMode(_LEDBuiltIn, OUTPUT);
    pinMode(EnablePin, INPUT);
    digitalWrite(_LEDBuiltIn, LOW);
}
bool dumpsterfire = false;
bool AnalogControl = true;
bool PrecisionMode = false;
int16_t DriveLeftSpeed = 0;
int16_t DriveRightSpeed = 0;
int16_t AutonDriveSpeed = 0;
int16_t AutonLeftSpeed = 0;
int16_t AutonRightSpeed = 0;
int16_t AutonLiftSpeed = 0;
int16_t LiftSpeed = 0;
int16_t ClawSpeed = 0;
bool winning = true;
int _NextModeMillis = 0;
bool Armed = false;
bool AutoRunning = false;
int AutonNum = 1;
long OldLeftPos = -999;
long OldRightPos = -999;
long OldLiftPos = -999;
int commandNum = 1;
long LeftPos = 0;
long RightPos = 0;
long LiftPos = 0;
int AverageEncoderVal = 0;
int Distance = 0;
int AutonError = 0;
float AutonPercentRemain = 0;
float Pconst = 0;
int Setpoint = 0;
int RightError = 0;
int LeftError = 0;
int LiftError = 0;
int LeftSetpoint = 0;
int RightSetpoint = 0;
int LiftSetpoint = 0;
bool EnableVal = false;
int _NextControllerMillis = 0;


void ROBOT::Loop()
{
    //Read The Controller
    //READXBOX();
    if(_NextControllerMillis < millis())
    {
         READPS4();
        _NextControllerMillis = millis() + 5;
    }
    
    
    if(digitalRead(_Button0) == LOW)
    {
        digitalWrite(_LEDBuiltIn, HIGH);
        Yukon.SetupWIFI();
        delay(1000);
    }
    //Read The Sensors
    EnableVal = digitalRead(EnablePin);
    State.AutonLightSensorActive = EnableVal;
    Yukon.DisableWatchdog();
    
    if((Armed && EnableVal) || AutoRunning == true)
    {
        if(AutonNum ==1)
        Auton1();

        if(AutonNum == 2)
        Auton2();

        if(AutonNum == 3)
        Auton3();

        if(AutonNum == 4)
        Auton4();

        Armed = false;
    }

        LeftPos = (LeftEnc.read())*-1;
        RightPos = (RightEnc.read())*-1;
        LiftPos = LiftEnc.read(); 

    //Write To Motor Controllers
    if (_NextMotorControllerWriteMillis < millis())
    {
    _NextMotorControllerWriteMillis = millis() + 20;
    DriveLeft.SetMotorSpeed(State.DriveLeftSpeed);
    DriveRight.SetMotorSpeed(State.DriveRightSpeed);
    LiftMotor.SetMotorSpeed(State.LiftMotorSpeed);
    ClawMotor.SetMotorSpeed(State.ClawMotorSpeed);
    }

    //Write the Display
    if (_NextDisplayMillis < millis())
    {
        _NextDisplayMillis = millis() + 250;
        if(DebugMode)
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print("Right Enc");
            Yukon.OLED.println(RightEnc.read());
            Yukon.OLED.setTextSize(1); 
            Yukon.OLED.print("Lift Enc");
            Yukon.OLED.println(LiftEnc.read());
            Yukon.OLED.display();
        }
        else if (Auton.IsArmed())
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.print("ARMED");
            //Yukon.OLED.println(EnableVal);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print(Auton.QueuedProgramName());
            Yukon.OLED.display();
        }
        
        else if(AutoRunning)
        {
             Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(2);
            Yukon.OLED.print("Running");
            //Yukon.OLED.println(EnableVal);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.print(AutonNum);
            Yukon.OLED.display();
        }
        
        else
        {
            Yukon.OLED.clearDisplay();
            Yukon.OLED.setCursor(0, 0);
            Yukon.OLED.setTextSize(1);
            Yukon.OLED.println("MOSTLY");
            Yukon.OLED.println("HARMLESS");
            Yukon.OLED.print("Battery = ");
            Yukon.OLED.print(PS4.data.status.battery, DEC);
            Yukon.OLED.println(" / 16");
            Yukon.OLED.display();
        }
    }
}

void ROBOT::Auton1()
{   
    ResetEnc();
    //DriveForEnc(24,-150);
    DriveRight.SetMotorSpeed(-200); 
    DriveLeft.SetMotorSpeed(-200);
    delay(3500);
    DriveLeft.SetMotorSpeed(0);
    DriveRight.SetMotorSpeed(0); 
    ResetEnc();
    DriveForEnc(24, 150);
    EndAuton();
}

void ROBOT::Auton2()
{
   
}
void ROBOT::Auton3()
{

}
void ROBOT::Auton4()
{   
     
}



//Set inches positive, speed controlls direction
void ROBOT::DriveForEnc(float Inches, int16_t Speed)
{  
    //Find inches in ticks
    Distance = ((Inches)/(3.14*4)*360);
    LeftSetpoint = Distance;
    RightSetpoint = Distance;

    //Forwards
    if(Speed > 0)
    {
    while(RightEnc.read() < Distance || LeftEnc.read() < Distance)
    {   
        if(RightEnc.read() < RightSetpoint)
        {
            DriveRight.SetMotorSpeed(Speed);
        }
        if(LeftEnc.read() < LeftSetpoint)
        {
            DriveLeft.SetMotorSpeed(Speed);
        }
    }
    DriveRight.SetMotorSpeed(0); // Stop the loop once the encoders have counted up the correct number of encoder ticks.
    DriveLeft.SetMotorSpeed(0);
    }
    //Backwards
    if(Speed < 0)
    {
    while(RightEnc.read() > Distance || LeftEnc.read() > Distance)
    {   
        if(RightEnc.read() > Distance)
        {
            DriveRight.SetMotorSpeed(Speed);
        }
        if(LeftEnc.read() > Distance)
        {
            DriveLeft.SetMotorSpeed(Speed);
        }
    }
    DriveRight.SetMotorSpeed(0); // Stop the loop once the encoders have counted up the correct number of encoder ticks.
    DriveLeft.SetMotorSpeed(0);
    }
    ResetEnc();
    
}

//Degrees is positive to go clockwise, and negative to go counterclockwise
//Speed is positive
void ROBOT::TurnforEnc(int Degrees, int16_t Speed)
{                                                   
    float TicksInDeg = 6.7;
    int Setpoint = abs(Degrees) * TicksInDeg;

    if(Degrees > 0)
    {   RightSetpoint = Setpoint * -1;
        LeftSetpoint = Setpoint;
        while(RightEnc.read() > RightSetpoint || LeftEnc.read() < LeftSetpoint)
        {   
            
            if(RightEnc.read() > Setpoint)
            {
                DriveRight.SetMotorSpeed(Speed * -1);
            }

            if(LeftEnc.read() < Setpoint)
            {
                DriveLeft.SetMotorSpeed(Speed);
            }
            
            
        }

    }

    if(Degrees < 0)//Left turn, Left speed neg
    {   
        RightSetpoint = Setpoint;
        LeftSetpoint = Setpoint * -1;
        while(RightEnc.read() < Setpoint || LeftEnc.read() > Setpoint)
        {   
            if(RightEnc.read() < Setpoint)
            {
                DriveRight.SetMotorSpeed(Speed);
            }

            if(LeftEnc.read() > Setpoint)
            {
                DriveLeft.SetMotorSpeed(Speed * -1);
            }
    
        }

    }
    DriveRight.SetMotorSpeed(0);
    DriveLeft.SetMotorSpeed(0);
     
}

//Make inches Positve to go up, negative to go down
//Speed is always positive
void ROBOT::LiftForEnc(float Inches, int16_t Speed)
{
    float TicksPerInch = 0;
    int Setpoint = Inches * TicksPerInch;

    while(LiftEnc.read() < Setpoint)
    {
        if(_NextMotorControllerWriteMillis < millis())
        {
            LiftMotor.SetMotorSpeed(Speed);
        } 
    }
    
    while(LiftEnc.read() > Setpoint)
    {
        if(_NextMotorControllerWriteMillis < millis())
        {
            LiftMotor.SetMotorSpeed(Speed * -1);
        }
    }
    ResetEnc();
}

//Resets the encoders. Is automatically called, but you can call it if you want to be safe
void ROBOT::ResetEnc()
{
    LeftPos = 0;
    RightPos = 0;
    LiftPos = 0;
    LeftEnc.write(0);
    RightEnc.write(0);
    LiftEnc.write(0);    
}

//Put at the end of routines
void ROBOT::EndAuton()
{   
    AutoRunning = false;
    Armed = false;
    Drive.OISetSpeed(0,0);
    Serial.println("Auton Ended");
}

void ROBOT::READXBOX()
{
    //Read The Controller
    Usb.Task();

    if (Xbox.XboxReceiverConnected)
    {
    for (uint8_t i = 0; i < 4; i++)
    {
    if (Xbox.Xbox360Connected[i])
    {
        DriveLeftSpeed = (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(LeftHatY, i), 7500));
        DriveRightSpeed = (Yukon.XBOXJoystickTo255(Xbox.getAnalogHat(RightHatY, i), 7500));
        LiftSpeed = ((Xbox.getButtonPress(R2))-(Xbox.getButtonPress(L2)))*255;
        ClawSpeed = (Xbox.getButtonPress(R1)-Xbox.getButtonPress(L1))*255;
         
        if(Xbox.getButtonClick(Y))
        {
            PrecisionMode = !PrecisionMode;
        }

        if(Xbox.getButtonClick(XBOX))
        {
            DebugMode = !DebugMode;
        }

        if(PrecisionMode)
        {
            DriveLeftSpeed = DriveLeftSpeed/2;
            DriveRightSpeed = DriveRightSpeed/2;
        }

        if (Xbox.getButtonClick(LEFT))
        AutonNum--; 
        if (Xbox.getButtonClick(RIGHT))
        AutonNum++;
        if (Xbox.getButtonClick(DOWN))
        Armed = !Armed;
        if(Xbox.getButtonPress(X))
        AutoRunning = true;
        Drive.OISetSpeed(DriveLeftSpeed, DriveRightSpeed);
        Lift.OISetSpeed(LiftSpeed);
        Claw.OISetSpeed(ClawSpeed);
    }
    }
    }

}

void ROBOT::READPS4()
{
     DriveLeftSpeed = (PS4.data.analog.stick.ly)*2;
            DriveRightSpeed = (PS4.data.analog.stick.ry)*2;

            if(abs(DriveLeftSpeed) < 11)
            {
                DriveLeftSpeed = 0;
            }

            if(abs(DriveRightSpeed) < 11)
            {
                DriveRightSpeed = 0;
            }   
           
            LiftSpeed = (PS4.data.analog.button.r2)-(PS4.data.analog.button.l2);
            ClawSpeed = (PS4.data.button.r1-PS4.data.button.l1)*255;
            Drive.OISetSpeed(DriveLeftSpeed,DriveRightSpeed);
            Lift.OISetSpeed(LiftSpeed);
            Claw.OISetSpeed(ClawSpeed);
            

 
                if(PS4.data.button.circle == 1)
                {
                    PrecisionMode = !PrecisionMode;
                }

                if(PS4.data.button.down)
                {
                    Auton.ToggleArmed();
                }

                if(PS4.data.button.right)
                {
                    Auton.QueueNext();
                }

                if(PS4.data.button.left)
                {
                    Auton.QueuePrev();
                }

                if(PS4.data.button.options)
                {
                    DebugMode = !DebugMode;
                }

                if(PS4.data.button.up)
                {
                    AutoRunning = true;
                }

                 if(PrecisionMode)
                {
                DriveLeftSpeed = PS4.data.analog.stick.ly;
                DriveRightSpeed = PS4.data.analog.stick.ry;
                }
            

            
}