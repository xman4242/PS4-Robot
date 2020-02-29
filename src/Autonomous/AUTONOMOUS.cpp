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
    if(IsArmed()) ToggleArmed();
    Serial.println("Auton 1");
    delay(5000);
    Robot.Auton1();
}
void AUTONOMOUS::ExecAuton2()
{   
    if(IsArmed()) ToggleArmed();
    Robot.Auton2();
}
void AUTONOMOUS::ExecAuton3()
{
    if(IsArmed()) ToggleArmed();
    Robot.Auton3();
}
void AUTONOMOUS::ExecAuton4()
{
    if(IsArmed()) ToggleArmed();
    Robot.Auton4();
}