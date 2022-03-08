#include "MainWindow.h"
#include "global.h"
#include "TTwincatInterface.h"

using namespace Projet1;
using namespace System::Globalization;

void MainForm::UpdateUI(void)
{
	TC_BOOL b_l_Status;
	TC_INT i_l_Value;
	DATA_LOG s_l_PartData4Log;
	DateTime T_l_Now = DateTime::Now;
	bool b_l_ActiveAlarm;

	if (b_ScreensLoaded)
	{
		ReadTCData(e_CurrentMode, i_l_Value);
		eMachineMode = (MachineModes)i_l_Value;

		if (eLastMachineMode != eMachineMode)
		{
			eLastMachineMode = eMachineMode;
			switch (eMachineMode)
			{
				case MM_Dashboard:
					e_NewScreen = e_DashboardScreen;
					break;
				case MM_Manual:
					e_NewScreen = e_BaseMachineScreen;
					break;
			}
		}
		// Update screens
		if (e_NewScreen != e_CurrentScreen)
		{
			switch(e_NewScreen)
			{
				case e_ProdScreen:
					ShowScreen(pT_ProdScreen);
					break;
				case e_AlarmScreen:
					ShowScreen(pT_AlarmScreen);
					break;
				case e_LogScreen:
					ShowScreen(pT_LogScreen);
					break;
				case e_BaseMachineScreen:
					e_NewScreen = e_MachineScreen;
					ShowScreen(pT_MachineScreen);
					break;
				case e_DashboardScreen:
					ShowScreen(pT_DashboardScreen);
					break;
				case e_CounterScreen:
					ShowScreen(pT_CounterScreen);
					break;
			}
			e_CurrentScreen = e_NewScreen;
		}
		// Update the main window UI

		ReadTCData(s_ModeMask.MMM_Run,b_l_Status);
		this->btnStart->Enabled = (b_l_Status != 0);
		ReadTCData(s_ModeMask.MMM_Stop,b_l_Status);
		this->btnStop->Enabled = (b_l_Status != 0);
		ReadTCData(s_ModeMask.MMM_Pause,b_l_Status);
		this->btnPause->Enabled = (b_l_Status != 0);
		ReadTCData(s_ModeMask.MMM_Dashboard, b_l_Status);
		this->btnDashboard->Enabled = (b_l_Status != 0) || (eMachineMode == MM_Dashboard);
		ReadTCData(s_ModeMask.MMM_Init,b_l_Status);
		this->btnInit->Enabled = (b_l_Status != 0);
		ReadTCData(s_ModeMask.MMM_Manual,b_l_Status);
		this->btnManual->Enabled = (b_l_Status != 0) || (eMachineMode == MM_Manual);

		// Warn vision if nexera is logged on
		WriteTCData(b_MondemaMode, (TC_BOOL)TUser::b_HasSystemLevel());

		ReadTCData(s_MachineSafety.MM_CanLockDoor,b_l_Status);
		this->btnLockDoor->Enabled = (b_l_Status != 0);
		ReadTCData(s_MachineSafety.MM_CanUnlockDoor,b_l_Status);
		this->btnUnlockDoor->Enabled = (b_l_Status != 0);
		lblStatus->Text = ": " + gcnew String(aac_MachineModes[eMachineMode]);
		lblOrder->Text = ": " + ProductionOrder::pS_GetName();
		lblPart->Text = ": " + ProductionOrder::pS_GetReference();

		lblDate->Text = ": " + TUtilities::pS_FormatDate(T_l_Now);
		lblTime->Text = ": " + T_l_Now.ToString("T");
		btnExit->Enabled = !(ProductionOrder::b_OrderStarted());
		//Update alarms
		pT_AlarmScreen->UpdateAlarmsTable();
		lblLastAlarm->Text = pT_AlarmScreen->pS_GetLastAlarm(&b_l_ActiveAlarm);
		if (b_l_ActiveAlarm)
			lblLastAlarm->ForeColor = Color::Red;
		else
			lblLastAlarm->ForeColor = Color::Black;
		//Update parts data logging
		ReadTCData(s_PartData4Log,s_l_PartData4Log);
		if (s_l_PartData4Log.PDL_PartReady)
		{
			TJobLogger::AddJobPartLog(s_l_PartData4Log.PDL_PartStatus, (s_l_PartData4Log.PDL_EndOfProd != 0));
			ClearTCData(s_PartData4Log.PDL_PartReady);
			pT_ProdScreen->UpdateUI();
		}
		else
			pT_ProdScreen->UpdateUI();
		// Update screens
		pT_MachineScreen->UpdateUI();
		pT_DashboardScreen->UpdateUI();
		pT_CounterScreen->UpdateUI();
		UpdateLoginData();
		LogProbing();
	}
}

void MainForm::UpdateLoginData(void)
{
	lblUser->Text = ": " + TUser::pS_GetName();
	btnUsers->Enabled = TUser::b_HasManagerLevel();
}

void MainForm::LoadScreen(enum Screens e_x_NewScreen)
{
	e_NewScreen = e_x_NewScreen;
}


void MainForm::LogProbing()
{
	int i = 0;
	PROBING_LOG as_l_ProbingLog[2];
	TC_BOOL ab_l_NewLog[2];
	DateTime Now = DateTime::Now.Date;
	String^ pS_l_CompleteLine = gcnew String("");
	String^ pS_l_FileName = gcnew String("");

	CleanUpLogProbing();
	for (i = 0; i<2; i++)
	{
		ReadTCData(as_ProbingLog[i], as_l_ProbingLog[i]);
		ab_l_NewLog[i] = as_l_ProbingLog[i].PL_NewLog;
		if (ab_l_NewLog[i])
			ClearTCData(as_ProbingLog[i].PL_NewLog);
	}
	for (i = 0; i < 2; i++)
	{
		if ((apT_ExportFile[i] == nullptr) || ((Now - at_LastLog[i]).Days > 0))
		{
			at_LastLog[i] = Now;
			if (apT_ExportFile[i])
				delete (IDisposable^)apT_ExportFile[i];
			apT_ExportFile[i] = nullptr;
			pS_l_FileName = C_APP_PROBING_LOGS_PATH;
			pS_l_FileName += "Head_" + (i+1).ToString() + "_";
			pS_l_FileName += Now.ToString("_dd_MM_yyyy") + ".csv";

			if (File::Exists(pS_l_FileName))
			{
				apT_ExportFile[i] = File::AppendText(pS_l_FileName);
			}
			else
			{
				apT_ExportFile[i] = File::AppendText(pS_l_FileName);
				apT_ExportFile[i]->AutoFlush = true;
				pS_l_CompleteLine = "Date;Zone;Position;Position contrôle;Seuil Précedent;Seuil";
				apT_ExportFile[i]->WriteLine(pS_l_CompleteLine);
				apT_ExportFile[i]->Flush();
			}
		}
		if (ab_l_NewLog[i])
		{
			pS_l_CompleteLine = TUtilities::pS_FormatDateTime(DateTime::Now) + "; " + String::Format("{0:D}; {1:F3}; {2:F3}; {3:D}; {4:D}", as_l_ProbingLog[i].PL_ProbingArea, as_l_ProbingLog[i].PL_ProbingPos[0], as_l_ProbingLog[i].PL_ProbingPos[1], as_l_ProbingLog[i].PL_PreviousProbingThreshold, as_l_ProbingLog[i].PL_ProbingThreshold);
			apT_ExportFile[i]->WriteLine(pS_l_CompleteLine);
			apT_ExportFile[i]->Flush();
			ab_l_NewLog[i] = false;
		}
	}

}

void MainForm::CleanUpLogProbing()
{
	if (!b_NeedCleanup)
	{
		if ((DateTime::Now.Date - t_LastCleanUp).Days > 0)
		{
			b_NeedCleanup = true;
		}
	}
	if (b_NeedCleanup)
	{
		DateTime Now = DateTime::Now.Date;
		t_LastCleanUp = Now;
		b_NeedCleanup = false;
		String^ sFolder = C_APP_PROBING_LOGS_PATH;
		sFolder = sFolder->Remove(sFolder->Length - 1);

		for each (String^ sFile in Directory::GetFiles(sFolder))
		{
			try
			{
				String^ sDate = sFile->Substring(sFile->Length - 14, 10);
				DateTime tDate = DateTime::ParseExact(sDate, "dd_MM_yyyy", CultureInfo::InvariantCulture, DateTimeStyles::None);
				if ((Now - tDate).Days > 30)
				{
					File::Delete(sFile);
				}
			}
			catch (...)
			{

			}
		}
	}

}