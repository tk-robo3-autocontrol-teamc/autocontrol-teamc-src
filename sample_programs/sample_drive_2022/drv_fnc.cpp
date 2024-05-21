#include <stdio.h>
#include "drv_fnc.h"


//
// functions -----------------------------------------------------------------------
//

// Get Position direct via function
int Drive::GetPositionIs(WORD iNodeID)
{
	int ret;

	ret = VCS_GetPositionIs(hKeyHandle, iNodeID, &PositionIs, &ErrorCode);

	if (ret == 1) {
		return PositionIs;
	} else {
		printf("Error Code VCS_GetPositionIs: %5.8x \n", ErrorCode);
		return 0;
	}
}


// Clear motor driver error
int Drive::ClearError(WORD iNodeID)
{
	int ret;

	ret = VCS_ClearFault(hKeyHandle, iNodeID, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_ClearFalut: %5.8x \n", ErrorCode);
		return 0;
	}
}

void Drive::ClearErrorDrivers()
{
	ClearError(iNodeIDLeft);
	ClearError(iNodeIDRight);
}


// Set profille Position
int Drive::SetPositionProfile(WORD iNodeID, DWORD iSpeed, DWORD iAcc, DWORD iDec)
{
	int ret;

	ret = VCS_SetPositionProfile(hKeyHandle, iNodeID, iSpeed, iAcc, iDec, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_SetPositionProfile: %5.8x \n", ErrorCode);
		return 0;
	}
}

void Drive::SetPositionProfileDrivers(DWORD iSpeed, DWORD iAcc, DWORD iDec)
{
	SetPositionProfile(iNodeIDLeft, iSpeed, iAcc, iDec);
	SetPositionProfile(iNodeIDRight, iSpeed, iAcc, iDec);
}

// Set Velocity Positon
int Drive::SeVelocityProfile(WORD iNodeID, DWORD iAcc, DWORD iDec)
{
	int ret;

	ret = VCS_SetVelocityProfile(hKeyHandle, iNodeID, iAcc, iDec, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_SetVelocityProfile: %5.8x \n", ErrorCode);
		return 0;
	}
}

void Drive::SetVelocityProfileDrivers(DWORD iAcc, DWORD iDec)
{
	SeVelocityProfile(iNodeIDLeft, iAcc, iDec);
	SeVelocityProfile(iNodeIDRight, iAcc, iDec);
}


// Active Profile Position
int Drive::ActivatePositionProfile(WORD iNodeID)
{
	int ret;

	ret = VCS_ActivateProfilePositionMode(hKeyHandle, iNodeID, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_SetPositionProfile: %5.8x \n", ErrorCode);
		return 0;
	}
}

void Drive::ActivatePositionProfileDrivers()
{
	ActivatePositionProfile(iNodeIDLeft);
	ActivatePositionProfile(iNodeIDRight);
}


// Active Velocity Position
int Drive::ActivateVelocityProfile(WORD iNodeID)
{
	int ret;

	ret = VCS_ActivateProfileVelocityMode(hKeyHandle, iNodeID, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_ActivateProfileVelocityMode: %5.8x \n", ErrorCode);
		return 0;
	}
}

void Drive::ActivateVelocityProfileDrivers()
{
	ActivateVelocityProfile(iNodeIDLeft);
	ActivateVelocityProfile(iNodeIDRight);
}


// Enalbe Driver
int Drive::SetEnableState(WORD iNodeID)
{
	int ret;

	ret = VCS_SetEnableState(hKeyHandle, iNodeID, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_SetEnableState: %5.8x \n", ErrorCode);
		return 0;
	}
}


// Disable Driver
int Drive::SetDisableState(WORD iNodeID)
{
	int ret;

	ret = VCS_SetDisableState(hKeyHandle, iNodeID, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_SetDisableState: %5.8x \n", ErrorCode);
		return 0;
	}
}


// Move to Position
int Drive::MoveToPosition(WORD iNodeID, long iPosition)
{
	int ret;

	ret = VCS_MoveToPosition(hKeyHandle, iNodeID, iPosition, false, true, &ErrorCode);

	if (ret == 1) {
		return 1;
	} else {
		printf("Error Code VCS_MoveToPosition: %5.8x \n", ErrorCode);
		return 0;
	}
}


// Get Movement State
int Drive::GetMovementState(WORD iNodeID)
{
	int ret;

	ret = VCS_GetMovementState(hKeyHandle, iNodeID, &reached, &ErrorCode);

	if (ret == 1) {
		return reached;
	} else {
		printf("Error Code VCS_GetMovementState: %5.8x \n", ErrorCode);
		return 0;
	}
}


// Move to straight
int Drive::MoveToStraight(int count)
{
	int ret1, ret2;

	ret1 = MoveToPosition(iNodeIDLeft, int(-count));
	ret2 = MoveToPosition(iNodeIDRight, int(count));

	if (ret1 == 0) {
		return 0;
	} else {
		if (ret2 == 0) {
			return 0;
		} else {
			return 1;
		}
	}
}

// Move to turn
int Drive::MoveToTrun(int count)
{
	int ret1, ret2;

	ret1 = MoveToPosition(iNodeIDLeft, int(count));
	ret2 = MoveToPosition(iNodeIDRight, int(count));

	if (ret1 == 0) {
		return 0;
	} else {
		if (ret2 == 0) {
			return 0;
		} else {
			return 1;
		}
	}
}


// Calculation encorder count
int Drive::CalcEncorderCount(double distance)
{
	double v1, v2;
	int count;

	v1 = distance / (M_PI * DWHEEL_DIAMETER);
	v2 = v1 * IWHEEL_GEAR / IMOTOR_GEAR;
	count = (int)(IENCORDER_COUNT * v2 * DGEAR_RATIO * IMULTIPLY);

	return count;
}


// Calculation turn move length
double Drive::	CalTurnMoveLength(double degree)
{
	double v, length;

	v = degree / 360.0;
	length = DTREAD * M_PI * v;

	return length;
}
//
// functions ------------------------------------------------------------------------------------------
//
