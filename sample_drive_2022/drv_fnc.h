#ifndef _DRVFNC_H_
#define _DRVFNC_H_

#include <math.h>
#include <unistd.h>
#include "../EPOS_Linux_Library/include/Definitions.h"


// Mechanical values
#define DWHEEL_DIAMETER	82.0			// 82mm
#define DTREAD			307.6			// tread 307.6mm
#define IMOTOR_GEAR		16
#define IWHEEL_GEAR		45
#define DGEAR_RATIO		1539.0 / 44.0	// Gear Ratio
#define IENCORDER_COUNT	512				// encorder pulse
#define IMULTIPLY		4				// encorder 4 multiply

typedef void* HANDLE;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned int DWORD;


class Drive {
public:

	BOOL reached=0;
	DWORD ErrorCode=0;

	WORD iNodeIDLeft=1;
	WORD iNodeIDRight=2;
	HANDLE hKeyHandle=0;
	int PositionIs=0;

	
	// Get Position direct via function
	int GetPositionIs(WORD iNodeID);

	// Clear motor driver error
	int ClearError(WORD iNodeID);
	void ClearErrorDrivers();

	// Set profille Position
	int SetPositionProfile(WORD iNodeID, DWORD iSpeed, DWORD iAcc, DWORD iDec);
	void SetPositionProfileDrivers(DWORD iSpeed, DWORD iAcc, DWORD iDec);

	// Set Velocity Positon
	int SeVelocityProfile(WORD iNodeID, DWORD iAcc, DWORD iDec);
	void SetVelocityProfileDrivers(DWORD iAcc, DWORD iDec);

	// Active Profile Position
	int ActivatePositionProfile(WORD iNodeID);
	void ActivatePositionProfileDrivers();

	// Active Velocity Position
	int ActivateVelocityProfile(WORD iNodeID);
	void ActivateVelocityProfileDrivers();

	// Enalbe Driver
	int SetEnableState(WORD iNodeID);

	// Disable Driver
	int SetDisableState(WORD iNodeID);

	// Move to Position
	int MoveToPosition(WORD iNodeID, long iPosition);

	// Get Movement State
	int GetMovementState(WORD iNodeID);

	// Move to straight
	int MoveToStraight(int count);

	// Move to turn
	int MoveToTrun(int count);

	// Calculation encorder count
	int CalcEncorderCount(double distance);

	// Calculation turn move length
	double CalTurnMoveLength(double degree);
};

#endif // _DRVFNC_H_

