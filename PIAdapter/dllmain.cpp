/* PIAdapter/dllmain.cpp
 * Created by Tetsu Otter 20200620
*/

#include "ats.h"
#include <chrono>
#include <thread>

#define MMFName_Syncer "PIAdapter_Syncer001"
#define MMFName_ArgData "PIAdapter_ArgData001"
#define MMFName_RWData "PIAdapter_RWData001"

BOOL APIENTRY DllMain( HMODULE hModule,
											 DWORD  ul_reason_for_call,
											 LPVOID lpReserved
										 )
{
		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH://Called when this dll is called first time
			//Check Running Architecture
			//Check $(FileName).txt
			//	if failed in this step, show error msg and return FALSE
			//Replace "$(TargetArchitecture)" to x86, x64 etc.
			//Check Dlls are exist
			//	if failed in this step, remove the dll-path from list
			//Check Dlls Architecture
			//	if failed in this step, remove the dll-path from list
			//if Architecture is not same...
			//	Create MemoryMappedFile(MMFName_Syncer, )
			//	Create $(FileName).Adapter.exe process if needed with dll-path and SyncerOffset
			//	if failed in this section, show error msg
			//if usable dll is not available, return FALSE
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH://Called when this dll is disposed
			//if resources is not released, do in this section.
				break;
		}
		return TRUE;
}

DE void SC Load()
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC Dispose()
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0

	//release all of the dll resources.
}
DE int SC GetPluginVersion()
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
	return PI_VERSION;
}
DE void SC SetVehicleSpec(Spec s)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC Initialize(int b)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE Hand SC Elapse(State S, int * p, int * s)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => do not parallel
	//wait syncer to be 0

	//brake => take bigger value
	//power => take smaller value
	//revers=> take 0.  if not, take bigger value

	return handle;
}
DE void SC SetPower(int p)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0

	handle.P = p;
}
DE void SC SetBrake(int b)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0

	handle.B = b;
}
DE void SC SetReverser(int r)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0

	handle.R = r;
}
DE void SC DoorOpen()
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC DoorClose()
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC KeyDown(int k)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC KeyUp(int k)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC HornBlow(int k)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC SetSignal(int a)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}
DE void SC SetBeaconData(Beacon b)
{
	//set 1 to Syncer
	//(do some actions in the adapter) => parallel
	//wait syncer to be 0
}

