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
    //Line up diagonal
    //Go straight to tower
    //Cube in corner
    //Blue
    Robot.Lift.ForAsync(6000,255,100);
    Robot.Drive.ForAsync(280,200,200,100);
    Robot.Claw.ForAsync(3000,255,100);
    Robot.Drive.ForAsync(1500,-200,-200,100);
    Robot.Drive.ForAsync(500,200,200,100);
    Robot.Drive.ForAsync(1300,200,-200,100);
    Robot.Drive.ForAsync(1000,200,200,100);
    Robot.Drive.ForAsync(700,200,200,100);
    Robot.Drive.ForAsync(500,-200,-200,100); 

    //Robot.Drive.ForAsync( )
}
void AUTONOMOUS::ExecAuton2()
{    
    //Line up diagonal
    //Go straight to tower
    //Cube in corner
    //REd
    Robot.Lift.ForAsync(7500,255,100);
    Robot.Drive.ForAsync(280,200,200,100);
    Robot.Claw.ForAsync(3000,255,100);
    Robot.Drive.ForAsync(1500,-200,-200,100);
    Robot.Drive.ForAsync(500,200,200,100);
    Robot.Drive.ForAsync(1100,-200,200,100);
    Robot.Drive.ForAsync(1000,200,200,100);
    Robot.Drive.ForAsync(700,200,200,100);
    Robot.Drive.ForAsync(500,-200,-200,100);
}
void AUTONOMOUS::ExecAuton3()
{
    Robot.Drive.ForAsync(1500,-200,-200,100);
    Robot.Drive.ForAsync(750,200,200,100);
}
void AUTONOMOUS::ExecAuton4()
{
   Robot.DriveForEnc(24,200);
   //Robot.TurnforEnc(90,200);
}