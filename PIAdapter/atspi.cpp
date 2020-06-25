/* PIAdapter/ dllmain.cpp => atspi.cpp
 * Created by Tetsu Otter 20200620 => 20200626
 * Copyright 2020 Tetsu Otter
 * License : The MIT License
*/

#include "ats.h"
#include "PIAdapter.h"
#include <chrono>
#include <thread>
#include <string>

#define MMFName_File "PIAdapter.mmf.%X.bin" //%XにPIDを入れる.

#define MMFName_Syncer "PIAdapter_Syncer"
#define MMFName_ArgData "PIAdapter_ArgData"
#define MMFName_RWData "PIAdapter_RWData"
#define MMFName_PanelD "PIAdapter_PanelD"
#define MMFName_SoundD "PIAdapter_SoundD"

MMF_ArgData *ArgData = NULL;
MMF_RWData *RWData = NULL;
MMF_ArrayD *PanelD = NULL;
MMF_ArrayD *SoundD = NULL;
int Syncer_len = 0;
int *Syncer = NULL;

//MMFに関しては日経XTECHを参照 : https://xtech.nikkei.com/it/article/COLUMN/20071107/286607/

BOOL APIENTRY DllMain(HMODULE hModule,
											DWORD ul_reason_for_call,
											LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: //Called when this dll is called first time
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

		//MemoryMappedFileは実ファイルとする.  ファイル名はMMFName_File
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH: //Called when this dll is disposed
													 //if resources is not released, do in this section.
		break;
	}
	return TRUE;
}

void SC DoPIFunc(int Flag)
{
	for (int i = 0; i < Syncer_len; i++)
		RAISE_FLAG(Syncer[i], Flag); //実行命令/実行中フラグを立てる

	//FLAG_CHECK_MAXに達するまでの間, IsEnabledフラグおよびFunctionフラグをチェックする.
	//  => タイムアウト機能
	bool Doing = false;
	for (int i = 0; i < FLAG_CHECK_MAX; i++, Doing = false)
	{
		for (int j = 0; j < Syncer_len; j++) //各PIの状態を読み出す.
			if (!Doing && IsRaised(Syncer[j], SyncerFlag::F_IsEnabled) && IsRaised(Syncer[j], Flag))
				Doing = true; //このPIは未だ実行中

		if (!Doing)
			break; //各PIは実行を完了済み

		Sleep(FLAG_CHECK_RATE); //連続して読むのはやりすぎだから, ちょっと待つ.
	}

	//何か実行中のPIがある
	if (Doing)
		//全PI Check
		for (int i = 0; i < Syncer_len; i++)
			//PI有効かつ, Timeoutしたにも関わらず関数実行中である
			if (IsRaised(Syncer[i], SyncerFlag::F_IsEnabled) && IsRaised(Syncer[i], Flag))
				//実行完了を検出できなければ, PI異常としてそのプラグインは無効化.
				//但し, 処理負荷の都合上, UnloadはDisposeで行う.
				LOWER_FLAG(Syncer[i], SyncerFlag::F_IsEnabled);
}

DE void SC Load()
{
	//PIの関数を実行する
	DoPIFunc(SyncerFlag::F_Load);
}
DE void SC Dispose()
{
	DoPIFunc(SyncerFlag::F_Dispose);

	//release all of the dll resources.
}
DE int SC GetPluginVersion()
{
	DoPIFunc(SyncerFlag::F_GetPluginVersion);
	return PI_VERSION;
}
DE void SC SetVehicleSpec(Spec s)
{
	ArgData->spec = s; //引数の値をセットする.

	DoPIFunc(SyncerFlag::F_SetVehicleSpec);
}
DE void SC Initialize(int b)
{
	ArgData->initialize = b; //引数の値をセットする

	DoPIFunc(SyncerFlag::F_Initialize);
}
DE Hand SC Elapse(State S, int *p, int *s)
{
	//引数の値をセットする
	ArgData->state = S;

	memcpy(PanelD->arr, p, sizeof(int) * ARR_SIZE); //受け取ったPanel配列の情報をコピーする
	memcpy(SoundD->arr, s, sizeof(int) * ARR_SIZE); //受け取ったSound配列の情報をコピーする.

	for (int i = 0, PI_IsEnabled = false; i < Syncer_len; i++, PI_IsEnabled = false) //順々にに実行する.
	{
		RAISE_FLAG(Syncer[i], SyncerFlag::F_Elapse); //実行命令/実行中フラグを立てる

		for (int j = 0; j < FLAG_CHECK_MAX; j++)
			if (!IsRaised(Syncer[j], SyncerFlag::F_IsEnabled) && !IsRaised(Syncer[j], SyncerFlag::F_Elapse))
			{
				PI_IsEnabled = true;
				break; //実行完了済み
			}
			else
				Sleep(FLAG_CHECK_RATE); //連続して読むのはやりすぎだから, ちょっと待つ.

		//実行完了を検出できなければ, PI異常としてそのプラグインは無効化.
		//但し, 処理負荷の都合上, UnloadはDisposeで行う.
		if (!PI_IsEnabled)
			LOWER_FLAG(Syncer[i], SyncerFlag::F_IsEnabled);
	}

	memcpy(p, PanelD->arr, sizeof(int) * ARR_SIZE); //PIが弄った情報を書き戻す
	memcpy(p, SoundD->arr, sizeof(int) * ARR_SIZE); //PIが弄った情報を書き戻す

	return RWData->h; //Calleeがうまく何とかしてくれてると信じて
}
DE void SC SetPower(int p)
{
	ArgData->setPower = p;

	DoPIFunc(SyncerFlag::F_SetPower);

	handle.P = p;
}
DE void SC SetBrake(int b)
{
	ArgData->setBrake = b;

	DoPIFunc(SyncerFlag::F_SetBrake);

	handle.B = b;
}
DE void SC SetReverser(int r)
{
	ArgData->setReverser = r;

	DoPIFunc(SyncerFlag::F_SetReverser);

	handle.R = r;
}
DE void SC DoorOpen()
{
	DoPIFunc(SyncerFlag::F_DoorOpen);
}
DE void SC DoorClose()
{
	DoPIFunc(SyncerFlag::F_DoorClose);
}
DE void SC KeyDown(int k)
{
	ArgData->keyDown = k;

	DoPIFunc(SyncerFlag::F_KeyDown);
}
DE void SC KeyUp(int k)
{
	ArgData->keyUp = k;

	DoPIFunc(SyncerFlag::F_KeyUp);
}
DE void SC HornBlow(int k)
{
	ArgData->hornBlow = k;

	DoPIFunc(SyncerFlag::F_HornBlow);
}
DE void SC SetSignal(int a)
{
	ArgData->setSignal = a;

	DoPIFunc(SyncerFlag::F_SetSignal);
}
DE void SC SetBeaconData(Beacon b)
{
	ArgData->beacon = b;

	DoPIFunc(SyncerFlag::F_SetBeaconData);
}
