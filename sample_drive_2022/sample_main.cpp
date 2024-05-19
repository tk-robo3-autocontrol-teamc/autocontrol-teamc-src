#include <stdio.h>
#include "drv_fnc.h"


// main ----------------------------------------------------------------------------------------------
int main()
{
    char deviceName[]           = "EPOS4";
    char protocolStackName[]    = "MAXON SERIAL V2";
    char interfaceName[]        = "USB";
    char portName[]             = "USB0";

    Drive drive;

    // Open USB port
    printf("Opening Port ... \n");
    drive.hKeyHandle = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName, &drive.ErrorCode);

    if (drive.hKeyHandle != 0) {
        printf("hKeyHandle : %8p \n", drive.hKeyHandle);

        // Clear Error
        printf("Clear Error...\n");
        drive.ClearErrorDrivers();

        // Set Profile Position Mode
        printf("Set Profile Position...\n");
        // Speed = 3000, Acceleration = 1000, Deceleration = 5000
        drive.SetPositionProfileDrivers(3000, 1000, 5000);

        printf("Activate Profile Position...\n");
        drive.ActivatePositionProfileDrivers();

        // Enable Motor Driver
        printf("Enable Motor Driver...\n");
        drive.SetEnableState(drive.iNodeIDLeft);
        drive.SetEnableState(drive.iNodeIDRight);

        // Move Position
        // 1. Go straight 300mm
        printf("# 1. Go straight 300mm : %8d\n", drive.CalcEncorderCount(300.0));
        drive.MoveToStraight(drive.CalcEncorderCount(300.0));

        // move end check
        drive.reached = false;
        while (drive.reached == false) {
            drive.reached = drive.GetMovementState(drive.iNodeIDLeft);
        }

        // 2. Go Turn Left
        printf("# 2. Go Turn Left : %8d \n", drive.CalcEncorderCount(drive.CalTurnMoveLength(90.0)));
        drive.MoveToTrun(drive.CalcEncorderCount(drive.CalTurnMoveLength(90.0)));

        // move end check
        drive.reached = false;
        while (drive.reached == false) {

            drive.reached = drive.GetMovementState(drive.iNodeIDLeft);
        }

        // 3. Go straight 200mm
        printf("# 3. Go straight 200mm : %8d \n", drive.CalcEncorderCount(200.0));
        drive.MoveToStraight(drive.CalcEncorderCount(200.0));

        // move end check
        drive.reached = false;
        while (drive.reached == false) {

            drive.reached = drive.GetMovementState(drive.iNodeIDLeft);
        }

        // 4. Go Turn Right
        printf("# 4. Go Turn Right : %8d \n", drive.CalcEncorderCount(drive.CalTurnMoveLength(90.0)));
        drive.MoveToTrun(drive.CalcEncorderCount(drive.CalTurnMoveLength(90.0)) * (-1));

        // move end check
        drive.reached = false;
        while (drive.reached == false) {

            drive.reached = drive.GetMovementState(drive.iNodeIDLeft);
        }

        // 5. Go straight 200mm
        printf("# 5. Go straight 200mm : %8d \n", drive.CalcEncorderCount(200.0));
        drive.MoveToStraight(drive.CalcEncorderCount(200.0));

        // move end check
        drive.reached = false;
        while (drive.reached == false) {

            drive.reached = drive.GetMovementState(drive.iNodeIDLeft);
        }

        // Set Velocity Mode
        // Acceleration = 1000, Deceleration = 5000
        printf("Set Profile Velocity... \n");
        drive.SetVelocityProfileDrivers(1000, 5000);

        printf("Activate Profile Velocity...\n");
        drive.ActivateVelocityProfileDrivers();


        printf("turn 10 seconeds...\n");
        // Move Velocity 10 seconds
        // Turning
        VCS_MoveWithVelocity(drive.hKeyHandle, drive.iNodeIDLeft, 3000, &drive.ErrorCode);
        VCS_MoveWithVelocity(drive.hKeyHandle, drive.iNodeIDRight, 3000, &drive.ErrorCode);
        // wait 10 seconds
        sleep(10);			// sec
        printf("10 sec\n");

        // Disable Motor Driver
        drive.SetDisableState(drive.iNodeIDLeft);
        drive.SetDisableState(drive.iNodeIDRight);

        // Close Com - Port
        VCS_CloseDevice(drive.hKeyHandle, &drive.ErrorCode);
        printf("Error Code Closing Port: %5.8x \n", drive.ErrorCode);

    } else {
        // Error Exit
        printf("Could not open Com-Port \n");
        printf("hKeyHandle: %8p \n", drive.hKeyHandle);
        printf("Error Openening Port: %5.8x \n", drive.ErrorCode);
    }

}
