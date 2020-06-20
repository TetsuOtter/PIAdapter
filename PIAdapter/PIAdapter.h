#pragma once
/* PIAdapter/PIAdapter.h
 * Created by Tetsu Otter 20200620
*/
#include "ats.h"
#define ARR_SIZE 256

typedef union MMF_ArgData
{
	State state;
	Spec spec;
	Beacon beacon;
	int IntValue;

} MMF_ArgData;

typedef struct MMF_RWData {
	int p[ARR_SIZE];//panel values
	int s[ARR_SIZE];//sound values
	Hand h;//returned value
};
typedef struct SyncerVars
{
	UINT8 Load;
	UINT8 Dispose;
	UINT8 GetPluginVersion;
	UINT8 SetVehicleSpec;
	UINT8 Initialize;
	UINT8 Elapse;
	UINT8 SetPower;
	UINT8 SetBrake;
	UINT8 SetReverser;
	UINT8 DoorOpen;
	UINT8 DoorClose;
	UINT8 KeyDown;
	UINT8 KeyUp;
	UINT8 HornBlow;
	UINT8 SetSignal;
	UINT8 SetBeaconData;
};