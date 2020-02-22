
#include "DRIVE.h"
#include "ROBOT.h"

DRIVE::DRIVE(ROBOT &refRobot) : Robot(refRobot)
{
}

void DRIVE::Loop()
{
    //Only Run Command Code When Valid
    if (!CmdTimedOut() && CmdIsRunning())
    {
        if (CmdName() == "ForAsync")
        {
            Robot.State.DriveLeftSpeed = _CmdDriveLeftSpeed;
            Robot.State.DriveRightSpeed = _CmdDriveRightSpeed;
            while (CmdUpdatePercent(millis()))
            {
                delay(20);
            }
        }
    }
    Robot.State.DriveLeftSpeed = _OIDriveLeftSpeed;
    Robot.State.DriveRightSpeed = _OIDriveRightSpeed;

    delay(20);
}

void DRIVE::OISetSpeed(int16_t DriveLeftSpeed,int16_t DriveRightSpeed)
{
    _OIDriveLeftSpeed = DriveLeftSpeed;
    _OIDriveRightSpeed = DriveRightSpeed;
}

bool DRIVE::ForAsync(long durationMS, int16_t DriveLeftSpeed,int16_t DriveRightSpeed, uint8_t HoldUntilPercent)
{
    bool retVal = ForAsync(durationMS, DriveLeftSpeed,DriveRightSpeed);
    while (CmdPercentComplete() < HoldUntilPercent && retVal)
    {
        delay(20);
    }

    return retVal;
}

bool DRIVE::ForAsync(long durationMS, int16_t DriveLeftSpeed,int16_t DriveRightSpeed)
{
    _CmdDriveLeftSpeed = DriveLeftSpeed;
    _CmdDriveRightSpeed = DriveRightSpeed;
    

    bool retVal = CmdStart("ForAsync", millis(), millis() + durationMS, durationMS + 500);

    return retVal;
}
