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
    _AutonARMED = false;
    Serial.println("Auton 1");
    Robot.Auton1();
}
void AUTONOMOUS::ExecAuton2()
{   
    _AutonARMED = false;
    Serial.println("Auton 2");
    Robot.Auton2();
}
void AUTONOMOUS::ExecAuton3()
{
    _AutonARMED = false;
    Serial.println("Auton 3");
    Robot.Auton3();
}
void AUTONOMOUS::ExecAuton4()
{
    _AutonARMED = false;
    Serial.println("Auton 4");
    Robot.Auton4();
}