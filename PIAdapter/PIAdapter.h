#pragma once
/* PIAdapter/PIAdapter.h
 * Created by Tetsu Otter 20200620
*/
#include "ats.h"
#define ARR_SIZE 256
#define PIADAPTER_VERSION 0x0001
#define FLAG_CHECK_RATE 1
#define FLAG_CHECK_MAX 0x7F				 //約127ms
#define FLAG_CHECK_MAX_ELAPSE 0x3F //約63ms

#define RAISE_FLAG(Dst, Flag) Dst = Dst | Flag
#define LOWER_FLAG(Dst, Flag) Dst = Dst & (~Flag)
#define IsRaised(Dst, Flag) ((Dst & Flag) > 0)

#define SET_SF(Name) Name = 1 << SyncerFlag_Padding::Pad_##Name

typedef struct MMF_ArgData
{
	State state;
	Spec spec;
	Beacon beacon;
	int initialize;
	int setPower;
	int setBrake;
	int setReverser;
	int keyDown;
	int keyUp;
	int hornBlow;
	int setSignal;
} MMF_ArgData;

typedef struct MMF_RWData
{
	UINT16 CallerVersion;
	UINT16 CalleeVersion;
	Hand h; //returned value
} MMF_RWData;

typedef struct MMF_ArrayD
{
	int len = ARR_SIZE;
	int arr[ARR_SIZE];
} MMF_ArrayD;

enum SyncerFlag_Padding
{
	Pad_F_IsEnabled,
	Pad_F_Load,
	Pad_F_Dispose,
	Pad_F_GetPluginVersion,
	Pad_F_SetVehicleSpec,
	Pad_F_Initialize,
	Pad_F_Elapse,
	Pad_F_SetPower,
	Pad_F_SetBrake,

	Pad_F_SetReverser,
	Pad_F_DoorOpen,
	Pad_F_DoorClose,
	Pad_F_KeyDown,
	Pad_F_KeyUp,
	Pad_F_HornBlow,
	Pad_F_SetSignal,
	Pad_F_SetBeaconData
};
enum SyncerFlag
{
	SET_SF(F_IsEnabled),
	SET_SF(F_Load),
	SET_SF(F_Dispose),
	SET_SF(F_GetPluginVersion),
	SET_SF(F_SetVehicleSpec),
	SET_SF(F_Initialize),
	SET_SF(F_Elapse),
	SET_SF(F_SetPower),
	SET_SF(F_SetBrake),

	SET_SF(F_SetReverser),
	SET_SF(F_DoorOpen),
	SET_SF(F_DoorClose),
	SET_SF(F_KeyDown),
	SET_SF(F_KeyUp),
	SET_SF(F_HornBlow),
	SET_SF(F_SetSignal),
	SET_SF(F_SetBeaconData)
};

void SC DoPIFunc(int);

#undef SET_SF
