#include "AUTONOMOUS.h"
#include "ROBOT.h"

AUTONOMOUS::AUTONOMOUS(ROBOT &refRobot) : Robot(refRobot)
{
    _MaxProgramNumber = 4;
}

void AUTONOMOUS::Loop()
{
    if (_AutonARMED)
    {
        if (Robot.State.AutonLightSensorActive)
        {
            LaunchQueued();
        }
    }

    if (_RunningAuton == "Auton1") ExecAuton1();
    else if(_RunningAuton == "Auton2") ExecAuton2();
    else if(_RunningAuton == "Auton3") ExecAuton3();
    else if(_RunningAuton == "Auton4") ExecAuton4();

     _RunningAuton = "";
    delay(20);
}

void AUTONOMOUS::ExecAuton1()
{   
    Serial.println("Success 1");
    //Robot.DriveForEnc(24,-150);
    //Robot.DriveForEnc(24,150);
    Robot.Drive.ForAsync(1000,255,255,100);
    Serial.println("Success 2");
}
void AUTONOMOUS::ExecAuton2()
{
    
}
void AUTONOMOUS::ExecAuton3()
{

}
void AUTONOMOUS::ExecAuton4()
{

}