#include "CounterScreen.h"

using namespace Projet1;

void CounterScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_DWORD d_l_Data;

		ReadTCData(s_Counter.TC_PearlingMotorUseTime[0], d_l_Data);
		tbLeftMotorUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_PearlingMotorUseTime[1], d_l_Data);
		tbRightMotorUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_PearlingSpindleUseTime[0], d_l_Data);
		tbLeftSpindleUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_PearlingSpindleUseTime[1], d_l_Data);
		tbRightSpindleUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_AspirationUseTime, d_l_Data);
		tbAspirationUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_VacuumUseTime, d_l_Data);
		tbVacuumUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_Prod.PC_ProdQty, d_l_Data);
		tbPartProduced->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_MeanMTBF, d_l_Data);
		tbMeanMTBF->Text = TUtilities::pS_FormatTimeSpan(TimeSpan::FromSeconds(d_l_Data));
		ReadTCData(s_Counter.TC_MachineOnTime, d_l_Data);
		tbMachineOnTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCData(s_Counter.TC_InProdTime, d_l_Data);
		tbInProdTime->Text = String::Format("{0:D}", d_l_Data);

	}
}

void CounterScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
}
