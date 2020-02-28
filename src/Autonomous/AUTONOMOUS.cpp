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
    //Diagonaly for tower
    //back and reset against wall
    //Get 2 cubes
    //corner score
    Serial.println("Auton1");
    Robot.DriveForEnc(24,150);
    //Robot.TurnforEnc(90,150);
}
void AUTONOMOUS::ExecAuton2()
{
    //Emergency 1 Point
    Robot.DriveForEnc(24, -150);
    Robot.DriveForEnc(24, 150);
}
void AUTONOMOUS::ExecAuton3()
{

}
void AUTONOMOUS::ExecAuton4()
{

}